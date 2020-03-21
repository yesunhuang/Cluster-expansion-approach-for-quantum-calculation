function dydt = convert(t,y,data,tsize)
    y_s=libpointer('doublePtr',y);
    calllib('dsdll', 'cedll_SetCurrentValue', data, y_s, tsize*2);
    ansArr = rand(1, tsize*2);
    p=libpointer('doublePtr', ansArr);
    calllib('dsdll', 'cedll_CalEvolution', data,p);
    dydt=p.Value;
    dydt=reshape(dydt,tsize*2,1);
end
