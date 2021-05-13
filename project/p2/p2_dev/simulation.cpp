/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#include <iostream>
#include <fstream>
#include "simulation.h"
#include "server_type.h"
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

//--------------------------------- simulation.cpp ----------------------------------
void printUser(const User_t& user, const string& relationship)
{
    cout << user.username << endl;
    cout << relationship << endl;
    cout << "Followers: " << user.num_followers
         << "\nFollowing: " << user.num_following << endl;
}

void printPost(const Post_t& post)
{
    cout << post.owner->username << endl;
    cout << post.title << endl;
    cout << post.text << endl;
    cout << "Tags: ";
    for(int i = 0; i<post.num_tag; ++i)
    {
        cout << post.tagPts[i]->tag_content << " ";
    }
    cout << "\nLikes: " << post.num_likes << endl;
    if (post.num_comments > 0)
    {
        cout << "Comments:" << endl;
        for(int i = 0; i<post.num_comments; ++i)
        {
            cout << post.comments[i].user->username << ": "
                 << post.comments[i].text << endl;
        }
    }
    cout << "- - - - - - - - - - - - - - -" << endl;
}

void printTag(const Tag_t& tag, int rank)
{
    cout << rank << " " << tag.tag_content << ": " << tag.tag_score << endl;
}

//--------------------------------- exception.cpp ----------------------------------
void ValidArgument(int n)
{
    if (n < 2)
    {
        string error_info = "Error: Wrong number of arguments!\n"
                            "Usage: ./p2 <username> <logfile>\n";
        throw Exception_t(INVALID_ARGUMENT, error_info);
    }
}

void MFILE(ifstream& fin, const string& fileName)
{
    if (!fin)
    {
        string error_info = "Error: Cannot open file ";
        error_info += fileName;
        error_info += "!\n";
        throw Exception_t(FILE_MISSING, error_info);
    }
}

void ValidOverflow(int num, bool numInput, Max max, User_t* user, Post_t* post)
{
    num = (!numInput) ? num + 1 : num;
    if (num > MaxNum[(int)max])
    {
        string error_info;
        switch (max)
        {
            case Max::USERS:
                    error_info =  "Error: Too many users!\n";
                    break;
            case Max::FOLLOWERS:
            case Max::FOLLOWINGS:
            case Max::POSTS:
                    error_info =  "Error: Too many " + MaxOut[(int)max] + " for user " + user->username + "!\n";
                    break;
            case Max::COMMENTS:
            case Max::LIKES:
            case Max::TAGS:
                    error_info =  "Error: Too many " + MaxOut[(int)max] + " for post " + post->title + "!\n";                                         
                    break;
        }
        error_info +=  "Maximal number of " + MaxOut[(int)max] + " is " + to_string(MaxNum[(int)max]) + ".\n";    
        throw Exception_t(CAPACITY_OVERFLOW, error_info);
    }
}

