# Chapter 2: Operator Tree

>  It describes the data structure we used to implement the calculator. The inspiration came from *trie*s which is widely used in string searching.

## Introduction

> It should be emphasized that the operators to be stored in the operator tree actually refer to the ensemble average of certain operator, that is:

$$
<A>=tr(\rho A)
$$

> Thus <ab> and <a><b> have different meaning in the tree. And we put a '.' in the operator input to distinguish them. For example: <abc><bc> represented in the input is {bc.abc}.

> We use a order tree structure to describe a set of operators and their coefficient. And this structure support several operation which enable us to implement **cluster expansion** process in a efficient way.

## Operator Representation

> **All the operators to be put in the operator tree should be normalized operators. **
>
> **We also consider the high order terms which are produced by the cluster expansion process as single operator, and we always keep different multiplied parts of the operator in length increasing order (Or, we can say, integer increasing order). ** 

> Map all the basic operator to integer and translate the operator into array(or string for less space), use '0' to represent '.'. For example:

$$
a^{\dagger}.c^{\dagger}cba^{\dagger}a->[1,0,5,6,4,1,2]
$$

## Tree Structure

### Node

> Each node contain links that are either null or references to its child. (Maybe there is also a link to its parents .) Obviously, you can use a pointer (or reference) array to store the link, the array length is 2m+1, m is the numbers of modes.(U can improve it and use less space based on the fact that some link is absolutely null due to the property of normalized operator.). 
>
> Besides, each note except for the root is labelled with the integer value which we use to denote basic operators.
>
> Specifically, just like what we did in *tries*, we store the coefficient associated with each operator in the node corresponding to its last number in the array. *nodes with zero coefficients exist to facilitate search in the operator tree and do not correspond to certain operator.* 
>
> Obviously, the max deep of the tree is n, n is the length of the longest operator.

> * Example: 
>
>    	consider a set of operators:
>
>   | operator    | array representation | coefficient |
>   | ----------- | -------------------- | ----------- |
>   | {a^dag a b^dag b c} | [1,2,3,4,6]          | 1           |
>   | {a b^dag b } | [2,3,4]              | 16          |
> 	|{a.b^dag |[2,0,3]|6|
> 	|{a.c.a^dag a}|[2,0,6,0,1,2]|4|
> 	|{a.b.c}|[2,0,4,0,6]|6|
> 	
> 	The tree representation is:
> 	
> 	```mermaid
> 	graph TB
> 	 	id1((root))
> 	 	id1-->id2((1:0))
> 	 	id1-->id3((2:0))
> 	 	id2-->id4((2:0))
> 	 	id4-->id16((3:0))
> 	 	id16-->id17((4:0))
> 	 	id17-->id18((6:1))
> 	 	id3-->id5((0:0))
> 	 	id5-->id8((3:6))
> 	 	id5-->id9((4:0))
> 	 	id5-->id10((6:0))
> 	 	id9-->id11((0:0))
> 	 	id11-->id12((6:6))
> 	 	id10-->id13((0:0))
> 	 	id13-->id14((1:0))
> 	 	id14-->id15((2:4))
> 	 	id3-->id6((3:0))
> 	 	id6-->id7((4:16))
> 	```
> 	
> 	

### Search

> Given a certain normalized operator in form of array, simply scanning the array from left to right and do DFS using the pointer stored in current node' s pointer array. The pointer obviously can be reached in constant time. If we come across a null pointer or the coefficient of the node standing for the last basic operator is zero during the searching, it means that the operator does not exist in the tree. 
>
> The search process can be completed in O(n) time, where n is the length of the given operator.

### Insert

> Given a certain normalized operator and its coefficient, do the search process described above. If the search hit, renew the coefficient. If not, create new node following the branches according to the array form of the operator and store the coefficient in the last node.
>
> The insert process can be completed in O(n) time, where n is the length of the given operator.

### Delete

> To delete a certain operator in the tree need a bit more work. If the last node of the operator is not the leave, we just set its coefficient to zero. If it is the leave, destroy the node and the pointer linked to it, and in the DFS recalling process, we delete all the node way back until we reach the root, the node with none zero coefficient or the node with more than one child.(In lazy version, we can also just set its coefficient to zeros but might result in space wasting)
>
> The delete process can guarantee to be completed in O(n) time and costs O(ln n) on average, where n is the length of the certain operator.

### Multiply

