
class GeoHash {
public:
    /*
     * @param latitude: one of a location coordinate pair 
     * @param longitude: one of a location coordinate pair 
     * @param precision: an integer between 1 to 12
     * @return: a base32 string
     */
    string encode(double latitude, double longitude, int precision) {
        string base32Map = "0123456789bcdefghjkmnpqrstuvwxyz";
        vector<double> longitudeRange = {-180, 180};
        vector<double> latitudeRange = {-90, 90};
       // long long value = 0;  it is wrong to use long long, will over flow. Should use string.
        string totalCode;
        string result;
        int len = 5 * precision - 1;
    
        while (len >= 0) {
            double longitudeMid = (longitudeRange[0] + longitudeRange[1]) / 2;
            double latitudeMid = (latitudeRange[0] + latitudeRange[1]) / 2;
            if (longitude > longitudeMid) { 
                totalCode = totalCode + '1';
                longitudeRange[0] = longitudeMid;
            } else {
                totalCode = totalCode + '0';
			    longitudeRange[1] = longitudeMid;
            }

            if (latitude > latitudeMid) {
                totalCode = totalCode + '1';
                latitudeRange[0] = latitudeMid;
            } else {
                totalCode = totalCode + '0';
                latitudeRange[1] = latitudeMid;
            }
            
            len -=2;
        }
        
        for (int i = 0; i < precision; ++i) {
            string subCode = totalCode.substr(i * 5, 5);
            result = result + base32Map[mapping(subCode)];
        }
        

        return result;
    }
    
private:
    // mapping a 5-digit bin to the index, like atoi
    int mapping(string code) {
        int result = 0;
        int len = code.size();
        for (int i = 0; i < len; ++i) {
            if (code[i] == '1') {
                result += 1 << (len - i - 1);
            }
        }        
        return result;
    }   
};