void ValidLog(User_t* user1, User_t* user2, Cmd cmd, int indexPost, int indexCom, const Comment_t& comment)
{
    /* first line */
    string error_info;
    switch (cmd)
    {
        case Cmd::LIKE:
        case Cmd::UNLIKE:
        case Cmd::COMMENT:
                error_info = "Error: " + user1->username + " cannot " + Out[(int)cmd]
                                       + " post #" + to_string(indexPost) + " of "
                                       + user2->username + "!\n";  
                break;

        case Cmd::UNCOMMENT:
                error_info = "Error: " + user1->username + " cannot " + Out[(int)cmd] 
                                       + " comment #" + to_string(indexCom) + " of post #" 
                                       + to_string(indexPost) + " posted by " + user2->username + "!\n";
                break;

        case Cmd::DELETE:
                error_info = "Error: " + user2->username + " cannot " + Out[(int)cmd]
                                       + " post #" + to_string(indexPost) + "!\n";
                break;
    }

    /* second line */
    /* if post not found */
    if (!user2->FindPost(indexPost))
    {
        error_info += user2->username + " does not have post #" + to_string(indexPost) + ".\n";
        throw Exception_t(INVALID_LOG, error_info);
    }
    /* if post found -> in divides into different situation */
    else 
    {
        auto& post = user2->posts[indexPost - 1];
        switch(cmd)
        {
            case Cmd::LIKE:
                if (!post.AddLikeUser(user1))
                {
                    error_info += user1->username + " has already liked post #" + to_string(indexPost) + " of " + user2->username + ".\n";  
                    throw Exception_t(INVALID_LOG, error_info);
                }
                break;

            case Cmd::UNLIKE:
                if (!post.DeleteLikeUser(user1))
                {
                    error_info += user1->username + " has not liked post #" + to_string(indexPost) + " of " + user2->username + ".\n";  
                    throw Exception_t(INVALID_LOG, error_info);
                }
                break;

            case Cmd::DELETE:
                user2->DeletePost(indexPost);
                break;
            
            case Cmd::COMMENT:
                // conmment
                post.AddComm(comment);
                break;

            case Cmd::UNCOMMENT:
                if (!post.FindComm(indexCom))
                {
                    error_info += "Post #" + to_string(indexPost) + " does not have comment #" + to_string(indexCom) + ".\n";
                    throw Exception_t(INVALID_LOG, error_info);
                }
                else if (!post.DeleteComm(user1, indexCom))
                {
                    error_info += user1->username + " is not the owner of comment #" + to_string(indexCom) + ".\n";
                    throw Exception_t(INVALID_LOG, error_info);
                }
                break;
        }
    }
}


//--------------------------------- server_type.cpp ----------------------------------
/* in-class static member initialization */
Server* User_t::serverPt = nullptr;
const int Tag_t::weightP = 5;
const int Tag_t::weightL = 1;
const int Tag_t::weightC = 3;

//--------------------------------- Server class ----------------------------------
Server::Server(const InputFile& iF)
    :  inputFile(iF), num_users(0), num_tags(0)
{
    User_t::serverPt = this;
}

void Server::ParseNameFile()
{
    ifstream fin(inputFile.nameFile); 
    MFILE(fin, inputFile.nameFile); // prevent "FILE_MISSING"

    // read "users" directory path
    fin >> usersDir;

    // read user id
    string tempId;
    while (fin >> tempId)
    {
        ValidOverflow(num_users, false, Max::USERS, nullptr, nullptr); // prevent "OVERFLOW"
        user[num_users++].username = tempId;
    }
    fin.close();

    // parse info of every user
    for (int i = 0; i < num_users; i++)
    {
        user[i].ParseUser();
    }
}

void Server::ParseLogFile()
{
    LogFileParser parser(this, inputFile.logFile);
    parser.ParseLogFile();
}

User_t* Server::NameToPt(const string& userName)
{
    int i = 0;
    for (; i < num_users && user[i].username != userName; i++)  continue;
    return (i == num_users) ? nullptr : user + i;
}

Tag_t* Server::TagToPt(const string& tagName)
{
    int i, j;
    // ** skip all the deleted tag.
    for (i = 0, j = 0; i < num_tags; j++)
    {
        if (tag[j].tag_content == tagName && tag[j].num_relatedPost != 0) break;
        if (tag[j].num_relatedPost) i++;
    }
    if (i >= num_tags)
    {
        for (j = 0; tag[j].num_relatedPost; j++) continue;
        tag[j].tag_content = tagName;
        num_tags++;
    }
    return tag + j;
}

void Server::UpdateTagsScores()
{
    // ** skip all the deleted tag
    for (int i = 0, j = 0; i < num_tags; j++)
    {
        if (tag[j].num_relatedPost)
        {
            i++;
            tag[j].UpdateTagScore();
        }
    }
}


