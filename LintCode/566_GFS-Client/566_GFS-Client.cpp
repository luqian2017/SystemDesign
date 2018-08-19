
/* Definition of BaseGFSClient
 * class BaseGFSClient {
 * private: map<string, string> chunk_list;
 * public:
 *     string readChunk(string& filename, int chunkIndex) {
 *         // Read a chunk from GFS
 *     }
 *     void writeChunk(string& filename, int chunkIndex,
 *                     string& content) {
 *         // Write a chunk to GFS     
 *     }
 *  };
 */


class GFSClient : public BaseGFSClient {
public:

    /*
    * @param chunkSize: An integer
    */
    GFSClient(int chunkSize) {
        this->chunkSize = chunkSize;
    }

    /*
     * @param filename: a file name
     * @return: conetent of the file given from GFS
     */
    string read(string &filename) {
        
        if (mp.find(filename) == mp.end()) return "";
        
        int numOfChunks = mp[filename];
        string result;
        for (int i = 0; i < numOfChunks; ++i) {
            result = result + readChunk(filename, i);
        }
        return result;
    }

    /*
     * @param filename: a file name
     * @param content: a string
     * @return: nothing
     */
    void write(string &filename, string &content) {
        //important! Make sure that in the case of fileSize < chunkSize, num = 1;
        int numOfChunks = (content.size() + chunkSize - 1) / chunkSize;
        mp[filename] = numOfChunks;
        for (int i = 0; i < numOfChunks; ++i) {
            string subFile = content.substr(i * chunkSize, chunkSize);
            writeChunk(filename, i, subFile);
        }
    }
    
private:
    size_t chunkSize;
    map<string, int> mp; //stores filename<->numOfChunks
};
