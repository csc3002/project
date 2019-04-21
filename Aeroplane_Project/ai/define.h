/*
 * File: define.h
 * ---------------
 * This file defines data structures and macros for an AI.
 */

#include <string>
#ifndef DEFINE_H
#define DEFINE_H

// Define regions
#define APRON "apron"
#define OFF "off"
#define OUTERLOOP "outerloop"
#define TRACK "track"
#define WIN "win"

// Define chess id
#define ALLBACK -1
#define NOCHESS 0
#define RED1 1
#define RED2 2
#define RED3 3
#define RED4 4
#define YELLOW1 5
#define YELLOW2 6
#define YELLOW3 7
#define YELLOW4 8
#define BLUE1 9
#define BLUE2 10
#define BLUE3 11
#define BLUE4 12
#define GREEN1 13
#define GREEN2 14
#define GREEN3 15
#define GREEN4 16

// Define chessboard code
#define OUTSIDE -1
#define OUTER_BEGIN 0
#define OUTER_END 51
#define TRACK_BEGIN 1
#define TRACK_END 6
#define RED_OFF 3       // The point after the taking off point
#define YELLOW_OFF 16
#define BLUE_OFF 29
#define GREEN_OFF 42
#define RED_TURN 0      // Turning points to the track
#define YELLOW_TURN 13
#define BLUE_TURN 26
#define GREEN_TURN 39
#define RED_FLY_BEGIN 20    // Flying points
#define RED_FLY_END 32
#define YELLOW_FLY_BEGIN 33
#define YELLOW_FLY_END 45
#define BLUE_FLY_BEGIN 46
#define BLUE_FLY_END 6
#define GREEN_FLY_BEGIN 7
#define GREEN_FLY_END 19


// Define colors
#define RED 0
#define YELLOW 1
#define BLUE 2
#define GREEN 3

// Define some macro function
#define IsRed(x) (x.color == RED)   //judge whether a chess is red
#define IsYellow(x) (x.color == YELLOW)     //judge whether a chess is yellow
#define IsBlue(x) (x.color == BLUE)     //judge whether a chess is blue
#define IsGreen(x) (x.color == GREEN)   //judge whether a chess is green
#define IsSameSide(x,y) (x.color == y.color)    //judge whether two chess are the same color
#define IsBlockRed(x) (x % 4 == 0)  //judge whether the block is red
#define IsBlockYellow(x) (x % 4 == 1)  //judge whether the block is yellow
#define IsBlockBlue(x) (x % 4 == 2)  //judge whether the block is blue
#define IsBlockGreen(x) (x % 4 == 3)  //judge whether the block is green

/* TODO: define some buff states */

// Define the structure representing the coordinate

typedef struct _coordinate {
    std::string region;      //region of the block
    int code;           //the code for the block
} COORDINATE;

// Define the stucture representing a move

typedef struct _chessmove {
    int chessID;         // the ID of chess being moved
    int rollPoint;       // roll point
} CHESSMOVE;

// Define the structure representing a chess

typedef struct _chess {
    int chessID;                // the ID of the chess
    int color;               // the color of the chess
    COORDINATE currentCoor;     // the current coordinate of the chess
    std::string buff_state;
    int round_left;

} CHESS;


#endif // DEFINE_H
