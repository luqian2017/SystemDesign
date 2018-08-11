这题要注意的是要用两个map，一个存储hashcode vs restaurant, 一个存储id vs hashcode。
注意这里hashcode 不能直接用geohash，因为同一个坐标可能有好几家餐馆。可以用geohash+id 或 geohash+name。