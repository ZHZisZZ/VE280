/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#ifndef SIMULATION_H
#define SIMULATION_H
#include "server_type.h"

//--------------------------------- simulation.h ---------------------------------
// Print Function
void printUser(const User_t& user, const string& relationship);
// Print Function
void printPost(const Post_t& post);
// Print Function
void printTag(const Tag_t& tag, int rank);


//--------------------------------- exception.h ----------------------------------
enum Error_t 
{
    INVALID_ARGUMENT,
    FILE_MISSING,
    CAPACITY_OVERFLOW,
    INVALID_LOG,
};

struct Exception_t: public exception
{
    Error_t error;
    string error_info;

    Exception_t(Error_t err, const string& info){
        this->error = err;
        this->error_info = info;
    }
};

/// enum class "Cmd" and "Max" and corresponding const arr
//  are used to reduce duplicate when printing error_info 
enum class Cmd
{
    LIKE,
    UNLIKE,
    COMMENT,
    UNCOMMENT,
    DELETE,
};
const string Out[] = {"like", "unlike", "comment", "uncomment", "delete"};

enum class Max
{
    USERS,
    FOLLOWERS,
    FOLLOWINGS,
    POSTS,
    COMMENTS,
    LIKES,
    TAGS
};
const string MaxOut[] = {"users", "followers", "followings", "posts", "comments", "likes", "tags"};
const int MaxNum[] = {MAX_USERS, MAX_FOLLOWERS, MAX_FOLLOWING, MAX_POSTS, MAX_COMMENTS, MAX_LIKES, MAX_TAGS};



// FIRST STAGE: Argument & Filemissing
void MFILE(ifstream& fin, const string& fileName);
void ValidArgument(int n);
// SECOND STAGE: Logfile Catch Function
void ValidLog(User_t* user1, User_t* user2, Cmd cmd, int indexPost, int indexCom = 0, const Comment_t& comment = {});
// FIRST & SECOND STAGE: Overflow are checked in both username and logfile
void ValidOverflow(int num, bool numInput = false, Max max = Max::USERS, User_t* user = nullptr, Post_t* post = nullptr);


#endif 