
/**
 * Definition of Location:
 * class Location {
 * public:
 *     double latitude, longitude;
 *     static Location create(double lati, double longi) {
 *         // This will create a new location object
 *     }
 * };
 * Definition of Restaurant
 * class Restaurant {
 * public:
 *     int id;
 *     string name;
 *     Location location;
 *     static Restaurant create(string &name, Location &location) {
 *         // This will create a new restaurant object,
 *         // and auto fill id
 *     }
 * };
 * Definition of Helper
 * class Helper {
 * public:
 *     static get_distance(Location &location1, Location &location2) {
 *         // return distance between location1 and location2.
 *     }
 * };
 * class GeoHash {
 * public:
 *     static string encode(Location &location) {
 *         // return convert location to a GeoHash string
 *     }
 *     static Location decode(string &hashcode) {
 *          // return convert a GeoHash string to location
 *     }
 * };
 */

class Node {
public:
    double distance;
    Restaurant restaurant;
    Node(double d, Restaurant r) : distance(d), restaurant(r) {}  
    bool operator <(const Node& n) const {return distance < n.distance;}
    
};

class MiniYelp {
public:
    map<string, Restaurant> hashMap;    //(HashCode, Restaurant)
    map<int, string> idMap;    //(id, HashCode)
    stringstream ss;
    MiniYelp() {
        
    }

    // @param name a string
    // @param location a Location
    // @return an integer, restaurant's id
    int addRestaurant(string name, Location &location) {
        Restaurant restaurant = Restaurant::create(name, location);   
        ss << restaurant.id;
        string geoHash = GeoHash::encode(location);
        string hashcode = geoHash + "." + ss.str();    //hashcode = geoHash + id;
        
        if (hashMap.find(hashcode) == hashMap.end()) { //is the if needed here?
            hashMap[hashcode] = restaurant;
            idMap[restaurant.id] = hashcode;
        }
        
        return restaurant.id;
    }

    // @param restaurant_id an integer
    void removeRestaurant(int restaurant_id) {
        if (idMap.find(restaurant_id) != idMap.end()) {
            string hashcode = idMap[restaurant_id];
            hashMap.erase(hashcode);
            idMap.erase(restaurant_id);
        }
    }

    // @param location a Location
    // @param k an integer, distance smaller than k miles
    // @return a list of restaurant's name and sort by 
    // distance from near to far.
    vector<string> neighbors(Location &location, double k) {
        vector<Node> neighborNodes;
        vector<string> result;
        for (auto & h : hashMap) {
            string hashcode = h.first;
            string geoHash = hashcode.substr(0, hashcode.find('.'));
            Location loc = GeoHash::decode(geoHash);
            double distance = Helper::get_distance(location, loc);
            if (distance < k) {
                neighborNodes.push_back(Node(distance, h.second));
            }
        }
        
        sort(neighborNodes.begin(), neighborNodes.end());
        for (auto & n : neighborNodes) {
            result.push_back(n.restaurant.name);
        }
        return result;
    }
};
