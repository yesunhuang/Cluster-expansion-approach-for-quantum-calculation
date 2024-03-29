/**
 * @ 文件名: main_wrapper.c
 * @ 功能: 封装, 并提供与Python的交互接口
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 2020年2月9日
 *
 */

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdlib.h>

#include "solver.h"

#define RAISE_PY_ERROR(err, strerr) do{if (!PyErr_Occurred()){PyErr_SetString(err, strerr);} return NULL;}while(0)

void destructDataCapsule(PyObject * capsule) {
	pDeriveData p = (pDeriveData)PyCapsule_GetPointer(capsule, "ClusterData");
	if (p == NULL)
		return;
	FreeOfDData(p);
	return;
}

/**
 * @ 函数: int CheckArgsDData(PyObject* dataobjct, pDeriveData* outputdd)
 *
 * @ 功能: 将被包装的pDeriveData数据解包, 并传回c语言指针
 *
 * @ param{dataobject}: 被包装的pDeriveData数据
 *
 * @ param{outputdd}: 解包的pDeriveData指针输出
 *
 * @ 返回值: 若存在删除并成功时,返回值为1; 否则,返回值为0.
 */
int CheckArgsDData(PyObject* dataobject, pDeriveData* outputdd) {
	if (!PyCapsule_CheckExact(dataobject)) {
		/* 检查是否为capsule */
		RAISE_PY_ERROR(PyExc_TypeError, "The passed arg isn't a cluster data object.");
	}
	if (strcmp(PyCapsule_GetName(dataobject), "ClusterData") != 0) {
		/* 检查是否为cluster的数据 */
		RAISE_PY_ERROR(PyExc_TypeError, "The passed arg isn't a cluster data object.");
	}
	*outputdd = (pDeriveData)PyCapsule_GetPointer(dataobject, "ClusterData");
	return 1;
}

/**
 * @ 函数: static PyObject* core_DeriveAssign(PyObject* self, PyObject* args)
 *
 * @ 功能: 根据传入的参数, 进行DeriveAndAssign过程
 *
 * @ 七个参数说明: [Initial状态], [Hamilton算符...], [Hamilton算符系数], [Collapse算符...], [Collapse算符系数], [Tracking算符...], 最长算符长度
 *
 * @ 返回值: 若存在删除并成功时,返回值为1; 否则,返回值为0.
 */
