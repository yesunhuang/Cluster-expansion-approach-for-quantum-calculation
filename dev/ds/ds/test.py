import cluster

Initial=[0,0]
Hamilton=[[1,2],[3,4],[1,1,4],[2,2,3],[1],[2]]
print(Hamilton)
Hc=[0.8,0.6,0.333,0.333,0.106,0.106]
print(Hc)
Co_ps=[[2],[4]]
print(Co_ps)
Cc=[complex(2),complex(4)]
print(Cc)
T_o=[[1,2],[3,4]]
print(T_o)

data=cluster.DeriveAssign(Initial,Hamilton,Hc,Co_ps,Cc,T_o,2)
cluster.PrintData(data)
#cluster.SetCurrentValue(data, [0.8,0.6,0.333,0.333,0.106,0.106])
#print(cluster.CalEvolution(data))