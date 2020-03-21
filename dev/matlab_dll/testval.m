global data
% 加载.dll库
[notfound,warnings] = loadlibrary('dsdll','dllwrapper.h');

% 定义变量
ho_arr = [1, 2, 3, 4, 1,1,4,2,2,3,1,2 ];
ho_coef = [0.8,1.6,2.0,2.0,8.831,8.831,0.0,0.0,0.0,0.0,0.0,0.0];
ho_size_arr = [2, 2,3,3,1,1];
ho_size = 6;

co_arr = [2,4];
co_coef = [2.0,4.0,0.0,0.0];
co_size_arr = [1, 1];
co_size = 2;

track_arr = [1, 2, 3, 4];
track_size_arr = [2, 2,0,0];
track_size = 2;

maxOPLen = 5;

% 获得data
data = calllib('dsdll', 'cedll_DeriveAssign', ...
libpointer('int32Ptr', ho_arr), libpointer('doublePtr', ho_coef), libpointer('int32Ptr', ho_size_arr), ho_size,... 
libpointer('int32Ptr', co_arr), libpointer('doublePtr', co_coef), libpointer('int32Ptr', co_size_arr), co_size,...
libpointer('int32Ptr', track_arr), libpointer('int32Ptr', track_size_arr), track_size, maxOPLen);

% 获得track算符的数量
tsize = calllib('dsdll', 'cedll_GetTrackingTreeSize', data);

% 设置current value
y0 = zeros(1,tsize*2,'double'); 	% 改变前三项的current value
tspan=[0 10];
%[t,y] = ode15s(@(t,y) convert(t,y,data,tsize), tspan, y0);
%plot(t,y(:,1),'-o',t,y(:,2),'-.');
% 获得CalEvolution值
%ansArr = rand(1, tsize*2);	% 创建存储的数组
%p=libpointer('doublePtr', ansArr);
%ansArr=calllib('dsdll', 'cedll_CalEvolution', data,p);
% 之后，ansArr中即为calEvolution的答案，采用实虚分离数组形式表达
%print(ansArr)
%calllib('dsdll', 'cedll_Destroy', data);