//--------------------------------- User_t struct ----------------------------------
void User_t::ParseUser()
{
    // Parse every user separately;
    std::string userDir = serverPt->usersDir + string("/") + username;
    std::string infoDir = userDir + string("/user_info");
    
    ifstream fin(infoDir);
    MFILE(fin, infoDir); // prevent "FILE_MISSING"

    fin >> num_posts;
    ValidOverflow(num_posts, true, Max::POSTS, this, nullptr); // prevent "OVERFLOW"

    ParseFollowingANDers(fin);
    fin.close();

    // parse the "post" of every user
    for (int i = 0; i < num_posts; i++)
    {
        posts[i].owner = this;
        posts[i].index = i + 1;
        posts[i].ParsePost();
    }
}

void User_t::ParseFollowingANDers(ifstream& fin)
{
    // Parse following;
    fin >> num_following;
    ValidOverflow(num_following, true, Max::FOLLOWINGS, this, nullptr); // prevent "OVERFLOW"

    for (int i = 0; i < num_following; i++)
    {
        std::string followingName;
        fin >> followingName;
        following[i] = serverPt->NameToPt(followingName);
    }

    // Paser follower;
    fin >> num_followers;
    ValidOverflow(num_followers, true, Max::FOLLOWERS, this, nullptr); // prevent "OVERFLOW"

    for (int i = 0; i < num_followers; i++)
    {
        std::string followersName;
        fin >> followersName;
        followers[i] = serverPt->NameToPt(followersName);
    }
}

bool User_t::FindPost(int postIndex) const
{
    return postIndex <= num_posts;
}

/* i starts from i */
bool User_t::DeletePost(int postIndex)
{
    if (!FindPost(postIndex)) return false;
    // change tag states
    posts[postIndex - 1].UpdateTagState_DeletePost();
    for (int i = postIndex; i < num_posts; i++)
    {
        posts[i - 1] = posts[i];
    }
    posts[num_posts-1].num_comments = 0;
    posts[num_posts-1].num_likes = 0;
    posts[num_posts-1].num_tag = 0;
    // delete the first one instead of covering the old one with the new one
    num_posts--;
    return true;
}


int User_t::FindFollowingIndex(User_t* userToFind) const
{
    for (int i = 0; i < num_following; i++)
    {
        if (following[i] == userToFind) return i;
    }
    return -1;
}

int User_t::FindFollowerIndex(User_t* userToFind) const
{
    for (int i = 0; i < num_followers; i++)
    {
        if (followers[i] == userToFind) return i;
    }
    return -1;
}


//--------------------------------- Post_t struct ----------------------------------
void Post_t::ParsePost()
{
    std::string postDir = User_t::serverPt->usersDir +
                          std::string("/") +
                          owner->username +
                          std::string("/posts/") +
                          to_string(index);

    ifstream fin(postDir);
    MFILE(fin, postDir); // prevent "MISSING_FILE"

    // read title;
    getline(fin, title);

    // read tags;
    // read tags until temp is not tag;
    std::string temp;
    getline(fin, temp);
    while (*temp.begin() == '#' && *(temp.end()-1) == '#')
    {
        temp = temp.substr(1, temp.size() - 2);
        // skip the repeated tag;
        int i;
        for (i = 0; i < num_tag && tagPts[i]->tag_content != temp; i++) continue;
        if (i == num_tag)
        {
            // skip the repeated tag;
            ValidOverflow(num_tag, false, Max::TAGS, nullptr, this); // prevent "OVERFLOW"
            Tag_t* tempPt = User_t::serverPt->TagToPt(temp);
            tempPt->num_relatedPost++;
            tagPts[num_tag++] = tempPt;
        }
        getline(fin, temp);
    }

    // read text;
    text = temp;

    // read likes;
    fin >> num_likes;
    ValidOverflow(num_likes, true, Max::LIKES, nullptr, this); // prevent "OVERFLOW"
    for (int i = 0; i < num_likes; i++)
    {
        std::string likeUserName;
        fin >> likeUserName;
        like_users[i] = User_t::serverPt->NameToPt(likeUserName);
    }

    // read comments;
    fin >> num_comments;
    fin.get();
    ValidOverflow(num_comments, true, Max::COMMENTS, nullptr, this); // prevent "OVERFLOW"
    for (int i = 0; i < num_comments; i++)
    {
        std::string commentUserName;
        std::string commentContent;
        getline(fin, commentUserName);
        comments[i].user =  User_t::serverPt->NameToPt(commentUserName);
        getline(fin, comments[i].text);
    }
    fin.close();

    UpdateTagState_InitalPost();
}

