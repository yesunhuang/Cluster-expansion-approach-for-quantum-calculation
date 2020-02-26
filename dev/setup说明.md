# 使用说明

### 配置环境

* Matlab


### 配置步骤

1. 首先将dsdll.dll与dllwrapper.h放在.m脚本同目录下，进入.m文件，加入以下代码以加载动态链接库

```matlab
[notfound,warnings] = loadlibrary('dsdll','dllwrapper.h');  %加载.dll库
```

2. 之后便可以开始调用函数

### 函数通用调用方式说明

对于dll文件中的任意函数，假设其形式为

```c
ReturnType Function(ParType1 p1, ParType2 p2, ..., ParTypeN pN);
```

则在matlab中，其调用方式为使用calllib函数调用，例如

```matlab
sth = calllib('dsdll', 'Funtion', p1, p2, ..., pN);
```

**注意，由matlab传入c的参数类型，一定要严格符合dll函数原型中的参数类型**

### dll文件中函数原型

现在列出dll文件中的函数原型：

```c
typedef unsigned long long M_DATAPOINTER;

int cedll_CalEvolution(M_DATAPOINTER dataPtr, double* outputArr);

M_DATAPOINTER cedll_DeriveAssign(
    int* ho_arr, double* ho_coef, int* ho_size_arr, int ho_size, 
    int* co_arr, double* co_coef, int* co_size_arr, int co_size, 
    int* track_arr, int* track_size_arr, int track_size, 
    int maxOPLen);

int cedll_Destroy(M_DATAPOINTER dataPtr);

int cedll_GetCurrentValue(M_DATAPOINTER dataPtr, double* outputArr, int arrSize);
int cedll_GetHamiltonCoef(M_DATAPOINTER dataPtr, double* outputArr, int arrSize);
int cedll_GetCollapseCoef(M_DATAPOINTER dataPtr, double* outputArr, int arrSize);
int cedll_GetTrackingTreeSize(M_DATAPOINTER dataPtr);

int cedll_SetCurrentValue(M_DATAPOINTER dataPtr, double* inputArr, int arrSize);
int cedll_SetHamiltonCoef(M_DATAPOINTER dataPtr, double* inputArr, int arrSize);
int cedll_SetCollapseCoef(M_DATAPOINTER dataPtr, double* inputArr, int arrSize);

int cedll_UpdateInitialValue(M_DATAPOINTER dataPtr, int* init_arr, int arrSize);

```



### API说明

#### 1.  DeriveAssign(...)

函数原型：

```c
M_DATAPOINTER cedll_DeriveAssign(
    int* ho_arr, double* ho_coef, int* ho_size_arr, int ho_size, 
    int* co_arr, double* co_coef, int* co_size_arr, int co_size, 
    int* track_arr, int* track_size_arr, int track_size, 
    int maxOPLen);
```

参数说明：

* ho_arr：不同于以往，在matlab中，这个数组中须为严格的整数。同时，hamilton算符采取数组形式的输入。再者，由于采用一维数组代替二维数组，现在其输入方式略有改变。例如，对于三个H算符，$[1,2,3,4]$ ，$[2,1]$，$[5,6,7]$，则现在只需将其全部组合起来，即为ho_arr，即ho_arr为$[1,2,3,4,2,1,5,6,7]$。
* ho_coef：H算符的系数输入，相比以前，有大改动。ho_coef数组的前半部分，存储系数的实数部分；后半部分，存储系数的虚数部分。例如，对于三个H算符系数$3+4i$和$-1$和$-2i$，现在其ho_coef为$[3.0,-1.0,0.0,4.0,-1.0,-2.0]$，今后我将其称为***实虚分离数组***形式，注意须强制为小数类型。
* ho_size_arr：由于ho_arr的输入转为一维数组，因此需要知道每个H算符的长度，以还原真正的H算符。对于上述的H算符，现在其ho_size_arr为$[4,2,3]$
* ho_size：H算符的个数。对于上述的例子，ho_size为3
* C算符和T算符的输入，请聪明的读者类比于H算符
* maxOPLen：跟以前一样

返回参数：

* 调用函数后，会返回一个在Matlab中表示为uint64类型的数据，此实际为C语言中的一个指针类型，**请勿随意更改，否则将导致程序崩溃**
* 该返回值将作为其他函数中的***dataPtr***参数使用。

#### 2. CalEvolution(...)

函数原型：

```c
int cedll_CalEvolution(M_DATAPOINTER dataPtr, double* outputArr);
```

参数说明：

* dataPtr：由DeriveAssign函数产生的指针。
* outputArr：在matlab中，传入的**拥有足够空间的数组（请自行预先分配空间）**的指针，结果采用***实虚分离数组***形式表达，故注意大小应为data中tracking算符数目的两倍。

返回值：

* 恒为1

#### 3. GetCurrentValue(...)

