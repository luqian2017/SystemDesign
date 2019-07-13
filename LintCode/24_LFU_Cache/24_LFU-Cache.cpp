struct Node {
    int key;
    int timestamp;
    Node(int k, int t) : key(k), timestamp(t) {}
    bool operator < (Node & A) {
        return this->timestamp < A.timestamp;
    }
};

bool operator < (const Node & A, const Node & B) {
    return A.timestamp < B.timestamp;
}

class LFUCache {
public:
    /*
    * @param capacity: An integer
    */
    LFUCache(int capacity) : cap(capacity), minFreq(0) {
        freq2set[1] = std::set<Node>();
        timestamp = 0;
    }

    /*
     * @param key: An integer
     * @param value: An integer
     * @return: nothing
     */
    void set(int key, int value) {
        timestamp++;
        if (key2value.find(key) != key2value.end()) {
            key2value[key] = value;
            get(key);
            return;
        }
        
        if (key2value.size() >= cap) {
            //int lowestKey = *(freq2set[minFreq].begin());
            Node firstMinFreqNode = *(freq2set[minFreq].begin());
            freq2set[minFreq].erase(firstMinFreqNode);
            key2value.erase(firstMinFreqNode.key);
            key2freq.erase(firstMinFreqNode.key);
        }
        
        key2value[key] = value;
        minFreq = 1;
        key2freq[key] = 1;
        freq2set[1].insert(Node(key, timestamp));
    }

    /*
     * @param key: An integer
     * @return: An integer
     */
    int get(int key) {
        timestamp++;
        if (key2value.find(key) == key2value.end()) {
            return -1;
        }
        int freq = key2freq[key];
        
        for (auto s : freq2set[freq]) {
            if (s.key == key) freq2set[freq].erase(s);
        }
        
        
        //only when the last minFreq key was deleted, increment minFreq
        if (minFreq == freq && freq2set[minFreq].size() == 0) minFreq++;

        freq++;
        
        key2freq[key] = freq;
        if (freq2set.find(freq) == freq2set.end()) {
            freq2set[freq] = std::set<Node>();
        }
        freq2set[freq].insert(Node(key, timestamp));
        
        return key2value[key];
    }
    
private:
    unordered_map<int, int> key2value; //(key, value)
    unordered_map<int, int> key2freq; //(key, freq)
    unordered_map<int, std::set<Node>> freq2set; //(freq, set of keys)
    
    int cap;
    int minFreq;
    int timestamp;
};