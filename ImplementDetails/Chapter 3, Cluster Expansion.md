# Cluster Expansion

> *Cluster Expansion* process is the key part of the calculator, but with the help of the fascinating data structure, it is not hard to implement.

## Introduction

> In order to calculate the evolution of the ensemble average of certain operator basing on the *Lindblad master equation*, we need to know the ensemble average of  the higher order term, which make it inevitable to solve infinite system of differential equations. However, with the help of *Cluster Expansion* approach, we are able to make some approximation and simplify the problem.
>
> Here is the simple introduction to the recursive definition of cluster expansion process:
> $$
> <N>=<N>_s
> 	\\+<N-2>_s\Delta<2>\\+<N-3>_s\Delta<3>\\+<N-4>_s\Delta<4>+<N-4>\Delta<2>\Delta<2>
> 	\\+...
> 	\\+\Delta<N>
> $$
> where each product term represents one factorization symbolically and implicitly includes a sum over all factorizations within the class of terms identified. The purely correlated part is denoted by the last term. By omitting the last term, we are able to make good approximation and avoid solving infinite system of differential equations.

##  Problem

> Given an operator consist of n **basic operators**, use the cluster expansion approach to decompose it into a set of operators consist of no more than n-1 basic operators.
>
> For example:
> $$
> <aaa>=3<a><aa>-2<a>^3\\
> <abc>=<a><bc>+<b><ac>+<c><ab>-2<a><b><c>
> $$
>
> Output the decomposed result in the form of operator tree.

## Solution

### Basic Idea

>Consider a simple condition of the problem where all the basic operators in a single operator are different. In that way, the problem reduce to a well-known model: finding all different ways to put n different balls in n same boxes. By assuming that the boxes with one ball represent single basic operator factorization, boxes with  m(>1) balls represent the m-basic-operators correlations terms. It is not difficult to figure out that each distribution way of the balls represent one certain term in the cluster expansion.
>
>By applying the theory of *Bell*, the total number of the terms in n-length-operator cluster expansion is
>$$
>B_n 
>$$
>where *B_i* is the *Bell Number*.
>
>And the recursion formula of *Bell Number* is
>$$
>B_{n+1}=\Sigma_{k=0}^nC_{n}^{n-k}B_k
>$$
>Following the instruction of this formula, we can use recursion technique to calculate *cluster expansion*.

### Tree representation

> We will use two kind of trees in the recursion process. One is the *B-Tree*, corresponding to the right side of the cluster-expansion equation. The other is the *Delta-Tree*, which represent the expression of Delta<N> where:
> $$
> \Delta<N>=<N>-<N>_s-<N-2>_s\Delta<2>-<N-3>_s\Delta<3>-...
> $$
> By assuming the operator with no '0' element in array representation refers to Delta<N> in B-Tree but <N> in delta tree, it is obvious that if we set all the coefficients in *B-Tree* to their opposite number except for this operator, we can generate the corresponding *Delta-Tree*.

### Combination

> 