static PyObject*
core_DeriveAssign(PyObject* self, PyObject* args) {
	if (PyTuple_Size(args) != 7) {
		RAISE_PY_ERROR(PyExc_TypeError, "Too many(few) args are passed.");
	}
	/* 读入数据并转换类型 */
	pOPArray* inputArr_HO; int* inputArrLens_HO; Complex* inputArrCoef_HO; int inputArrLen_HO;
	pOPArray* inputArr_CO; int* inputArrLens_CO; Complex* inputArrCoef_CO; int inputArrLen_CO;
	int* inputArr_Init; int inputArrLen_Init;
	pOPArray* inputArr_Track; int* inputArrLens_Track; int inputArrLen_Track;
	int maxOPLen;
	PyObject* objects[6];
	if (!PyArg_ParseTuple(args, "OOOOOOI", objects, objects + 1, objects + 2, objects + 3, objects + 4, objects + 5, &maxOPLen)) {
		RAISE_PY_ERROR(PyExc_TypeError, "The passed args aren't valid.");
	}
	// [Initial状态]
	if (!PyList_CheckExact(objects[0])) {
		RAISE_PY_ERROR(PyExc_TypeError, "The 1st arg isn't a list.");
	}
	inputArrLen_Init = PyList_Size(objects[0]);
	inputArr_Init = (int*)malloc(inputArrLen_Init * sizeof(int)); ASSERTNULL(inputArr_Init);
	for (int i = 0; i < inputArrLen_Init; ++i) {
		PyObject* tempobj = PyList_GetItem(objects[0], i);
		if (!PyLong_Check(tempobj)) {
			RAISE_PY_ERROR(PyExc_TypeError, "The arg in initial list isn't long type.");
		}
		inputArr_Init[i] = PyLong_AsLong(tempobj);
	}
#ifdef __CRTDEBUG__
	printf("object[0]\n");
#endif // __TREEDEBUG__
	// [Hamiton算符...], [Hamilton算符系数...]
	if (!PyList_CheckExact(objects[1])) {
		RAISE_PY_ERROR(PyExc_TypeError, "The 2nd arg isn't a list.");
	}
	inputArrLen_HO = PyList_Size(objects[1]);
	inputArr_HO = (pOPArray*)malloc(inputArrLen_HO * sizeof(pOPArray)); ASSERTNULL(inputArr_HO);
	inputArrLens_HO = (int*)malloc(inputArrLen_HO * sizeof(int)); ASSERTNULL(inputArrLens_HO);
	for (int i = 0; i < inputArrLen_HO; ++i) {
		PyObject* tempobj = PyList_GetItem(objects[1], i);
		if (!PyList_CheckExact(tempobj)) {
			RAISE_PY_ERROR(PyExc_TypeError, "The arg in hamilton list isn't a list.");
		}
		inputArrLens_HO[i] = PyList_Size(tempobj);
		inputArr_HO[i] = (pOPArray)malloc(inputArrLens_HO[i] * sizeof(UINT_L)); ASSERTNULL(inputArr_HO[i]);
		for (int j = 0; j < inputArrLens_HO[i]; ++j) {
			PyObject* tt = PyList_GetItem(tempobj, j);
			if (!PyLong_Check(tt)) {
				RAISE_PY_ERROR(PyExc_TypeError, "The arg in hamilton operator isn't long type.");
			}
			inputArr_HO[i][j] = PyLong_AsLong(tt);
		}
	}
	if (!PyList_CheckExact(objects[2])) {
		RAISE_PY_ERROR(PyExc_TypeError, "The 3rd arg isn't a list.");
	}
	inputArrCoef_HO = (Complex*)malloc(inputArrLen_HO * sizeof(Complex)); ASSERTNULL(inputArrCoef_HO);
	for (int i = 0; i < inputArrLen_HO; ++i) {
		PyObject* tempc = PyList_GetItem(objects[2], i);
		if (PyComplex_CheckExact(tempc)) {
			inputArrCoef_HO[i].real = PyComplex_RealAsDouble(tempc);
			inputArrCoef_HO[i].image = PyComplex_ImagAsDouble(tempc);
		}
		else if (PyLong_Check(tempc)) {
			inputArrCoef_HO[i].real = PyLong_AsDouble(tempc);
			inputArrCoef_HO[i].image = 0.0;
		}
		else if (PyFloat_Check(tempc)) {
			inputArrCoef_HO[i].real = PyFloat_AsDouble(tempc);
			inputArrCoef_HO[i].image = 0.0;
		}
		else {
			RAISE_PY_ERROR(PyExc_TypeError, "The arg in hamilton coef list isn't complex or long or float type.");
		}
	}
#ifdef __CRTDEBUG__
	printf("object[1,2]\n");
#endif // __CRTDEBUG__
	// [Collapse算符...], [Collapse算符系数...]
	if (!PyList_CheckExact(objects[3])) {
		RAISE_PY_ERROR(PyExc_TypeError, "The 4th arg isn't a list.");
	}
	inputArrLen_CO = PyList_Size(objects[3]);
	inputArr_CO = (pOPArray*)malloc(inputArrLen_CO * sizeof(pOPArray)); ASSERTNULL(inputArr_CO);
	inputArrLens_CO = (int*)malloc(inputArrLen_CO * sizeof(int)); ASSERTNULL(inputArrLens_CO);
	for (int i = 0; i < inputArrLen_CO; ++i) {
		PyObject* tempobj = PyList_GetItem(objects[3], i);
		if (!PyList_CheckExact(tempobj)) {
			RAISE_PY_ERROR(PyExc_TypeError, "The arg in collapse list isn't a list.");
		}
		inputArrLens_CO[i] = PyList_Size(tempobj);
		inputArr_CO[i] = (pOPArray)malloc(inputArrLens_CO[i] * sizeof(UINT_L)); ASSERTNULL(inputArr_CO[i]);
		for (int j = 0; j < inputArrLens_CO[i]; ++j) {
			PyObject* tt = PyList_GetItem(tempobj, j);
			if (!PyLong_Check(tt)) {
				RAISE_PY_ERROR(PyExc_TypeError, "The arg in collapse operator isn't long type.");
			}
			inputArr_CO[i][j] = PyLong_AsLong(tt);
		}
	}
	if (!PyList_CheckExact(objects[4])) {
		RAISE_PY_ERROR(PyExc_TypeError, "The 5th arg isn't a list.");
	}
	inputArrCoef_CO = (Complex*)malloc(inputArrLen_CO * sizeof(Complex)); ASSERTNULL(inputArrCoef_CO);
	for (int i = 0; i < inputArrLen_CO; ++i) {
		PyObject* tempc = PyList_GetItem(objects[4], i);
		if (PyComplex_CheckExact(tempc)) {
			inputArrCoef_CO[i].real = PyComplex_RealAsDouble(tempc);
			inputArrCoef_CO[i].image = PyComplex_ImagAsDouble(tempc);
		}
		else if (PyLong_Check(tempc)) {
			inputArrCoef_CO[i].real = PyLong_AsDouble(tempc);
			inputArrCoef_CO[i].image = 0.0;
		}
		else if (PyFloat_Check(tempc)) {
			inputArrCoef_CO[i].real = PyFloat_AsDouble(tempc);
			inputArrCoef_CO[i].image = 0.0;
		}
		else {
			RAISE_PY_ERROR(PyExc_TypeError, "The arg in hamilton coef list isn't complex or long or float type.");
		}
	}
#ifdef __CRTDEBUG__
	printf("object[3,4]\n");
#endif // __CRTDEBUG__
	// [Tracking算符...]
	if (!PyList_CheckExact(objects[5])) {
		RAISE_PY_ERROR(PyExc_TypeError, "The 6th arg isn't a list.");
	}
	inputArrLen_Track = PyList_Size(objects[5]);
	inputArr_Track = (pOPArray*)malloc(inputArrLen_Track * sizeof(pOPArray)); ASSERTNULL(inputArr_Track);
	inputArrLens_Track = (int*)malloc(inputArrLen_Track * sizeof(int)); ASSERTNULL(inputArrLens_Track);
	for (int i = 0; i < inputArrLen_Track; ++i) {
		PyObject* tempobj = PyList_GetItem(objects[5], i);
		if (!PyList_CheckExact(tempobj)) {
			RAISE_PY_ERROR(PyExc_TypeError, "The arg in tracking list isn't a list.");
		}
		inputArrLens_Track[i] = PyList_Size(tempobj);
		inputArr_Track[i] = (pOPArray)malloc(inputArrLens_Track[i] * sizeof(UINT_L)); ASSERTNULL(inputArr_Track[i]);
		for (int j = 0; j < inputArrLens_Track[i]; ++j) {
			PyObject* tt = PyList_GetItem(tempobj, j);
			if (!PyLong_Check(tt)) {
				RAISE_PY_ERROR(PyExc_TypeError, "The arg in tracking operator isn't long type.");
			}
			inputArr_Track[i][j] = PyLong_AsLong(tt);
		}
	}
#ifdef __CRTDEBUG__
	printf("object[5]\n");
#endif // __CRTDEBUG__
	/* 生成data */
	pDeriveData data = NULL;
	DeriveAssign(inputArr_HO, inputArrLens_HO, inputArrCoef_HO, inputArrLen_HO,
		inputArr_CO, inputArrLens_CO, inputArrCoef_CO, inputArrLen_CO,
		inputArr_Init, inputArrLen_Init, inputArr_Track, inputArrLens_Track, inputArrLen_Track, maxOPLen, &data);

	/* capsule包装 */
	PyObject* cap = PyCapsule_New(data, "ClusterData", destructDataCapsule);

	/* 释放申请的内存 */
	for (int i = 0; i < inputArrLen_HO; ++i) {
		free(inputArr_HO[i]);
	}
	free(inputArrLens_HO);
	free(inputArrCoef_HO);
	for (int i = 0; i < inputArrLen_CO; ++i) {
		free(inputArr_CO[i]);
	}
	free(inputArrLens_CO);
	free(inputArrCoef_CO);
	free(inputArr_Init);
	for (int i = 0; i < inputArrLen_Track; ++i) {
		free(inputArr_Track[i]);
	}
	free(inputArrLens_Track);

	return cap;
}

