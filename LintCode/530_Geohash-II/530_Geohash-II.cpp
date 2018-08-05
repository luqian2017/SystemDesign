class GeoHash {
public:
    /*
     * @param geohash: geohash a base32 string
     * @return: latitude and longitude a location coordinate pair
     */
    vector<double> decode(string &geohash) {
        string base32Map = "0123456789bcdefghjkmnpqrstuvwxyz";
        vector<double> latitude = {-90, 90};
        vector<double> longitude = {-180, 180};
        bool isLongTurn = true;     //longitude first, then latitude
            
        for (int i = 0; i < geohash.size(); ++i) {

            int val = base32Map.find(geohash[i]);  //position is the value
            
            for (int j = 0; j < 5; ++j) {
                
                if (isLongTurn) {
                
                    if (val & (1 << (4 - j)))
                        longitude[0] = (longitude[0] + longitude[1]) / 2;
                    else         
                        longitude[1] = (longitude[0] + longitude[1]) / 2;
                    
                } else {
                
                    if (val & (1 << (4 - j)))
                        latitude[0] = (latitude[0] + latitude[1]) / 2;
                    else         
                        latitude[1] = (latitude[0] + latitude[1]) / 2;
                
                }
                
                isLongTurn = !isLongTurn;
            }
        }
        
        vector<double> result = {(latitude[0] + latitude[1]) / 2, 
                                 (longitude[0] + longitude[1]) / 2};
        
        return result;
    }
};