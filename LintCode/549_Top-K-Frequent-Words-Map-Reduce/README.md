我用的C++ stl::priority_queue来作为一个max heap来保存前K个最频繁的词。 
注意 
1) 这里heap的维护是在Reducer端。 
2) priority_queue需要自定义operator < (因为object是自定义的)。如果里面是this->count < pair2.count就是最大堆(跟int类型默认一样)。如果是this->count > pair2.count就是最小堆。

        bool operator < (const Pair & pair2) const {   //max heap
            if (this->count == pair2.count) {
                return this->key > pair2.key;
            }
            return this->count < pair2.count; 
        }
3) priority_queue这个结构好像不能设固定大小。可以再加个count K来输出最大的K个元素，当然也可以再包一层写个wrapper 类。