static PyObject*
core_CalEvolution(PyObject* self, PyObject* args) {
	PyObject* pyData = NULL;
	if (PyTuple_Size(args) != 1) {
		RAISE_PY_ERROR(PyExc_TypeError, "Too many args are passed.");
	}
	if (!PyArg_ParseTuple(args, "O", &pyData)) {
		RAISE_PY_ERROR(PyExc_TypeError, "The passed arg isn't a object.");
	}
	pDeriveData data = NULL;
	CheckArgsDData(pyData, &data);

	Complex* output = NULL;
	if (CalEvolution(data, &output) == 0 && output == NULL) {
		RAISE_PY_ERROR(PyExc_RuntimeError, "Fatal Error.");
	};
	int size = data->size;
	PyObject* comList = PyList_New(size);
	for (int i = 0; i < size; ++i) {
		PyObject* c = PyComplex_FromDoubles(output[i].real, output[i].image);
		PyList_SetItem(comList, i, c);
	}
	free(output);

	return comList;
}

static PyObject*
core_SetCurrentValue(PyObject* self, PyObject* args) {
	if (PyTuple_Size(args) != 2) {
		RAISE_PY_ERROR(PyExc_TypeError, "Too many(few) args are passed.");
	}
	PyObject* pyData, * pyList;
	if (!PyArg_ParseTuple(args, "OO", &pyData, &pyList))
	{
		RAISE_PY_ERROR(PyExc_TypeError, "The passed args aren't objects.");
	}
	if (!PyList_CheckExact(pyList)) {
		RAISE_PY_ERROR(PyExc_TypeError, "The second arg isn't a strict list.");
	}
	pDeriveData data;
	CheckArgsDData(pyData, &data);
	int listSize = PyList_Size(pyList);
	Complex* buf = (Complex*)malloc(data->size * sizeof(Complex)); ASSERTNULL(buf);
	memset(buf, 0, data->size * sizeof(Complex));
	for (int i = 0; i < MIN(listSize, data->size); ++i) {
		PyObject* temp = PyList_GetItem(pyList, i);
		if (PyComplex_CheckExact(temp)) {
			buf[i].real = PyComplex_RealAsDouble(temp);
			buf[i].image = PyComplex_ImagAsDouble(temp);
		}
		else if (PyFloat_Check(temp)) {
			buf[i].real = PyFloat_AsDouble(temp);
			buf[i].image = 0.0;
		}
		else if (PyLong_Check(temp)) {
			buf[i].real = PyLong_AsDouble(temp);
			buf[i].image = 0.0;
		}
		else {
			RAISE_PY_ERROR(PyExc_TypeError, "The stuff in the list aren't complexes or longs or floats.");
		}
	}
	SetCurrentValueOfDData(data, buf, MIN(listSize, data->size));
	free(buf);
	Py_RETURN_NONE;
}

