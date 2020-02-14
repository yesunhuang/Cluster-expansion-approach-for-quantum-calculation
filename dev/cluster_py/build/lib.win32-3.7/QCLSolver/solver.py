from QCLSolver.data import Data
import types
from typing import List, Tuple, Any, Union, Dict
import numpy as np
import scipy.integrate
import functools
import copy


def Solve(H, Co_ps, Initial_State, tlist, trackOp, maxOpLen, user_args=None, method='RK45',
          t_eval=None, dense_output=False, events=None, vectorized=False, **options: Dict[Any, Any]):
    # 检查输入正确性, 并返回raw数据
    (HOList, rawHOCoefList, COList, rawCOCoefList) = __CheckAndParse(H, Co_ps, Initial_State, trackOp, maxOpLen)
    # 构造正确的t0, 并传入真正的初值
    t0 = tlist[0]
    HOCoefList0 = []
    COCoefList0 = []
    for stuff in rawHOCoefList:
        if isinstance(stuff, types.FunctionType):
            HOCoefList0.append(stuff(t0))
        else:
            HOCoefList0.append(stuff)
    for stuff in rawCOCoefList:
        if isinstance(stuff, types.FunctionType):
            COCoefList0.append(stuff(t0))
        else:
            COCoefList0.append(stuff)
    ddata = Data(Initial_State, HOList, COList, HOCoefList0, COCoefList0, trackOp, maxOpLen)
    y0c = np.array(ddata.GetCurrentValue())
    n = len(y0c)

    # 复制新的options和user_args
    options_new = None
    if len(options) > 0:
        options_new = copy.copy(options)
    user_args_new = copy.copy(user_args)
    if user_args_new is None:
        user_args_new = ()

    # 包装event
    events_wrapped_copy = None
    if events is not None:
        events_wrapped_copy = Copy_Func(__EventWrapper)
        events_wrapped_copy.terminal = False
        events_wrapped_copy.direction = float(0)
        if hasattr(events, 'terminal'):
            events_wrapped_copy.terminal = events.terminal
        if hasattr(events, 'direction'):
            events_wrapped_copy.direction = events.direction

    # 包装jac
    jac_func = None
    if options_new is not None and options_new.get('jac') is not None \
            and isinstance(options_new.get('jac'), types.FunctionType):
        jac_func = options.get('jac')
        # noinspection PyTypeChecker
        options_new['jac'] = __JacWrapper

    # 包装user_args为args_wrapped, 格式为[ddata, n, rawHOCoefList, rawCOCoefList, events, jac_func, user_args]
    if not isinstance(user_args, tuple) and user_args is not None:
        raise TypeError("Parameter user_args is not a tuple.")
    args_wrapped = (ddata, n, rawHOCoefList, rawCOCoefList, events, jac_func, user_args_new)

    return scipy.integrate.solve_ivp(__ConvertToSolver, tlist, y0c, method=method, t_eval=t_eval,
                                     events=events_wrapped_copy,
                                     dense_output=dense_output, vectorized=vectorized, args=args_wrapped,
                                     options=options_new)


def __CheckAndParse(H, Co_ps, Initial_State, trackOp, maxOpLen):
    # check
    for item in H:
        if not isinstance(item, list) and len(item) != 2:
            raise SyntaxError("Invalid parameter in parameter H.")
        if not isinstance(item[0], str):
            raise TypeError("Invalid types in parameter H.")
        if not isinstance(item[1], complex) and not isinstance(item[1], int) \
                and not isinstance(item[1], float) and not isinstance(item[1], types.FunctionType):
            raise TypeError("Invalid types in parameter H.")
    for item in Co_ps:
        if not isinstance(item, list) and len(item) != 2:
            raise SyntaxError("Invalid parameter in parameter Co_ps.")
        if not isinstance(item[0], str):
            raise TypeError("Invalid types in parameter Co_ps.")
        if not isinstance(item[1], complex) and not isinstance(item[1], int) \
                and not isinstance(item[1], float) and not isinstance(item[1], types.FunctionType):
            raise TypeError("Invalid types in parameter Co_ps.")
    for item in Initial_State:
        if not isinstance(item, complex) and not isinstance(item, int) and not isinstance(item, float):
            raise TypeError("Invalid types in parameter Initial_State.")
    for item in trackOp:
        if not isinstance(item, str):
            raise TypeError("Invalid types in parameter trackOp.")
    if maxOpLen <= 0:
        raise SyntaxError("Parameter maxOpLen must be greater than zero.")
    # parse
    hoList = []
    coList = []
    hoCoefList = []
    coCoefList = []
    for item in H:
        hoList.append(item[0])
        hoCoefList.append(item[1])
    for item in Co_ps:
        coList.append(item[0])
        coCoefList.append(item[1])
    return hoList, hoCoefList, coList, coCoefList


def __ConvertToSolver(t, y, ddata: Data, n, rawHOCoefList, rawCOCoefList, events, jac_func, user_args: Tuple[Any]):
    ddata.SetCurrentValue(y.tolist())
    # 完成时变的系数
    HOCoefList = []
    COCoefList = []
    for stuff in rawHOCoefList:
        if isinstance(stuff, types.FunctionType):
            HOCoefList.append(stuff(t, *user_args))
        else:
            HOCoefList.append(stuff)
    for stuff in rawCOCoefList:
        if isinstance(stuff, types.FunctionType):
            COCoefList.append(stuff(t, *user_args))
        else:
            COCoefList.append(stuff)
    ddata.SetCoefHOList(HOCoefList)
    ddata.SetCoefCOList(COCoefList)
    dydtc = ddata.Calculate()
    return np.asarray(dydtc)


def __EventWrapper(t, y, ddata, n, rawHOCoefList, rawCOCoefList, events, jac_func, user_args: Tuple[Any]):
    return events(t, y, *user_args)


def __JacWrapper(t, y, ddata, n, rawHOCoefList, rawCOCoefList, events, jac_func, user_args: Tuple[Any]):
    return jac_func(t, y, *user_args)


def Copy_Func(f):
    g = types.FunctionType(f.__code__, f.__globals__, name=f.__name__,
                           argdefs=f.__defaults__,
                           closure=f.__closure__)
    g = functools.update_wrapper(g, f)
    g.__kwdefaults__ = f.__kwdefaults__
    return g

Hamilton=[['Aa', 0.8],['Bb',1.6],['AAb',1],['aaB',1],['A',2],['a',2]];print(Hamilton)
Co_ps=[['a',2],['b',4]];print(Co_ps)
T_o=['Aa','Bb'];print(T_o)
sol2=Solve(Hamilton, Co_ps, [0,0], (0,10), T_o, 5)
print('good')