bool Post_t::AddLikeUser(User_t* user)
{
    if (FindLikeUser(user) != -1) return false;
    ValidOverflow(num_likes, false, Max::LIKES, owner, this);
    //if (num_likes == MAX_LIKES) return true;
    like_users[num_likes++] = user;
    tagLikeInc();
    return true;
}

bool Post_t::DeleteLikeUser(User_t* user)
{
    int index;
    if ( ( index = FindLikeUser(user) ) == -1) return false;
    for (int i = index + 1; i < num_likes; i++)
    {
        like_users[i - 1] = like_users[i];
    }
    num_likes--;
    tagLikeDec();
    return true;
}

bool Post_t::FindComm(int commIndex) const
{
    return commIndex <= num_comments;
}

void Post_t::AddComm(const Comment_t& comment)
{
    ValidOverflow(num_comments, false, Max::COMMENTS, owner, this);
    comments[num_comments++] = comment;
    tagCommInc();
}

bool Post_t::DeleteComm(User_t* user, int commIndex)
{
    if (comments[commIndex - 1].user != user) return false;
    for (int i = commIndex; i < num_comments; i++)
    {
        comments[i - 1] = comments[i];
    }
    num_comments--;
    tagCommDec();
    return true;
}

void Post_t::UpdateTagState_InitalPost()
{
    for (int i = 0; i < num_tag; i++)
    {
        tagPts[i]->num_relatedLike += num_likes;
        tagPts[i]->num_relatedComm += num_comments;
    }
}

void Post_t::UpdateTagState_DeletePost()
{
    for (int i = 0; i < num_tag; i++)
    {
        tagPts[i]->num_relatedPost--;
        tagPts[i]->num_relatedLike -= num_likes;
        tagPts[i]->num_relatedComm -= num_comments;
        if ( !tagPts[i]->num_relatedPost )
        {
            tagPts[i]->tag_content = "";
            User_t::serverPt->num_tags--;
        }
    }
}

int Post_t::FindLikeUser(User_t* user)
{
    int i = 0;
    for (; i < num_likes && like_users[i] != user; i++) continue;
    return i == num_likes ? -1 : i;
}

void Post_t::tagLikeInc()
{
    for (int i = 0; i < num_tag; i++)
    {
        tagPts[i]->num_relatedLike++;
    }
}

void Post_t::tagLikeDec()
{
    for (int i = 0; i < num_tag; i++)
    {
        tagPts[i]->num_relatedLike--;
    }
}

void Post_t::tagCommInc()
{
    for (int i = 0; i < num_tag; i++)
    {
        tagPts[i]->num_relatedComm++;
    }
}

void Post_t::tagCommDec()
{
    for (int i = 0; i < num_tag; i++)
    {
        tagPts[i]->num_relatedComm--;
    }
}


//--------------------------------- LogFileParser.cpp ----------------------------------
void LogFileParser::ParseLogFile()
{
    ifstream fin(logFile);
    MFILE(fin, logFile);

    std::string sentence;
    while (getline(fin, sentence))
    {
        try
        {
            ParseSentence(sentence);
            if (parseResult[0] == "trending" && isdigit(parseResult[1][0]))      
                trending();
            else if (parseResult[1] == "visit")    
                visit();
            else if (parseResult[1] == "refresh")
                refresh();
            else if (parseResult[1] == "follow")
                follow();
            else if (parseResult[1] == "unfollow")
                unfollow();
            else if (parseResult[1] == "like")
                like();
            else if (parseResult[1] == "unlike")
                unlike();
            else if (parseResult[1] == "comment")
                comment(fin);
            else if (parseResult[1] == "uncomment")
                uncomment();
            else if (parseResult[1] == "post")
                post(fin);
            else if (parseResult[1] == "delete")
                deletep();
        }
        catch (const Exception_t& e)
        {
            cout << e.error_info;
        }
    }
    fin.close();
}

