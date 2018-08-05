

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