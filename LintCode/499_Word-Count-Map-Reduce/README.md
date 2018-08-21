这题其实就是简单模拟字符串分块统计个数和归并的过程。 
我用的stringstream来split字符串。

jiuzhang给的答案是用split()函数，我觉得也不错。

void Map(Input<string>* input) {
        // Write your code here
        // Please directly use func 'output' to 
        // output the results into output buffer.
        // void output(string &key, int value);
        while (!input->done()) {
            vector<string> words = split(input->value(), " ");
            for (string word : words) {
                output(word, 1);
            }
            input->next();
        }
    }

    vector<string> split(const string &str, string delim) {
        vector<string> results;
        int lastIndex = 0, index;
        while ((index = str.find(delim, lastIndex)) != string::npos) {
            results.push_back(str.substr(lastIndex, index - lastIndex));
            lastIndex = index + delim.length();
        }
        if (lastIndex != str.length()) {
            results.push_back(str.substr(lastIndex, str.length() - lastIndex));
        }
        return results;
    }