函数原型：

```c
int cedll_GetCurrentValue(M_DATAPOINTER dataPtr, double* outputArr, int arrSize);
```

参数说明：

* dataPtr：由DeriveAssign函数产生的指针。
* outputArr：在matlab中，传入的**拥有足够空间的数组（请自行预先分配空间）**的指针，结果采用***实虚分离数组***形式表达。
* arrSize：分配好的数组的大小，理论上建议应为tracking算符数目的两倍。否则，只读取tracking算符中的前$\lfloor \frac{arrSize}{2} \rfloor$个的current value写入数组中。

返回值：

* 恒为1

#### 4. GetTrackingTreeSize(...)

函数原型：

```c
int cedll_GetTrackingTreeSize(M_DATAPOINTER dataPtr);
```

参数说明：

* dataPtr：由DeriveAssign函数产生的指针。

返回值：

* 返回data中tracking算符的数量。
* 此函数可用于确定上述某些函数的数组预留大小。

#### 5. SetHamiltonCoef(...)

函数原型：

```c
int cedll_SetHamiltonCoef(M_DATAPOINTER dataPtr, double* inputArr, int arrSize);
```

参数说明：

* dataPtr：由DeriveAssign函数产生的指针。
* inputArr：在matlab中，传入的**拥有足够空间的数组（请自行预先分配空间）**的指针，结果采用***实虚分离数组***形式表达。
* arrSize：分配好的数组的大小，理论上建议应为tracking算符数目的两倍。否则，只写入H算符系数数组中的前$\lfloor \frac{arrSize}{2} \rfloor$个值。

返回值：

* 恒为1

#### 6. UpdateInitialValue(...)

函数原型：

```c
int cedll_UpdateInitialValue(M_DATAPOINTER dataPtr, int* init_arr, int arrSize);
```

作用：

* 根据传入的初态，更新current value值

参数说明：

* dataPtr：由DeriveAssign函数产生的指针。
* init_arr：在matlab中，传入的**拥有足够空间的数组（请自行预先分配空间）**的指针，由于Initial Value为实数，故不用实虚分离。
* arrSize：init_arr的数组大小。

返回值：

* 恒为1

#### 7. SetHamiltonCoef(...)

函数原型：

```c
int cedll_Destroy(M_DATAPOINTER dataPtr);
```

参数说明：

* dataPtr：由DeriveAssign函数产生的指针。

返回值：

* 恒为1

作用：

* 销毁data，释放内存

### Matlab传指针给C的方式

Matlab中，将指针作为参数，传给动态链接库函数，需要以下述形式：

```matlab
% 产生double*（double类型指针）
x = [1.0,2.0,3.0];
p = libpointer('doublePtr', x);

% 产生int*（int32类型指针）
x = [1,2,3];
p = libpointer('int32Ptr', x);
```

另外附上c语言中类型与Matlab中类型的对应表：

![对应表1](.\matlab_dll\对应表1.png)

![对应表2](.\matlab_dll\对应表2.png)

### 完整Matlab程序实例

```matlab
% 加载.dll库
[notfound,warnings] = loadlibrary('dsdll','dllwrapper.h');

% 定义变量
ho_arr = [1, 2, 3, 4, 2, 1, 5, 6, 7];
ho_coef = [3.0, -1.0, 0.0, 4.0, -1.0, -2.0];
ho_size_arr = [4, 2, 3];
ho_size = 3;

co_arr = [1, 2, 3, 4];
co_coef = [2.0, 4.0, 0.0, 0.0];
co_size_arr = [2, 2];
co_size = 2;

track_arr = [1, 2, 3, 4];
track_size_arr = [2, 2];
track_size = 2;

maxOPLen = 3;

% 获得data
data = calllib('dsdll', 'cedll_DeriveAssign', 
libpointer('int32Ptr', ho_arr), libpointer('doublePtr', ho_coef), libpointer('int32Ptr', ho_size_arr), ho_size, 
libpointer('int32Ptr', co_arr), libpointer('doublePtr', co_coef), libpointer('int32Ptr', co_size_arr), co_size, 
libpointer('int32Ptr', track_arr), libpointer('int32Ptr', track_size_arr), track_size, maxOPLen);

% 获得track算符的数量
tsize = calllib('dsdll', 'cedll_GetTrackingTreeSize', data);

% 设置current value
cv = [1.0, 1.0, 1.0, 0.0, 0.0, 0.0]; 	% 改变前三项的current value
calllib('dsdll', 'cedll_SetCurrentValue', data, libpointer('doublePtr', cv), 6);

% 获得CalEvolution值
ansArr = rand(1, tsize);	% 创建存储的数组
calllib('dsdll', 'cedll_CalEvolution', data, libpointer('doublePtr', ansArr));
% 之后，ansArr中即为calEvolution的答案，采用实虚分离数组形式表达
```

