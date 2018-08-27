class Node {
public:
    Node(int t, int c) : timestamp(t), count(c) {}
    int32_t getTimestamp() {return timestamp;}
    void incCount() {count++;}
    uint32_t getCount() {return count;}
private:
    int32_t timestamp;
    uint32_t count;
};

class WebLogger {
public:
    WebLogger() : count(0) {}

    /*
     * @param timestamp: An integer
     * @return: nothing
     */
    void hit(int timestamp) {
        if (!dq.empty() && (dq.front().getTimestamp() == timestamp)) {
            dq.front().incCount();
        } else {
            dq.push_back(Node(timestamp, 1));
        }
        count++;
    }

    /*
     * @param timestamp: An integer
     * @return: An integer
     */
    int get_hit_count_in_last_5_minutes(int timestamp) {
        while(!dq.empty() && ((dq.front().getTimestamp() + 300) <= timestamp)) {
            count -= dq.front().getCount();
            dq.pop_front();
        }
        return count;
    }

private:
    uint32_t count;
    deque<Node> dq;
};
