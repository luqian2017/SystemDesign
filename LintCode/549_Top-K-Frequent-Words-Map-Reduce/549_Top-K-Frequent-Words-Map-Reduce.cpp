/**
 * Definition of Input:
 * template<class T>
 * class Input {
 * public:
 *     bool done(); 
 *         // Returns true if the iteration has elements or false.
 *     void next();
 *         // Move to the next element in the iteration
 *         // Runtime error if the iteration has no more elements
 *     T value();
 *        // Get the current element, Runtime error if
 *        // the iteration has no more elements
 * }
 * Definition of Document:
 * class Document {
 * public:
 *     int id; // document id
 *     string content; // document content
 * }
 */
class TopKFrequentWordsMapper: public Mapper {
public:
//Map does not need to touch heap, it is Reducer's duty to manage the heap.
    void Map(Input<Document>* input) {
        // Please directly use func 'output' to output 
        // the results into output buffer.
        // void output(string &key, int value);
        while(!input->done()) {
            stringstream ss;
            string word;
            ss << input->value().content;
            while(ss >> word) output(word, 1);
            input->next();
        }
        
    }
};


class TopKFrequentWordsReducer: public Reducer {
public:
    void setUp(int k) {
        // initialize your data structure here
        this->k = k;
    }

    void Reduce(string &key, Input<int>* input) {
        // Write your code here
        int count = 0;
        while(!input->done()) {
            count += input->value();
            input->next();
        }
        Pair pair(key, count);
//        if (pq.size() < k) {
            pq.push(pair);
//        } else if (pair < pq.top())
            
//        }
        
    }

    void cleanUp() {
        // Please directly use func 'output' to output 
        // the top k pairs <word, times> into output buffer.
        // void output(string &key, int &value);
        int num = 0;
        while(!pq.empty() && num < k) {
            Pair tempPair = pq.top();
            output(tempPair.key, tempPair.count);
            num++;
            pq.pop();
        }

    }
private:
    int k;
    
    struct Pair{
        string key;
        int count;
        Pair(string k, int c) : key(k), count(c) {}
        bool operator < (const Pair & pair2) const {   //max heap
            if (this->count == pair2.count) {
                return this->key > pair2.key;
            }
            return this->count < pair2.count; 
        }
    };
    
    priority_queue<Pair> pq;   //Max-Heap
};
