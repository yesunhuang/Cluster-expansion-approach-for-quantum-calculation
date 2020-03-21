global data
% ����.dll��
[notfound,warnings] = loadlibrary('dsdll','dllwrapper.h');

% �������
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

% ���data
data = calllib('dsdll', 'cedll_DeriveAssign', ...
libpointer('int32Ptr', ho_arr), libpointer('doublePtr', ho_coef), libpointer('int32Ptr', ho_size_arr), ho_size,... 
libpointer('int32Ptr', co_arr), libpointer('doublePtr', co_coef), libpointer('int32Ptr', co_size_arr), co_size,...
libpointer('int32Ptr', track_arr), libpointer('int32Ptr', track_size_arr), track_size, maxOPLen);

% ���track���������
tsize = calllib('dsdll', 'cedll_GetTrackingTreeSize', data);

% ����current value
y0 = zeros(1,tsize*2,'double'); 	% �ı�ǰ�����current value
tspan=[0 10];
%[t,y] = ode15s(@(t,y) convert(t,y,data,tsize), tspan, y0);
%plot(t,y(:,1),'-o',t,y(:,2),'-.');
% ���CalEvolutionֵ
%ansArr = rand(1, tsize*2);	% �����洢������
%p=libpointer('doublePtr', ansArr);
%ansArr=calllib('dsdll', 'cedll_CalEvolution', data,p);
% ֮��ansArr�м�ΪcalEvolution�Ĵ𰸣�����ʵ�����������ʽ���
%print(ansArr)
%calllib('dsdll', 'cedll_Destroy', data);
