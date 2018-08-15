
class Node {
public:
    Node() : isWord(false) {
        children = vector<Node *>(26, nullptr);
    }

    bool isWord;
    vector<Node*> children;
};

class Trie {
public:
    Trie() {
        root = new Node();
    }

    /*
     * @param word: a word
     * @return: nothing
     */
    void insert(string &word) {
        Node *p = root;
        
        for (int i = 0; i < word.size(); ++i) {
            if (p->children[word[i] - 'a'] == nullptr) {
                p->children[word[i] - 'a'] = new Node();
            }

            p = p->children[word[i] - 'a'];  
        }
        
        p->isWord = true;    
    }

    /*
     * @param word: A string
     * @return: if the word is in the trie.
     */
    bool search(string &word) {
        Node *p = root;
        for (int i = 0; i < word.size(); ++i) {
            if (p->children[word[i] - 'a'] == nullptr)
                return false;
            p = p->children[word[i] - 'a'];    
        }
        
        if (p->isWord) return true;
        else return false;
    }

    /*
     * @param prefix: A string
     * @return: if there is any word in the trie that starts with the given prefix.
     */
    bool startsWith(string &prefix) {
        Node *p = root;
        for (int i = 0; i < prefix.size(); ++i) {
            if (p->children[prefix[i] - 'a'] == nullptr)
                return false;
            p = p->children[prefix[i] - 'a'];    
        }
        return true;       
     }

private: 
    Node* root;
};
