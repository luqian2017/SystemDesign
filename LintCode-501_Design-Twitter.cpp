/*
    最重要的一点是在设计getTen()时，一定要从order逆序找出order最大的那10条，这样才能说是最近的10条tweet。
*/


/**
 * Definition of Tweet:
 * class Tweet {
 * public:
 *     int id;
 *     int user_id;
 *     String text;
 *     static Tweet create(int user_id, string tweet_text) {
 *         // This will create a new tweet object,
 *         // and auto fill id
 *     }
 * }
 */

class Node {
public: 
    Tweet tweetEntry;
    Node(int ord, Tweet tweet) : order(ord), tweetEntry(tweet) {}
    bool operator < (const Node & o) const {
        return order > o.order;
    }
private:
    int order;
};

class MiniTwitter {
public:
    MiniTwitter() {
        // do intialization if necessary
        friends.clear();
        users_tweets.clear();
        order = 0;
    }

    /*
     * @param user_id: An integer
     * @param tweet_text: a string
     * @return: a tweet
     */
     Tweet postTweet(int user_id, string &tweet_text) {
        Tweet tweet = Tweet::create(user_id, tweet_text);
        if (users_tweets.find(user_id) == users_tweets.end()) {
            users_tweets[user_id] = vector<Node>();
        }
        users_tweets[user_id].push_back(Node(++order, tweet));
        return tweet;
    }

    /*
     * @param user_id: An integer
     * @return: a list of 10 new feeds recently and sort by timeline
     */
    vector<Tweet> getNewsFeed(int user_id) {
        vector<Node> allRecords; //including tweets from the user and his friends
        //if the user exists in the system
        if (users_tweets.find(user_id) != users_tweets.end()) {

            allRecords = getTen(users_tweets[user_id]);
        }
        //if the user has friends
        if (friends.find(user_id) != friends.end()) {
            for (auto friend_id : friends[user_id]) {
                if (users_tweets.find(friend_id) != users_tweets.end()) {
                    vector<Node> friendRecords = getTen(users_tweets[friend_id]);
                    allRecords.insert(allRecords.end(), friendRecords.begin(), friendRecords.end());
                }
            }
        }

        sort(allRecords.begin(), allRecords.end());
        vector<Tweet> newsFeed;
        int recordSize = allRecords.size();
        recordSize = min(10, recordSize);
        for (int i = 0; i < recordSize; ++i) {

            newsFeed.push_back(allRecords[i].tweetEntry);
        }
        return newsFeed;
    }

    /*
     * @param user_id: An integer
     * @return: a list of 10 new posts recently and sort by timeline
     */
    vector<Tweet> getTimeline(int user_id) {

        vector<Tweet> timeLine;
        if (users_tweets.find(user_id) == users_tweets.end()) {

            return timeLine;
        }

        vector<Node> userRecords = getTen(users_tweets[user_id]);
        sort(userRecords.begin(), userRecords.end());

        int recordsSize = userRecords.size();
        recordsSize = min(10, recordsSize);
        for (int i = 0; i < recordsSize; ++i) {

            timeLine.push_back(userRecords[i].tweetEntry);
        }

        return timeLine;
    }

    /*
     * @param from_user_id: An integer
     * @param to_user_id: An integer
     * @return: nothing
     */
    void follow(int from_user_id, int to_user_id) {

        if (friends.find(from_user_id) == friends.end()) {

            friends[from_user_id] = set<int>();
        }
        friends[from_user_id].insert(to_user_id);
    }

    /*
     * @param from_user_id: An integer
     * @param to_user_id: An integer
     * @return: nothing
     */
    void unfollow(int from_user_id, int to_user_id) {

        if (friends.find(from_user_id) != friends.end()) {

            friends[from_user_id].erase(to_user_id);
        }
    }

private:
    vector<Node> getTen(vector<Node> &records) {
        vector<Node> tenRecords;
        int recordSize = records.size();
        int count = 0;
        for (int i = recordSize - 1; i >= 0; --i) {    
            count++;
            tenRecords.push_back(records[i]);
            if (count == 10) break;
        }
        return tenRecords;
    }

    map<int, set<int>> friends;
    map<int, vector<Node>> users_tweets;
    int order;
};