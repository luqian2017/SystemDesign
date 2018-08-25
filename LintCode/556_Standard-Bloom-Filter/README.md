参考的网上的答案。

Note:
1) Bloom Filter的add()的主要思想是用多个hash方程来将输入map到bit串中的若干位，并对这些位都设1。
contains()的主要思想是用多个hash方程将输入map到bit串中的若干位，若这些位都为1，则返回true；有一个或多位为0，则返回false。
用一句话来总结Bloom Filter的主要思想就是：全真未必真，有假必定假。 

2) hash方程的cap和seed可以随意。seed越大则map得越均匀。

3) stl的bitset很好用。bitset<200000>是设一个200000位的bit串。 bitset.set(100)是将第100位置1。
```