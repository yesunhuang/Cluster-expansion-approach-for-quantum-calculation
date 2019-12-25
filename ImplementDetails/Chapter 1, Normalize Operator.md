## Chapter 1: Normalize Operator

### Single Mode Operators 

#### Problem:

>Given a arbitrary operator consists of  total length of **n** character representing by  

$$
a\space and\space a^{\dagger}
$$

> in arbitrary order  as follows:

$$
\{aa...a^{\dagger}a^{\dagger}...aaa....a^{\dagger}a^{\dagger}....aaa\} (length:m)
$$

> Following the rule of 

$$
[a,a^{\dagger}]=aa^{\dagger}-a^{\dagger}a=1
$$

> Decompose the input operator into several normalized operators which all the 'a^dag's are in front of 'a's . For example:

$$
{aa^{\dagger}a}=a^{\dagger}aa+a
$$

> Output all the normalized operators and their coefficients due to the decomposition process.

#### Solution:

> Regardless of the data structure to be described in the next chapter, we simply assuming that we are able to keep all the normalized operator' s coefficients in an array which can be access in constant time.(This is possible if we are going to use the hash table) 

> **Basic algorithm**:
>
> ​	Consider a normalized operator multiplied by a^dagger on the left. Assuming this operator have **i** 'a' and **j** 'a^dag'. Obviously the new operator can be decomposed into one normalized operator consisting of **i+1** 'a' and **j**  'a^dag', and **j** normalized operators consisting of **i** 'a' and **j-1** 'a^dag'. For example:

$$
a[a^{\dagger}a^{\dagger}aa]=a^{\dagger}a^{\dagger}aaa+2a^{\dagger}aa
$$

> **Solution**:
>
> ​	Basing on the simply algorithm described above, we simply scanning the operator from right to left. Every time we come across 'a', we do the composition process above and keep the result in a queue. 

> * **Step one:**
>
>   Starting from the right, record the current position with variable **i**. we ignore all the 'a' and when we come across the last 'a' , we put the scanned character together as an operator into the queue. And let the a variable **j** record the last 'a' 's position.

> * **Step two:**
>
>   Then, if we come across 'a^dag' , we do nothing. However, if we come across 'a', we out all the **current** operators in the queue. And for every operator, we do the decomposition process described above and add the new operator to the queue if it is not in the queue. (Notice that **i-j-1** tells us the additional 'a^dag' came across since last decomposition.) Besides, update the coefficient. Reset the value of **j** to **i**.

> * **Final step:**
>
>   When the scanning process is finished, use the value of **i** and **j** to out all the operators in the queue  and renew the coefficient.

> Obviously, the time complexity is

$$
O(N^2)
$$



### Multimode Operators

#### Problem:

>Given a arbitrary operator(m modes) consists of  total length of **n** character representing by  

$$
a, a^{\dagger},b,b^{\dagger},c,c^{\dagger}...(2m\space kind\space of\space character)
$$

> in arbitrary order  as follows:

$$
\{aa...a^{\dagger}a^{\dagger}...baab....b^{\dagger}a^{\dagger}....cac^\dagger\} (length:m)
$$

> Following the rule of 

$$
[O_i,O_i^{\dagger}]=O_iO_i^{\dagger}-O_i^{\dagger}O_i=1
$$

> Decompose the input operator into several normalized operators which all the 'O_i^dag's are in front of 'O_i's and all different modes' operators are in alphabetical order.

> Output all the normalized operators and their coefficients due to the decomposition process.

#### Solution:

> * **Step one:**
>
>   Using stable sort method to gather different modes' operators separately.

> * **Step two:**
>
>   For different modes, we do the single mode operators decomposition process and save them in the coefficient array separately.

> * **Final step:**
>
>   Multiply all the operators together based on the distributive law and we get all the normalized operators and their coefficients.