static PyObject*
core_SetHamiltonCoef(PyObject* self, PyObject* args) {
	if (PyTuple_Size(args) != 2) {
		RAISE_PY_ERROR(PyExc_TypeError, "Too many(few) args are passed.");
	}
	PyObject* pyData, * pyList;
	if (!PyArg_ParseTuple(args, "OO", &pyData, &pyList))
	{
		RAISE_PY_ERROR(PyExc_TypeError, "The passed args aren't objects.");
	}
	if (!PyList_CheckExact(pyList)) {
		RAISE_PY_ERROR(PyExc_TypeError, "The second arg isn't a strict list.");
	}
	pDeriveData data;
	CheckArgsDData(pyData, &data);
	int listSize = PyList_Size(pyList);
	Complex* buf = (Complex*)malloc(data->hoSize * sizeof(Complex)); ASSERTNULL(buf);
	memset(buf, 0, data->hoSize * sizeof(Complex));
	for (int i = 0; i < MIN(listSize, data->hoSize); ++i) {
		PyObject* temp = PyList_GetItem(pyList, i);
		if (PyComplex_CheckExact(temp)) {
			buf[i].real = PyComplex_RealAsDouble(temp);
			buf[i].image = PyComplex_ImagAsDouble(temp);
		}
		else if (PyFloat_Check(temp)) {
			buf[i].real = PyFloat_AsDouble(temp);
			buf[i].image = 0.0;
		}
		else if (PyLong_Check(temp)) {
			buf[i].real = PyLong_AsDouble(temp);
			buf[i].image = 0.0;
		}
		else {
			RAISE_PY_ERROR(PyExc_TypeError, "The stuff in the list aren't complexes or longs or floats.");
		}
	}
	SetHOCoefOfDData(data, buf, MIN(listSize, data->hoSize));
	free(buf);
	Py_RETURN_NONE;
}

