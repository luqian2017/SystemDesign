
不能指望把一个long_url hash成一个6位字符串，因为6位字符串太短，所以会有大量重复。 
解法是把short_url map成一个id (基于62)，这样short_url和id是严格的一一对应了，可以互相编解码出来。那long_url又怎么和short_url或id来对应呢？答案是用系统生成的唯一的一个counter来对应。每生成一个long_url，count++。根据这个系统唯一counter，可以找到对应的short_url。 
程序里面用了2个map:

    map<string, string> key_to_long;
    map<string, string> long_to_key;

这里key就相当于short_url(去掉了那个固定的头)。 
那为什么不需要long_to_id或id_to_long呢?因为key和id是一一对应的，有了long和key对应的map就行了。

注意： 
1) id要用long long，若用int肯定溢出 
2) key不足6位要补全 
3) 62 进制转换对字符串处理很重要。但注意必须用到convert函数，而不能直接用c-‘0‘将char转换成对应数值。因为c-‘0’只有对ASCII码才有效，而62进制跟ASCII不一致（ASCII码里面还加了一个其他字符） 
4) key = charSet[id % 62] + key 不可以写成 
key+=charSet[id%62] 
5) 62进制只处理数字和字母，所以short_url_header必须去掉，直接处理key即可，同时也省下了很多处理short_url_header的时间 .

