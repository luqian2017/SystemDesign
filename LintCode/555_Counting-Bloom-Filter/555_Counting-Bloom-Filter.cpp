
class HashClass{
public:
    HashClass(int c, int s) : cap(c), seed(s) {}
        
    int hashFunc(string &value) {
        int ret = 0;
        for (int i = 0; i < value.size(); ++i) {
            ret += seed * ret + value[i];
            ret %= cap;
        }
        return ret;
    }
private:
    int cap, seed;
};


class CountingBloomFilter {
public:
    /*
    * @param k: An integer
    */
    CountingBloomFilter(int k) {
        this->k = k;
        for (int i = 0; i < k; ++i) {
            hashVec.push_back(new HashClass(100000 + i, 2 *i + 3));
        }
        bitSets.resize(100000 + k, 0);
    }

    /*
     * @param word: A string
     * @return: nothing
     */
    void add(string &word) {
        for (int i = 0; i < k; ++i) {
            bitSets[hashVec[i]->hashFunc(word)]++;
        }
    }

    /*
     * @param word: A string
     * @return: nothing
     */
    void remove(string &word) {
        for (int i = 0; i < k; ++i) {
            int pos = hashVec[i]->hashFunc(word);
            if (bitSets[pos] > 0)
                bitSets[pos]--;
        }
    }

    /*
     * @param word: A string
     * @return: True if contains word
     */
    bool contains(string &word) {
        for (int i = 0; i < k; ++i) {
            if (!bitSets[hashVec[i]->hashFunc(word)])
                return false;
        }
        return true;
    }

private:
    int k;
    vector<HashClass *> hashVec;
    vector<int> bitSets;
};