static PyObject*
core_SetCollapseCoef(PyObject* self, PyObject* args) {
	if (PyTuple_Size(args) != 2) {
		RAISE_PY_ERROR(PyExc_TypeError, "Too many(few) args are passed.");
	}
	PyObject* pyData, * pyList;
	if (!PyArg_ParseTuple(args, "OO", &pyData, &pyList))
	{
		RAISE_PY_ERROR(PyExc_TypeError, "The passed args aren't objects.");
	}
	if (!PyList_CheckExact(pyList)) {
		RAISE_PY_ERROR(PyExc_TypeError, "The second arg isn't a strict list.");
	}
	pDeriveData data;
	CheckArgsDData(pyData, &data);
	int listSize = PyList_Size(pyList);
	Complex* buf = (Complex*)malloc(data->coSize * sizeof(Complex)); ASSERTNULL(buf);
	memset(buf, 0, data->coSize * sizeof(Complex));
	for (int i = 0; i < MIN(listSize, data->coSize); ++i) {
		PyObject* temp = PyList_GetItem(pyList, i);
		if (PyComplex_CheckExact(temp)) {
			buf[i].real = PyComplex_RealAsDouble(temp);
			buf[i].image = PyComplex_ImagAsDouble(temp);
		}
		else if (PyFloat_Check(temp)) {
			buf[i].real = PyFloat_AsDouble(temp);
			buf[i].image = 0.0;
		}
		else if (PyLong_Check(temp)) {
			buf[i].real = PyLong_AsDouble(temp);
			buf[i].image = 0.0;
		}
		else {
			RAISE_PY_ERROR(PyExc_TypeError, "The stuff in the list aren't complexes or longs or floats.");
		}
	}
	SetCOCoefOfDData(data, buf, MIN(listSize, data->coSize));
	free(buf);
	Py_RETURN_NONE;
}

static PyObject*
core_GetCurrentValue(PyObject* self, PyObject* args) {
	PyObject* pyData = NULL;
	if (PyTuple_Size(args) != 1) {
		RAISE_PY_ERROR(PyExc_TypeError, "Too many args are passed.");
	}
	if (!PyArg_ParseTuple(args, "O", &pyData)) {
		RAISE_PY_ERROR(PyExc_TypeError, "The passed arg isn't a object.");
	}
	pDeriveData data = NULL;
	CheckArgsDData(pyData, &data);

	PyObject* ansList = PyList_New(data->size);
	for (int i = 0; i < data->size; ++i) {
		PyList_SetItem(ansList, i, PyComplex_FromDoubles(data->curValues[i].real, data->curValues[i].image));
	}

	return ansList;
}

