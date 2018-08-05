
这题与Tiny Url II的区别是它要求没有那么严格，不需要生成全局唯一的id。
这两种方案区别如下：

Tiny Url: 
    long_url <-(256Base mapping)-> id <-(62Base mapping)-> short_key

Tiny Url II:
    long_url <-(system generate unique)-> id <-(62Base mapping)-> short_key

这里的short\_key就是short\_url去掉那个固定头。

具体来说：
1)Tiny Url里面是把long_url通过256 Base转换成一个(long long) id，再把这个id跟short_key通过62 Base 一一对应。要注意long_url和id不一定是一一对应的，所以要加个while循环来检查该id是不是已经用过。而id与short_key的62 Base是严格的一一对应的。

2) Tiny Url II里面long_url和id之间是严格一一对应的，因为是系统生成的全局唯一id。 short_key和id之间也是严格一一对应。