void LogFileParser::ParseSentence(const string& sentence)
{
    stringstream ss;
    ss << sentence;
    int i = 0;
    while (ss >> parseResult[i++]) continue;
}

bool sortHelp(Tag_t* t1, Tag_t* t2)
{
    if (t1->tag_score < t2->tag_score) return false;
    if (t1->tag_score == t2->tag_score)
    {
        if (t1->tag_content.compare(t2->tag_content) >= 0)
            return false;
    }
    return true;
}

void LogFileParser::trending() const
{
    std::cout << ">> trending\n";
    serverPt->UpdateTagsScores();
    int minTag = min(serverPt->num_tags, atoi(parseResult[1].c_str()));
    // sort the temporary pointer to tag rather than real tag in server
    Tag_t** cpyTags = new Tag_t* [serverPt->num_tags];
    for (int i = 0, j = 0; i < serverPt->num_tags; j++)
    {
        if (!serverPt->tag[j].num_relatedPost) continue;
        cpyTags[i++] = serverPt->tag + j;
    }
    sort(cpyTags, cpyTags + serverPt->num_tags, sortHelp);
    for (int i = 0; i < minTag; i++)
    {
        printTag(*(cpyTags[i]), i + 1);
    }
    delete [] cpyTags;
}

void LogFileParser::visit() const
{
    std::cout << ">> visit\n";
    User_t* user1 = serverPt->NameToPt(parseResult[0]);
    User_t* user2 = serverPt->NameToPt(parseResult[2]);
    bool following = false;
    bool follower  = false;
    std::string relation;
    if (user1 == user2)
        relation = "";
    else
    {
        for (int i = 0; i < user1->num_following; i++)
        {
            if (user1->following[i] == user2)
            {   
                following = true;
                break;
            }
        }
        for (int i = 0; i < user1->num_followers; i++)
        {
            if (user1->followers[i] == user2)
            {   
                follower = true;
                break;
            }
        }
        if (!following) relation = "stranger";
        else if (following && follower) relation = "friend";
        else relation = "following";
    }
    printUser(*user2 , relation);
}


void LogFileParser::refresh() const
{
    std::cout << ">> refresh\n";
    User_t* user1 = serverPt->NameToPt(parseResult[0]);
    for (int i = 0; i < user1->num_posts; i++)
    {
        printPost(user1->posts[i]);
    }
    for (int i = 0; i < user1->num_following; i++)
    {
        for (int j = 0; j < user1->following[i]->num_posts; j++)
        {
            printPost(user1->following[i]->posts[j]);
        }
    }
}

void LogFileParser::follow() const
{
    std::cout << ">> follow\n";
    User_t* user1 = serverPt->NameToPt(parseResult[0]);
    User_t* user2 = serverPt->NameToPt(parseResult[2]);
    // prevent double follow;
    if (user1->FindFollowingIndex(user2) != -1) return;
    user1->following[user1->num_following++] = user2;
    user2->followers[user2->num_followers++] = user1;
}

void LogFileParser::unfollow() const
{
    std::cout << ">> unfollow\n";
    User_t* user1 = serverPt->NameToPt(parseResult[0]);
    User_t* user2 = serverPt->NameToPt(parseResult[2]);
    int indexfollowing;
    // prevent double unfollow but not prompt
    if ((indexfollowing = user1->FindFollowingIndex(user2)) == -1) return;
    for (int i = indexfollowing; i < user1->num_following - 1; i++)
    {
        user1->following[i] = user1->following[i + 1];
    }
    user1->num_following--;
    int indexfollower = user2->FindFollowerIndex(user1);
    for (int i = indexfollower; i < user2->num_followers - 1; i++)
    {
        user2->followers[i] = user2->followers[i + 1];
    }
    user2->num_followers--;
}

