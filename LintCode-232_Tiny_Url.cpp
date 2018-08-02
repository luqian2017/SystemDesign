
/*
这题与Tiny Url II的区别是它要求没有那么严格，不需要生成全局唯一的id。
这两种方案区别如下：

Tiny Url: 
    long_url <-(256Base mapping)-> id <-(62Base mapping)-> short\_key

Tiny Url II:
    long_url <-(system generate unique)-> id <-(62Base mapping)-> short\_key

这里的short\_key就是short\_url去掉那个固定头。

具体来说：
1)Tiny Url里面是把long\_url通过256 Base转换成一个(long long) id，再把这个id跟short\_key通过62 Base 一一对应。要注意long_url和id不一定是一一对应的，所以要加个while循环来检查该id是不是已经用过。而id与short\_key的62 Base是严格的一一对应的。
2) Tiny Url II里面long_url和id之间是严格一一对应的，因为是系统生成的全局唯一id。 short\_key和id之间也是严格一一对应。
*/

class TinyUrl {
public:
    const long long SIXTY_TWO_POWER_SIX = 56800235584L;
    const string TINYURL = "http://tiny.url/";

     /*
     * @param url: a long url
     * @return: a short url starts with http://tiny.url/
     */
    string longToShort(string &url) {
        long long id = 0;
        for (int i = 0; i < url.size(); ++i) {
            id = (id * 256 + (long long)url[i]) % SIXTY_TWO_POWER_SIX;
        }
        id %= SIXTY_TWO_POWER_SIX;
       
        while (hashmap.find(id) != hashmap.end() && hashmap[id] != url) id++;
        
        hashmap[id] = url;
        return TINYURL + id2ShortKey(id);
    }

    /*
     * @param url: a short url starts with http://tiny.url/
     * @return: a long url
     */
     
    string shortToLong(string &url) {
        string shortKey = url.substr(TINYURL.size());
        //62 based mapping (url -> long long)
        long long id = 0;
        for (int i = 0; i < 6; ++i) {
            char c = shortKey[i];
            if (c >= '0' && c <= '9') id = id * 62 + c - '0';
            if (c >= 'a' && c <= 'z') id = id * 62 + c - 'a' + 10;
            if (c >= 'A' && c <= 'Z') id = id * 62 + c - 'A' + 36;

         }
         return hashmap[id];
    }

private:
    map<int, string> hashmap;  //id to long string
    
    string id2ShortKey(long long id) {
        const string charSets = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string shortKey;
        while (id > 0) {
            shortKey = charSets[id % 62] + shortKey;
            id /= 62;
        }
        
        while (shortKey.size() < 6) {
            shortKey = "0" + shortKey;
        }
        return shortKey;
    }
};