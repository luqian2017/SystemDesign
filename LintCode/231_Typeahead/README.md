此题考察对map的应用。 
map < string, vector > wordMap; 
记录每个subWord对应的dict中的名字。 
vector words; 
把dict中的名字按顺序记下来，方便search()返回。

注意去重。有两种去重的情况。 
一个是dict里面单个名字出现两个同样的字母或同样的单词时，比如说tree，或”Yang Yang”。这种情况通过 
if (wordMap[subWord][vecSize - 1] != index) 
来去重。 
另一种情况是dict里面出现两个一样的名字，比如说”James Wang”, “James Wang”，这种情况map自身就能去重。

如果这题的search是输入单个first name或last name，则可以简化用stringstream或split()函数来做。代码如下：

    Typeahead(unordered_set<string> dict) {
        int index = 0;
        for (auto str : dict) {
            words.push_back(str); 
            //split the string into words
            stringstream ss(str);
            string buf; //stores the first name or last name like "Jason", "Zhang", etc
            while(ss >> buf) {
                if (wordMap.find(buf) == wordMap.end()) {
                    wordMap[buf] = vector<int>(1, index);   //generate {index}
                } else {
                    wordMap[buf].push_back(index);
                }
            }

            index++;
        }
    }

另外，这题不知道能不能用Trie做。下次再想想。
