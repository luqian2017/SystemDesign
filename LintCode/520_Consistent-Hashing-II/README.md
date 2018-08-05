
注意:

1) 用一个map< int, int >来存储id和machine之间的映射关系。注意不能用map< int, vector<int> > 来存储一个machine和一串id，这样就没法找某个id对应哪个machine了。

2) 还要 用一个set<int>来存储已经用过的id。

3) map和set的key都是默认从大到小排序的。 记得lower_bound()这个函数非常非常有用！ map和set都可以用！