static PyObject*
core_GetHamiltonCoef(PyObject* self, PyObject* args) {
	PyObject* pyData = NULL;
	if (PyTuple_Size(args) != 1) {
		RAISE_PY_ERROR(PyExc_TypeError, "Too many args are passed.");
	}
	if (!PyArg_ParseTuple(args, "O", &pyData)) {
		RAISE_PY_ERROR(PyExc_TypeError, "The passed arg isn't a object.");
	}
	pDeriveData data = NULL;
	CheckArgsDData(pyData, &data);

	if (data->size == 0) {
		RAISE_PY_ERROR(PyExc_RuntimeError, "The data is empty.");
	}
	PyObject* ansList = PyList_New(data->hoSize);
	for (int i = 0; i < data->hoSize; ++i) {
		PyList_SetItem(ansList, i, PyComplex_FromDoubles(data->hoCoefs[i].real, data->hoCoefs[i].image));
	}

	return ansList;
}

static PyObject*
core_GetCollapseCoef(PyObject* self, PyObject* args) {
	PyObject* pyData = NULL;
	if (PyTuple_Size(args) != 1) {
		RAISE_PY_ERROR(PyExc_TypeError, "Too many args are passed.");
	}
	if (!PyArg_ParseTuple(args, "O", &pyData)) {
		RAISE_PY_ERROR(PyExc_TypeError, "The passed arg isn't a object.");
	}
	pDeriveData data = NULL;
	CheckArgsDData(pyData, &data);

	if (data->size == 0) {
		RAISE_PY_ERROR(PyExc_RuntimeError, "The data is empty.");
	}
	PyObject* ansList = PyList_New(data->coSize);
	for (int i = 0; i < data->coSize; ++i) {
		PyList_SetItem(ansList, i, PyComplex_FromDoubles(data->hoCoefs[i].real * 2, data->hoCoefs[i].image * 2));
	}

	return ansList;
}

static PyObject*
core_UpdateInitialState(PyObject* self, PyObject* args) {
	if (PyTuple_Size(args) != 2) {
		RAISE_PY_ERROR(PyExc_TypeError, "Too many(few) args are passed.");
	}
	PyObject* pyData, * pyList;
	if (!PyArg_ParseTuple(args, "OO", &pyData, &pyList))
	{
		RAISE_PY_ERROR(PyExc_TypeError, "The passed args aren't objects.");
	}
	if (!PyList_CheckExact(pyList)) {
		RAISE_PY_ERROR(PyExc_TypeError, "The second arg isn't a strict list.");
	}
	pDeriveData data;
	CheckArgsDData(pyData, &data);
	int listSize = PyList_Size(pyList);
	int* buf = (int*)malloc(listSize * sizeof(int)); ASSERTNULL(buf);
	memset(buf, 0, listSize * sizeof(int));
	for (int i = 0; i < listSize; ++i) {
		PyObject* temp = PyList_GetItem(pyList, i);
		if (PyLong_Check(temp)) {
			buf[i] = PyLong_AsDouble(temp);
		}
		else {
			RAISE_PY_ERROR(PyExc_TypeError, "The stuff in the list aren't longs.");
		}
	}
	UINT_L trackBuf[MAX_OPERATOR_LENGTH];
	Complex* ans = (Complex*)malloc(data->size * sizeof(Complex)); ASSERTNULL(ans);
	memset(ans, 0, data->size * sizeof(Complex));
	for (int i = 0; i < data->size; ++i) {
		pOPNode nowTrack = data->trackNodes[i];
		int nowArrLen = GetRoot(data->trackNodes[i], NULL);
		ArrayFromNode(nowTrack, nowArrLen, trackBuf);
		double temp;
		InitialValue(trackBuf, nowArrLen, buf, listSize, &temp);
		ans[i].real = temp;
	}
	// memcpy(data->curValues, ans, data->size * sizeof(Complex));
	SetCurrentValueOfDData(data, ans, data->size);

	PyObject* ansList = PyList_New(data->size);
	for (int i = 0; i < data->size; ++i) {
		PyList_SetItem(ansList, i, PyComplex_FromDoubles(ans[i].real, ans[i].image));
	}

	free(ans);
	free(buf);
	return ansList;
}

