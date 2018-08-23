这题要注意：
1） Map()的output输出input->value.id，而不是1。因为这里是要统计每个单词对应文档的id，不是统计单词个数。
2) Reduce（）不需要专门维护一个map<string, vector<int>>，这里直接用一个vector<int>就可以。