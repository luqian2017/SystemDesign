
class Memcache {
public:
    class Node {
        public:
            Node(int v = 0, int t = 0) : value(v), timeout(t) {}
            int value;
            int timeout;
    };
    
    /*
     * @param curtTime: An integer
     * @param key: An integer
     * @return: An integer
     */
    int get(int curtTime, int key) {
        if ((hashmap.find(key) == hashmap.end()) || 
            ((curtTime > hashmap[key].timeout) && (hashmap[key].timeout > 0))) {
            return INT_MAX;
        }

        return hashmap[key].value;    
    }

    /*
     * @param curtTime: An integer
     * @param key: An integer
     * @param value: An integer
     * @param ttl: An integer
     * @return: nothing
     */
    void set(int curtTime, int key, int value, int ttl) {
        Node node(value, 0);
        
        //if ttl = 0, timeout is already set as 0 in default constructor.
        if (ttl != 0) {
            node.timeout = curtTime + ttl - 1;
        }
    
        hashmap[key] = node;
    }


    /*
     * @param curtTime: An integer
     * @param key: An integer
     * @return: nothing
     */
    void del(int curtTime, int key) {
        if (hashmap.find(key) != hashmap.end()) {
            hashmap.erase(key);
        }
    }

    /*
     * @param curtTime: An integer
     * @param key: An integer
     * @param delta: An integer
     * @return: An integer
     */
    int incr(int curtTime, int key, int delta) {
        if (hashmap.find(key) == hashmap.end()) 
            return INT_MAX;
        
        if ((curtTime > hashmap[key].timeout) && (hashmap[key].timeout > 0))
            return INT_MAX;
            
        hashmap[key].value += delta;
        return hashmap[key].value;
    }

    /*
     * @param curtTime: An integer
     * @param key: An integer
     * @param delta: An integer
     * @return: An integer
     */
    int decr(int curtTime, int key, int delta) {
        if (hashmap.find(key) == hashmap.end()) 
            return INT_MAX;

        if ((curtTime > hashmap[key].timeout) && (hashmap[key].timeout > 0))
            return INT_MAX;
        
        hashmap[key].value -= delta;
        return hashmap[key].value;
    }
  
private:
    map<int, Node> hashmap;  
};