这题其实是考的字符串的tokenizer，我的方法version 1比较繁琐, 就是直接用split。


下面这个split()比较好用，链接在 
https://stackoverflow.com/questions/236129/the-most-elegant-way-to-iterate-the-words-of-a-string

std::vector<std::string> split(const std::string& text, const std::string& delims)
{
    std::vector<std::string> tokens;
    std::size_t start = text.find_first_not_of(delims), end = 0;

    while((end = text.find_first_of(delims, start)) != std::string::npos)
    {
        tokens.push_back(text.substr(start, end - start));
        start = text.find_first_not_of(delims, end);
    }
    if(start != std::string::npos)
        tokens.push_back(text.substr(start));

    return tokens;
}

九章的解法比较简洁：

/**
 * Definition of Document:
 * class Document {
 * public:
 *     int id;
 *     string content;
 * }
 */
class Solution {
public:
    /**
     * @param docs a list of documents
     * @return an inverted index
     */
    map<string, vector<int>> invertedIndex(vector<Document>& docs) {
        // Write your code here
        map<string, vector<int>> results;
        for (const Document& doc : docs) {
            string temp = "";
            string content = doc.content;
            int n = content.size();
            for (int i = 0; i < n; ++i) {
                if (content[i] == ' ') {
                    insert(results, temp, doc.id);
                    temp = "";
                } else
                    temp += content[i];
            }
            insert(results, temp, doc.id);
        }
        return results;
    }

    void insert(map<string, vector<int>> &results, string str, int id) {
        if (str == "")
            return;
        if (results.find(str) == results.end())
            results[str] = vector<int>();
        if (results[str].size() == 0 || results[str][results[str].size() - 1] != id)
            results[str].push_back(id);
    }
};

另外，这题也可以用stringstream直接将string tokenize，见version 2。 不过感觉比较慢。 
