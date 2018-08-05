/**
 * Definition of Column:
 * class Column {
 * public:
 *     int key;
 *     String value;
 *     Column(int key, string value) {
 *         this->key = key;
 *         this->value = value;
 *    }
 * }
 */


class MiniCassandra {
public:
    MiniCassandra() {
        // do intialization if necessary
    }

    /*
     * @param raw_key: a string
     * @param column_key: An integer
     * @param column_value: a string
     * @return: nothing
     */
    void insert(string &raw_key, int column_key, string &column_value) {
        hashmap[raw_key][column_key] = column_value;
    }

    /*
     * @param raw_key: a string
     * @param column_start: An integer
     * @param column_end: An integer
     * @return: a list of Columns
     */
    vector<Column> query(string &raw_key, int column_start, int column_end) {
        vector<Column> sol;

        if (hashmap.find(raw_key) == hashmap.end()) return sol;

        for (auto c : hashmap[raw_key]) {
            if ((c.first >= column_start) && (c.first <= column_end)) {
                sol.push_back(Column(c.first, c.second));
            }      
        }

        return sol;
    }

private:
    map<string, map<int, string>> hashmap;
};