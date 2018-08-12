/**
 * Definition of Document:
 * class Document {
 * public:
 *     int id;
 *     string content;
 * }
 */

//version 1: split the string
 
class Solution {
public:
    /**
     * @param docs a list of documents
     * @return an inverted index
     */
    map<string, vector<int>> invertedIndex(vector<Document>& docs) {
        map<string, vector<int>> result;

        for (auto doc : docs) { //should not use &doc here as d will be modified
            size_t pos = 0;
            string content = doc.content.substr(pos);
            while(pos < content.size()) {

                content = content.substr(pos);
                size_t nextPos = content.find(' ', 0);
                string sub_str;

                if (nextPos == string::npos) { //reach the end
                    sub_str = content.substr(0);
                    pos = content.size();
                } else {
                    sub_str = content.substr(0, nextPos);
                    pos = nextPos + 1;
                }

                if (sub_str.size() == 0) continue;

                if ((result.find(sub_str) == result.end()) || 
                        (find(result[sub_str].begin(), result[sub_str].end(), doc.id) == result[sub_str].end())) {
                        result[sub_str].push_back(doc.id);
                }
            }
        }

        return result;
    }
};

//version 2, based on stringstream
class Solution {
public:
    /**
     * @param docs a list of documents
     * @return an inverted index
     */
    map<string, vector<int>> invertedIndex(vector<Document>& docs) {
        map<string, vector<int>> result;

        for (auto & doc : docs) { //should not use &doc here as d will be modified
            stringstream ss(doc.content);
            string buf;
            vector<string> tokens; // Create vector to hold our words
            while (ss >> buf) tokens.push_back(buf);

            for (auto & token : tokens) {
                if (token.size() == 0) continue;
                if ((result.find(token) == result.end()) || 
                        (find(result[token].begin(), result[token].end(), doc.id) == result[token].end())) {
                        result[token].push_back(doc.id);
                }    
            }
        }

        return result;
    }
};