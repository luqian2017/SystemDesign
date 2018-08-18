class Typeahead {
public:
    /*
    * @param dict: A dictionary of words dict
    */
    map<string, vector<int>> wordMap;   //the vector<int> stores the index of the strings in dict.
    vector<string> words; // e.g., {"Jason Zhang", James Yu", ...}
    Typeahead(unordered_set<string> dict) {
        int index = 0;
        for (auto str : dict) {
            words.push_back(str); 
            //split the string into subWords
            int strSize = str.size();
            for (int i = 0; i < strSize; ++i) {
                for (int j = i; j < strSize; ++j) {
                    string subWord = str.substr(i, j - i + 1);
                    if (wordMap.find(subWord) == wordMap.end()) {
                        wordMap[subWord] = vector<int>(1, index);   //generate {index}
                    } else {
                        //remove duplicate: make sure that "Tree" will not enter into the vec twice as it has two 'e'.
                        int vecSize = wordMap[subWord].size();
                        if (wordMap[subWord][vecSize - 1] != index) {
                            wordMap[subWord].push_back(index);
                        }
                    }
                }
            }
            index++;
        }
    }

    /*
     * @param str: a string
     * @return: a list of words
     */
    vector<string> search(string &str) {
        vector<string> result;

        if (wordMap.find(str) == wordMap.end()) {
            return result;
        } else {
            for (auto i : wordMap[str]) {
                result.push_back(words[i]);
            }
        }      
        return result;
    }
};
