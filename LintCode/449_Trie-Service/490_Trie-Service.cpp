/**
 * Definition of TrieNode:
 * class TrieNode {
 * public:
 *     TrieNode() {}
 *     map<char, TrieNode*> children;
 *     vector<int> top10;
 * };
 */
class TrieService {
private:
    TrieNode* root;

public:
    TrieService() {
        root = new TrieNode();
    }

    TrieNode* getRoot() {
        // Return root of trie root, and 
        // lintcode will print the tree struct.
        return root;
    }

    //important code    
    void insert(string& word, int frequency) {
        TrieNode *p = root;
        for (int i = 0; i < word.size(); ++i) {
            if (p->children.find(word[i]) == p->children.end()) {
                p->children[word[i]] = new TrieNode();
            }
            p = p->children[word[i]];
            helper(p->top10, frequency);
        }
    }
    
    
    //insert to the right place, top10 is sorted from large to small
    void helper(vector<int>& top10, int freq) {
        top10.push_back(freq);
        int top10Size = top10.size();
        if (top10Size == 1) return;
        
        //start from top10Size - 2 as top10Size - 1 is already freq
        for (int i = top10Size - 2; i >= 0; --i) {
            if (top10[i] < top10[i + 1]) {
                int temp = top10[i];
                top10[i] = top10[i + 1];
                top10[i + 1] = temp;
            } else {
                break;
            }
        }
        
        if (top10Size > 10) top10.pop_back();
    }
    
};