void LogFileParser::post(ifstream& fin) const
{
    std::cout << ">> post\n";  
    User_t* user1 = serverPt->NameToPt(parseResult[0]);

    // prevent post overflow by reading the argument into trivial object;
    Post_t* post;
    bool flag = false;
    if (user1->num_posts >= MAX_POSTS)
    {
        Post_t triPost;
        post = &triPost;
    }
    else
    {
        flag = true;
        post = &user1->posts[user1->num_posts++];
    }

    post->owner = user1;
    // read title;
    getline(fin, post->title);
    // read tags;
    std::string temp;
    getline(fin, temp);
    // until temp is not tag;
    while (*temp.begin() == '#' && *(temp.end()-1) == '#')
    {
        //ValidOverflow(post.num_tag, false, Max::TAGS, nullptr, &post);
        if (user1->num_posts < MAX_POSTS || flag)
        {
            temp = temp.substr(1, temp.size() - 2);
            // skip the repeated tag;
            int i;
            for (i = 0; i < post->num_tag && post->tagPts[i]->tag_content != temp; i++) continue;
            // skip the repeated tag;
            if (i == post->num_tag)
            {
                Tag_t* tempPt = User_t::serverPt->TagToPt(temp);
                tempPt->num_relatedPost++;
                post->tagPts[post->num_tag++] = tempPt;
            }
        }
        getline(fin, temp);
    }
    // READ text;
    post->text = temp;

    if (!flag) ValidOverflow(user1->num_posts, false, Max::POSTS, post->owner, post);
}

void LogFileParser::like() const
{
    std::cout << ">> like\n";
    User_t* user1 = serverPt->NameToPt(parseResult[0]);
    User_t* user2 = serverPt->NameToPt(parseResult[2]);
    int postIndex = atoi(parseResult[3].c_str());
    // prevent "INVALID_LOG"
    ValidLog(user1, user2, Cmd::LIKE, postIndex);
}

void LogFileParser::unlike() const
{
    std::cout << ">> unlike\n";
    User_t* user1 = serverPt->NameToPt(parseResult[0]);
    User_t* user2 = serverPt->NameToPt(parseResult[2]);
    int postIndex = atoi(parseResult[3].c_str());
    // prevent "INVALID_LOG"
    ValidLog(user1, user2, Cmd::UNLIKE, postIndex);
}

void LogFileParser::comment(ifstream& fin) const
{
    std::cout << ">> comment\n";
    User_t* user1 = serverPt->NameToPt(parseResult[0]);
    User_t* user2 = serverPt->NameToPt(parseResult[2]);
    int postIndex = atoi(parseResult[3].c_str());
    std::string comment;
    getline(fin, comment);
    // prevent "INVALID_LOG"
    ValidLog(user1, user2, Cmd::COMMENT, postIndex, 0, {comment, user1});
}

void LogFileParser::uncomment() const
{
    std::cout << ">> uncomment\n";
    User_t* user1 = serverPt->NameToPt(parseResult[0]);
    User_t* user2 = serverPt->NameToPt(parseResult[2]);
    int postIndex = atoi(parseResult[3].c_str());
    int commIndex = atoi(parseResult[4].c_str());
    // prevent "INVALID_LOG"
    ValidLog(user1, user2, Cmd::UNCOMMENT, postIndex, commIndex);
}

void LogFileParser::deletep() const
{
    std::cout << ">> delete\n";
    User_t* user1 = serverPt->NameToPt(parseResult[0]);
    int postIndex = atoi(parseResult[2].c_str());
    // prevent "INVALID_LOG"
    ValidLog(nullptr, user1, Cmd::DELETE, postIndex);
}
