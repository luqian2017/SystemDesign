/*
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

*/



class TinyUrl2 {
public:
    TinyUrl2() : counter(0) {

    }
    /*
     * @param long_url: a long url
     * @param key: a short key
     * @return: a short url starts with http://tiny.url/
     */
    string createCustom(string &long_url, string &key) {

        string short_url = short_url_header + key;

        if (key_to_long.find(key) != key_to_long.end()) {
            if (key_to_long[key] == long_url)
                return short_url;  
            else    
                return "error";    
        }

        if (long_to_key.find(long_url) != long_to_key.end()) {
            if (long_to_key[long_url] == key)
                return short_url;
            else    
                return "error";
        }

        key_to_long[key] = long_url;
        long_to_key[long_url] = key;

        return short_url;
    }

    /*
     * @param long_url: a long url
     * @return: a short url starts with http://tiny.url/
     */
    string longToShort(string &long_url) {
        if (long_to_key.find(long_url) != long_to_key.end())
            return short_url_header + long_to_key[long_url];

        string key = idToKey(counter);
        long_to_key[long_url] = key;
        counter++;

        key_to_long[key] = long_url;
        return short_url_header + key;
    }

    /*
     * @param short_url: a short url starts with http://tiny.url/
     * @return: a long url
     */
    string shortToLong(string &short_url) {
        string key = short_url.substr(short_url_header.size(), short_url.size());

        if (key_to_long.find(key) != key_to_long.end()) {
            return key_to_long[key];
        }

        //补全， important!!!
        if (key_to_long.find(key) != key_to_long.end()) {
            return key_to_long[key];
        }

        return "";
    }

private:
    //there exists a one-to-one mapping between ID and shortURL, 
    //but no one-to-one mapping between shortURL and longURL
    //str = "abc"   str[0]='a', str[2]='c'

    long long keyToId(string key) {
        long long id = 0;
        for (int i = 0; i < key.size(); ++i) {
            id = id * 62 + convert(key[i]);
        }
        return id;
    }


    string idToKey(long long id) {
        string charSet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";  
        string key;
        while (id > 0) {
            key = charSet[id % 62] + key; //should not use key+=charSet[id%62] !
            id /= 62;
        } 

        //important, add padding chars if key's length is < 6
        while (key.size() < 6) {
            key = "0" + key;
        } 

        return key;    
    }

    int convert(char c) {
        //Note: it is not pure ASCII code, so cannot use c - '0' for all cases
        //charSet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"  
        if ((c >= '0') && (c <= '9')) return c - '0';
        if ((c >= 'a') && (c <= 'z')) return c - 'a' + 10;
        if ((c >= 'A') && (c <= 'Z')) return c - 'A' + 36;

    }

    int counter;
    const string short_url_header = "http://tiny.url/";
    map<string, string> key_to_long;
    map<string, string> long_to_key;

};