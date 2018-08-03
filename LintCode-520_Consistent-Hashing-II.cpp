/*
这题要注意的是用一个map< int, int >来存储id和machine之间的映射关系。注意不能用map< int, vector<int> > 来存储一个machine和一串id，这样就没法找某个id对应哪个machine了。
另外还要 用一个set<int>来存储已经用过的id。
另外再强调map和set的key都是默认从大到小排序的。记得**lower_bound()这个函数非常非常有用**！map和set都可以用！
*/


class Solution {
public:
    int n, k;
    map<int, int> shards;   //stores id<->machine mapping, multiple ids to one machine
    set<int> ids; //stores ids to make sure it is not reused
    /*
     * @param n: a positive integer
     * @param k: a positive integer
     * @return: a Solution object
     */
    static Solution create(int n, int k)  {
        Solution sol = Solution();
        sol.n = n;
        sol.k = k;
        return sol;
    }

    /*
     * @param machine_id: An integer
     * @return: a list of shard ids
     */
    vector<int> addMachine(int machine_id) {
        vector<int> nodes;
        for (int i = 0; i < k; ++i) {
            int id;
            do {
                id = rand() % n;
            } while(shards.find(id) != shards.end());
            shards[id] = machine_id;
            ids.insert(id);
            nodes.push_back(id);
        } 
        sort(nodes.begin(), nodes.end());
        return nodes;
    }

    /*
     * @param hashcode: An integer
     * @return: A machine id
     */
    int getMachineIdByHashCode(int hashcode) {
        auto id = shards.lower_bound(hashcode);
        if (id == shards.end())
            return shards.begin()->second;
         else
            return id->second;
    }    
};