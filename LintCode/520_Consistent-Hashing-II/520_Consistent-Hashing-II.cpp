
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