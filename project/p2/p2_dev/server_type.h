/*
 * This is VE280 Project 2, SU2020.
 * Written by Zhanhui Zhou, Ziqiao Ma(TA) and Zhuoer Zhu(TA).
 * Latest Update: 6/1/2020.
 * All rights reserved.
 */

#ifndef SERVER_TYPE_H
#define SERVER_TYPE_H

#include <string>
using namespace std;


/* Constants */
// Max number of users in the server
const int MAX_USERS = 20;

// Max number of followers per user
const int MAX_FOLLOWERS = 20;

// Max number of following per user
const int MAX_FOLLOWING = 20;

// Max number of posts per user
const int MAX_POSTS = 50;

// Max number of comments per post
const int MAX_COMMENTS = 50;

// Max number of likes per post
const int MAX_LIKES = 20;

// Max number of tags per post
const int MAX_TAGS = 5;

// Max number of total tags per server
const int MAX_ALL_TAGS = MAX_USERS * MAX_POSTS * MAX_TAGS;


struct Comment_t;
struct Tag_t;
struct Post_t;
struct User_t;
struct Server;



struct Comment_t
/*
// Type: Comment_t
// ------------------
// The type Comment_t is used to represent a comment
// It consists of:
// * text: text of comment
// * user: pointer to the user who posted that comment
*/
{
    string text;
    User_t *user;
};


struct Tag_t
/*
// Type: Tag_t
// ------------------
// The type Tag_t is used to represent a tag
// It consists of:
// * tag_content: the content of the tag
// * tag_score: the score of the tag used to determine the trend
// * num_related*: the tag related information
// * weight*: the score weight of corresponding elements.
*/
{
    string tag_content;
    int tag_score;
    int num_relatedPost;
    int num_relatedLike;
    int num_relatedComm;
private:
    static const int weightP;
    static const int weightL;
    static const int weightC;
public:
    // EFFECT: default constructor
    Tag_t(): tag_score(0), num_relatedPost(0), 
             num_relatedLike(0), num_relatedComm(0) {};

    // EFFECT: update tagscore
    void UpdateTagScore()
    {
        tag_score = num_relatedPost * weightP +
                    num_relatedLike * weightL +
                    num_relatedComm * weightC;
    }
};
// EFFECT: algorithm sort helper function.
bool sortHelp(Tag_t* t1, Tag_t* t2);


struct Post_t
/*
// Type: Post_t
// ------------------
// The type Comment_t is used to represent a post
// It consists of:
// * comments: An array of comments
// * like_users: An array of pointers to the users who like this post
// **(modified) tagsPts: An array of tag pointers pointing to Server::tag
// * owner: A pointer to the post owner
// * title: the title of the post
// * text: the text of the post
// * num_likes: the number of likes
// * num_comments: the number of comments
// * num_tags: the number of comments
*/
{
    int index;
    Comment_t comments[MAX_COMMENTS];
    User_t *like_users[MAX_LIKES];
    Tag_t  *tagPts[MAX_TAGS];
    User_t *owner;
    string title;
    string text;
    int num_likes;
    int num_comments;
    int num_tag;
public:
    /* EFFECT: default constructor */
    Post_t(): num_likes(0), num_comments(0), num_tag(0) {};

    /* EFFECT: parse the content of every post */
    void ParsePost();

    // EFFECT: add a user to like list
    //         return false if already in the list
    //         return true if successfully added
    bool AddLikeUser(User_t* user);

    // EFFECT: delete a user from like list
    //         return false if not in the list
    //         return true if successfully deleted
    bool DeleteLikeUser(User_t* user);

    // EFFECT: return false if comment not found in the list
    //         return true if comment found
    bool FindComm(int commIndex) const;

    // REQUIRE: FindComm should be used before calling this function
    // EFFECT: add a comment
    void AddComm(const Comment_t& comment);

    // REQUIRE: FindComm should be used before calling this function
    // EFFECT: delete a comment
    bool DeleteComm(User_t* user, int commIndex);

    // EFFECT: update the tag scores of tags in a deleted post
    void UpdateTagState_DeletePost();

private:
    // EFFECT: update the tag scores of tags in a initalized post
    void UpdateTagState_InitalPost();

    // EFFECT: Find the index of a user in the like list
    // NOTE: the index starts from 0 here
    int FindLikeUser(User_t* user);

    // EFFECT: increase/decrease the attribute of tag
    void tagLikeInc();
    // EFFECT: increase/decrease the attribute of tag
    void tagLikeDec();
    // EFFECT: increase/decrease the attribute of tag
    void tagCommInc();
    // EFFECT: increase/decrease the attribute of tag
    void tagCommDec();
};




