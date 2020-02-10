# 配置说明

### 配置环境

* Python 3.7及以上(低版本暂未测试)

### 配置步骤

1. 运行同目录下的setup.bat脚本

### import方式

```python
import cluster
```

### API说明

#### 1. DeriveAssign(...)方法

```python
cluster.DeriveAssign([Initial状态], [Hamilton算符...], [Hamilton算符系数], 
       [Collapse算符...], [Collapse算符系数], [Tracking算符...], 最长算符长度)
```

参数说明: 

* \[Initial状态\]: 一个表示初始状态量的list。例如$1,2,0,3$表示算符中$\{1,2\}$的初始量为1，$\{3,4\}$的初始量为2，$\{5,6\}$的初始量为0，$\{7,8\}$的初始量为3。
* \[Hamilton算符...\]: 含有多个Hamilton算符的列表。例如，两个个Hamilton算符表示为$[1,2,3,4]$ ，$[2,1]$，则\[Hamilton算符...\]为$[[1,2,3,4],[2,1]]$
* \[Hamilton算符系数\]: 含有上述Hamilton算符的系数的列表，系数由Python中的Complex类型表示。例如，两个个Hamilton算符表示为$[1,2,3,4]$ ，$[2,1]$，其系数分别为$1+i$和$-1$，则\[Hamilton算符系数\]为$[1+i,-1]$
* \[Collapse算符...\]: 类似于上面。
* \[Collapse算符系数\]: 类似于上面
* \[Tracking算符...\]: 类似于上面
* 最长算符长度: 字面意思

返回值：

* 含有上述信息的DeriveData对象

#### 2. CalEvolution(DeriveData data)方法

```python
cluster.CalEvolution(data)
```

参数说明：

* data: DeriveAssign(...)方法产生的DeriveData对象

返回值: 

* 含有计算结果的一个list

#### 3. SetCurrentValue(DeriveData data, PyList list)

```python
cluster.SetCurrentValue(data, list)
```

参数说明：

* data: DeriveAssign(...)方法产生的DeriveData对象
* list: 新的初值的list。初值设置的个数取决于data中

返回值：

* 无

