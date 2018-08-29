主要数据结构采用map<string, map<int, int>>，对应event, timestamp, counter。
1) 可以用stringstream转换"3/m" 里面的3，也可以用
atoi(rate.substr(0, pos).c_str());
