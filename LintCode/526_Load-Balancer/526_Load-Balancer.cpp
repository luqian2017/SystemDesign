class LoadBalancer {
public:
    LoadBalancer() {
        // do intialization if necessary
    }

    /*
     * @param server_id: add a new server to the cluster
     * @return: nothing
     */
    void add(int server_id) {
        // write your code here
        servers.push_back(server_id);
        um[server_id] = servers.size() - 1;
    }

    /*
     * @param server_id: server_id remove a bad server from the cluster
     * @return: nothing
     */
    void remove(int server_id) {
        int pos = um[server_id];
        int alt_server_id = servers[servers.size() - 1];
        swap(servers[servers.size() - 1], servers[um[server_id]]);
        um[alt_server_id] = pos;
        um.erase(server_id);
        servers.resize(servers.size() - 1);
    }

    /*
     * @return: pick a server in the cluster randomly with equal probability
     */
    int pick() {
        int randomPos = rand() % servers.size();
        return servers[randomPos];
    }

private:
    unordered_map<int, int> um; //(server_id, position)
    vector<int> servers; //server ids
};