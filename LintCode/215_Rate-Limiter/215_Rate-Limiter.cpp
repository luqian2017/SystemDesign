
class Solution {
public:
    /*
     * @param timestamp: the current timestamp
     * @param event: the string to distinct different event
     * @param rate: the format is [integer]/[s/m/h/d]
     * @param increment: whether we should increase the counter
     * @return: true or false to indicate the event is limited or not
     */

    bool isRatelimited(int timestamp, string event, string rate, bool increment) {
        int timeScale = 0;
        int pos = rate.find('/');
        int quota;
        stringstream ss;
        ss << rate.substr(0, pos); //pos also shows # of chars from 0 to pos
        ss >> quota; 
        string timeType = rate.substr(pos + 1, 1);
        switch (timeType[0]) {
            case 's':
                timeScale = 1;
                break;
            case 'm':
                timeScale = 60;
                break;
            case 'h':
                timeScale = 3600;
                break;
            case 'd':
                timeScale = 86400;
                break;
            default: 
                break;
        }
        
        int start_time = timestamp - timeScale + 1;
        int counter = 0;
        for (auto it = hashmap[event].lower_bound(start_time); it != hashmap[event].end(); ++it) {
                if (it->first < start_time) break;
                counter += it->second;
            }
        
        //we can only increment the count if increment is true
        if ((counter < quota) && increment) {  
            if (hashmap.find(event) == hashmap.end()) {
                hashmap[event] = map<int, int>();
            } else {
                if (hashmap[event].find(timestamp) == hashmap[event].end()) {
                    hashmap[event][timestamp] = 1;
                } else {
                    hashmap[event][timestamp]++;
                }
            }    
        }    
        
        return counter >= quota;   
    }
    
private:
    map<string, map<int, int>> hashmap;   //event, timestamp, count

};