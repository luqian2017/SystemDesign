#include <bitset>

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

class StandardBloomFilter {
public:
    /*
    * @param k: An integer
    */
    StandardBloomFilter(int k) {
       this->k = k;
       for (int i = 0; i < k; ++i) {
           hashVec.push_back(new HashClass(100000 + i, 2 * i + 3));
       }
    }

    /*
     * @param word: A string
     * @return: nothing
     */
    void add(string &word) {
        for (int i = 0; i < k; ++i) {
            bits.set(hashVec[i]->hashFunc(word));
        }
    }

    /*
     * @param word: A string
     * @return: True if contains word
     */
    bool contains(string &word) {
        for (int i = 0; i < k; ++i) {
            if (!bits[hashVec[i]->hashFunc(word)])
                return false;
        }
        return true;
    }

private:
    int k;
    vector<HashClass *> hashVec;
    bitset<200000> bits;
};