#ifdef __TREEDEBUG__
static PyObject*
core_PrintData(PyObject* self, PyObject* args) {
	PyObject* pyData = NULL;
	if (PyTuple_Size(args) != 1) {
		RAISE_PY_ERROR(PyExc_TypeError, "Too many args are passed.");
	}
	if (!PyArg_ParseTuple(args, "O", &pyData)) {
		RAISE_PY_ERROR(PyExc_TypeError, "The passed arg isn't a object.");
	}
	pDeriveData data = NULL;
	CheckArgsDData(pyData, &data);

	printf("---------------------------\n");
	UINT_L buf[MAX_OPERATOR_LENGTH];
	printf("Tracking Nodes:\n");
	for (int i = 0; i < data->size; ++i) {
		int len = GetRoot(data->trackNodes[i], NULL);
		ArrayFromNode(data->trackNodes[i], len, buf);
		printf("Nodes[%d]:  {%d", i, (int)buf[0]);
		for (int j = 1; j < len; ++j)
			printf(", %d", (int)buf[j]);
		printf("}\n");
	}
	printf("---------------------------");
	printf("\n\n\n");

	for (int i = 0; i < data->size; ++i) {
		printf("Tracking Operator %d :\n", i);
		for (int j = 0; j < data->hoSize; j++) {
			printf("HO_Tree %d, coef is %.3lf+(%.3lf)j:\n", j, 
				data->hoCoefs[j].real, data->hoCoefs[j].image);
			PrintOPTree(data->evoTrees_HO[i][j]);
			putchar('\n');
		}
		putchar('\n');
		for (int j = 0; j < data->coSize; j++) {
			printf("CO_Tree %d:, coef is %.3lf+(%.3lf)j:\n", j,
				data->coCoefs[j].real, data->coCoefs[j].image);
			PrintOPTree(data->evoTrees_CO[i][j]);
			putchar('\n');
		}
		printf("---------------------------");
		printf("\n\n\n");
	}

	Py_RETURN_NONE;
}
#endif // __TREEDEBUG__


static PyMethodDef coreMethods[] = {
	{"DeriveAssign",  core_DeriveAssign, METH_VARARGS, NULL},
	{"CalEvolution",  core_CalEvolution, METH_VARARGS, NULL},
	{"SetCurrentValue",  core_SetCurrentValue, METH_VARARGS, NULL},
	{"GetCurrentValue",  core_GetCurrentValue, METH_VARARGS, NULL},
	{"SetHamiltonCoef",  core_SetHamiltonCoef, METH_VARARGS, NULL},
	{"SetCollapseCoef",  core_SetCollapseCoef, METH_VARARGS, NULL},
	{"GetHamiltonCoef",  core_GetHamiltonCoef, METH_VARARGS, NULL},
	{"GetCollapseCoef",  core_GetCollapseCoef, METH_VARARGS, NULL},
	{"UpdateInitialState",  core_UpdateInitialState, METH_VARARGS, NULL},
#ifdef __TREEDEBUG__
	{"PrintData",  core_PrintData, METH_VARARGS, NULL},
#endif // __TREEDEBUG__

	{NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef coreModule = {
	PyModuleDef_HEAD_INIT,
	"core",		/* name of module */
	"The core for QCLSolver.",			/* module documentation, may be NULL */
	-1,				/* size of per-interpreter state of the module,
						or -1 if the module keeps state in global variables. */
	coreMethods
};

PyMODINIT_FUNC
PyInit_core(void) {
	return PyModule_Create(&coreModule);
}