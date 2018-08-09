/**
 * Definition of Trip:
 * class Trip {
 * public:
 *     int id; // trip's id, primary key
 *     int driver_id, rider_id; // foreign key
 *     double lat, lng; // pick up location
 *     Trip(int rider, double lat, double lng);
 * }
 * Definition of Helper
 * class Helper {
 * public:
 *     static get_distance(double lat1, double lng1,
 *                         double lat2, double lng2) {
 *         // return distance between (lat1, lng1) and (lat2, lng2)
 *     }
 * };
 */
class Location {
public:
    double lat;
    double lng;
    Location(double latitude, double longitude) : lat(latitude), lng(longitude) {}
};
    
class MiniUber {
public:
    map<int, Location *> ReportMap;
    map<int, Trip *> RequestMap;
    
    MiniUber() {
        // initialize your data structure here.
    }

    // @param driver_id an integer
    // @param lat, lng driver's location
    // return matched trip information if there have matched rider or NULL
    Trip* report(int driver_id, double lat, double lng) {
        if (RequestMap.find(driver_id) != RequestMap.end()) {
            return RequestMap[driver_id];
        }

        if (ReportMap.find(driver_id) == ReportMap.end()) {
            ReportMap[driver_id] = new Location(lat, lng);
        } else {
            ReportMap[driver_id]->lat = lat;
            ReportMap[driver_id]->lng = lng;
        }
        
        return nullptr;        
    }

    // @param rider_id an integer
    // @param lat, lng rider's location
    // return a trip
    Trip* request(int rider_id, double lat, double lng) {
        double minDist = 1e+6;
        int minDriverId = -1;
        for (auto &m : ReportMap) {
            double dist = Helper::get_distance(lat, lng, m.second->lat, m.second->lng);
            if (dist < minDist) {
                minDist = dist;
                minDriverId = m.first;
            }
        }
        
        Trip *trip = new Trip(rider_id, lat, lng);
        trip->driver_id = minDriverId;
        RequestMap[minDriverId] = trip;
        
        //in case no driver at all
        //if (minDriverId !=-1) 
        ReportMap.erase(minDriverId);   //erase the driver_id
        
        return trip;
    }
};