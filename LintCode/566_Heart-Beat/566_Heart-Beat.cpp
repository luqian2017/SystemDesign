class HeartBeat {
public:

    HeartBeat() {
        // do intialization if necessary
    }

    /*
     * @param slaves_ip_list: a list of slaves'ip addresses
     * @param k: An integer
     * @return: nothing
     */
    void initialize(vector<string> &slaves_ip_list, int k) {
        timeout = k << 1;   //timeout = 2 * k
        for (auto ip : slaves_ip_list) {
            slavesTsMap[ip] = 0;
        }
    }

    /*
     * @param timestamp: current timestamp in seconds
     * @param slave_ip: the ip address of the slave server
     * @return: nothing
     */
    void ping(int timestamp, string &slave_ip) {
        if (slavesTsMap.find(slave_ip) != slavesTsMap.end()) { 
            slavesTsMap[slave_ip] = timestamp;
        } 
    }

    /*
     * @param timestamp: current timestamp in seconds
     * @return: a list of slaves'ip addresses that died
     */
    vector<string> getDiedSlaves(int timestamp) {
        vector<string> result;
        
        for (auto st : slavesTsMap) {
            if ((timestamp - st.second) >= timeout) {
                result.push_back(st.first);
            }
        }
        
        return result;
    }

private:
    map<string, int> slavesTsMap;  //record slave_ip vs timestamp
    int timeout;  //set as k
    
};