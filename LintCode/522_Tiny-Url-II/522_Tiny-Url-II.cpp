
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