struct User_t
/*
// Type: User_t
// ------------------
// The type Comment_t is used to represent a user
// It consists of:
// * serverPt: A pointer points to the singleton server
// * posts: An array of posts
// * following: An array of following usernames
// * follower: An array of followers
// * username: the username of user
// * num_posts: the number of posts
// * num_following: the number of following users
// * num_follower: the number of followers
*/
{
    /* use static because User_t shares the same server */
    static Server *serverPt;
    Post_t posts[MAX_POSTS];
    User_t *following[MAX_FOLLOWING];
    User_t *followers[MAX_FOLLOWERS];
    string username;
    int num_posts;
    int num_following;
    int num_followers;
public:
    // EFFECT: default constructor 
    User_t(): num_posts(0), num_following(0), num_followers(0) {};

    // EFFECT: parse the content of every "user_info" file 
    void ParseUser();

    // REQUIRE: postIndex starts from 1
    // EFFECT: return false if post not found
    //         return true  if post found
    bool FindPost(int postIndex) const;

    // REQUIRE: postIndex starts from 1
    // Effect: return false if post not successfully deleted (not the owner)
    //         return true  if post deleted.
    bool DeletePost(int postIndex);

    // EFFECT: return the index of following/followers
    //         return -1 when not in the list
    // NOTE: index returned starts from 0
    int FindFollowingIndex(User_t* userToFind) const;
    int FindFollowerIndex(User_t* userToFind) const;

private:
    // EFFECT: parse the following&follower list in "user_info"
    void ParseFollowingANDers(ifstream& fin);
};



struct InputFile
{
    std::string nameFile;
    std::string logFile;
};


struct Server
/*
// Type: Server
// ------------------
// The type Server is used to represent a server
// It consists of:
// * inputFile: The inputFile path, including "username" and "logfile"
// * usersDir: The "users" directory path
// * user: The array of users
// * tag: The array of tags
// * num_users: The number of users
// * num_tags: The number of tags
*/
{
    InputFile inputFile;
    std::string usersDir;
    User_t user[MAX_USERS];
    Tag_t  tag[MAX_ALL_TAGS];
    int num_users;
    int num_tags;
public:
    // EFFECT: constructor the object using inputFile
    Server(const InputFile& iF);

    // EFFECT: return the pointer to user by his/her name
    //            if the user name is not in the user list,
    //            add this user before returning the pointer
    User_t* NameToPt(const string& userName);

    // EFFECT: return the pointer to tag by its content
    //            if the tag is not in the tag list,
    //            add this tag before returning the pointer
    Tag_t* TagToPt(const string& tagName);

    // EFFECT: update the scores of all tags according to likes/comments/posts
    void UpdateTagsScores();

    // EFFECT: read and process "username" file;
    void ParseNameFile();

    // EFFECT: read and process "logfile" file;
    void ParseLogFile();
};


//--------------------------------- LogFileParser.h ---------------------------------
struct LogFileParser
/*
// Type: LogFileParser
// ------------------
// The type Comment_t is used to help parsing the "logfile"
// It consists of:
// * serverPt: the pointer to the server
// * logFile: the "logfile" path
// * (private) parseResult: the result of parsing sentence into words:
                            "ZZH is hanhan" -> {"ZZH", "is", "hanham"}
*/
{
    Server* serverPt;
    const string& logFile;
private:
    std::string parseResult[5];
public:
    // EFFECT: default constructor
    LogFileParser(Server* sp, const string& lf) : serverPt(sp), logFile(lf) {};

    // EFFECT: parse the logfile 
    void ParseLogFile();
private:
    /* EFFECTS: parse the sentence into words */
    void ParseSentence(const string& sentence);

    /* EFFECTS: basic operation */
    void trending() const;
    /* EFFECTS: basic operation */
    void visit() const;
    /* EFFECTS: basic operation */
    void refresh() const;
    /* EFFECTS: basic operation */
    void follow() const;
    /* EFFECTS: basic operation */
    void unfollow() const;
    /* EFFECTS: basic operation */
    void like() const;
    /* EFFECTS: basic operation */
    void unlike() const;
    /* EFFECTS: basic operation */
    void comment(ifstream& fin) const;
    /* EFFECTS: basic operation */
    void uncomment() const;
    /* EFFECTS: basic operation */
    void post(ifstream& fin) const;
    /* EFFECTS: basic operation */
    void deletep() const;
};




#endif // SERVER_TYPE_H
