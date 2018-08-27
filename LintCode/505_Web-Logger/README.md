数据结构采用deque，参考了网上的答案。
注意
1） get_hit_count_in_last_5_minute()里面必须用<=。
2） 同一个timestamp可能hit多次，所以都必须加起来。
3）deque.front()是最老的entry，所以将其与当前timestamp比较，若不在当前5分钟内，则其count不算，再pop_front()，继续与当前timestamp比较。
