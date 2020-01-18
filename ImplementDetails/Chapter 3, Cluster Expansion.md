# Cluster Expansion

> *Cluster Expansion* process is the key part of the calculator, but with the help of the fascinating data structure, it is not hard to implement.

## Introduction

> In order to calculate the evolution of the ensemble average of certain operator basing on the *Lindblad master equation*, we need to know the ensemble average of  the higher order term, which make it inevitable to solve infinite system of differential equations. However, with the help of *Cluster Expansion* approach, we are able to make some approximation and simplfy the problem.
>
> Here is the simple introduction to the recursive defination of cluster expansion process:
> $$
> <N>=<N>_s
> 	\\+<N-2>_s\Delta<2>\\+<N-3>_s\Delta<3>\\+<N-4>_s\Delta<4>+<N-4>\Delta<2>\Delta<2>
> 	\\+...
> 	\\+\Delta<N>
> $$
> where each product term represents one factorization symbolically and implicitly includes a sum over all factorizations within the class of terms identified. The purely correlated part is denoted by the last term. By obmitting the last term, we are able to make good approximation and avoid solving infinite system of differential equations.

##  Problem

> Given an operator consist of n **basic operators**, use the cluster expansion approach to decompose it into a set of operators consist of no more than n-1 basic operators.
>
> For example:
> $$
> <aaa>=3<a><aa>-<a>^3\\
> <abc>=<a><bc>+<b><ac>+<c><ab>-3<a><b><c>
> $$
>
> Output the decomposed result in the form of operator tree.

## Solution

>