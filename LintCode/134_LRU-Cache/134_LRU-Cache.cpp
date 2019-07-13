class Node {
public:
    Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) { }
    int key, val;
    Node *prev;
    Node *next;
};

class LRUCache {
public:
    /*
    * @param capacity: An integer
    */
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->head = new Node(0, 0);
        this->tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    /*
     * @param key: An integer
     * @return: An integer
     */
    int get(int key) {
        //cout<<"get("<<key<<")"<<endl;
        if (mp.find(key) == mp.end()) return -1;
        
        Node *pNode = mp[key];
        pNode->prev->next = pNode->next;
        pNode->next->prev = pNode->prev;
        moveToTail(pNode);
        return pNode->val;
    }

    /*
     * @param key: An integer
     * @param value: An integer
     * @return: nothing
     */
    void set(int key, int value) {
     //   cout<<"set("<<key<<" , "<<value<<")"<<endl;
        if (mp.find(key) != mp.end()) {
//            mp[key] = new Node(key, valule);
            mp[key]->val = value;
            //maybe we also need to call moveToTail() here?
            mp[key]->prev->next = mp[key]->next;
            mp[key]->next->prev = mp[key]->prev;
            moveToTail(mp[key]);
            return;
        }
        
        if (mp.size() == capacity) {
            mp.erase(head->next->key);    //here we need to use the key field in the Node class
            head->next = head->next->next;
            head->next->prev = head;
        }
        
        Node *pNode = new Node(key,  value);
        mp[key] = pNode;
        moveToTail(pNode);
    }
    
    void moveToTail(Node *p) {
      //  cout<<"...moveToTail()"<<endl;
        p->prev = tail->prev;
        p->next = tail;
        tail->prev->next = p;
        tail->prev = p;

    //    cout<<"...end"<<endl;
    }

private:
    int capacity;
    Node *head, *tail;
    map<int, Node*> mp;
};