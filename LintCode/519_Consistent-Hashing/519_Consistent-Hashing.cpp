class Solution {
public:
    /*
     * @param n: a positive integer
     * @return: n x 3 matrix
     */
    vector<vector<int>> consistentHashing(int n) {
        vector<vector<int>> results;
        vector<int> machines = {0, 359, 1};
        results.push_back(machines);
        
        for (int i = 1; i < n; ++i) {
            
            int index = 0;
            for (int j = 1; j < i; ++j) { //since index = 0, if j start from 0, it is wasteful.
                if (results[j][1] - results[j][0] > results[index][1] - results[index][0]) 
                    index = j;
            }
  
            int x = results[index][0];
            int y = results[index][1];
            results[index][1] = x + (y - x) / 2; //cannot be written as x + (y - x) >> 1 as >> has very low priority!
            
            machines[0] = results[index][1] + 1;
            machines[1] = y;
            machines[2] = i + 1;   //it is i+1 since the machine ID starts from 1
            
            results.push_back(machines);
        }
        
        return results;
    }
};
————————————————
版权声明：本文为CSDN博主「纸上得来终觉浅 绝知此事要躬行」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/roufoo/article/details/81219554