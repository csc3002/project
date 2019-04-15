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
#define INNERLOOP "innerloop"
#define WIN "win"

// Define chess id
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
#define OUTER_BEGIN 0
#define OUTER_END 51
#define INNER_BEGIN 0
#define INNER_END 3

// Define colors
#define RED "RED"
#define YELLOW "YELLOW"
#define BLUE "BLUE"
#define GREEN "GREEN"

// Define some macro function
#define IsRed(x) (x.color == RED) //judge whether a chess is red
#define IsYellow(x) (x.color == YELLOW) //judge whether a chess is yellow
#define IsBlue(x) (x.color == BLUE) //judge whether a chess is blue
#define IsGreen(x) (x.color == GREEN) //judge whether a chess is green
#define IsSameSide(x,y) (x.color == y.color)

// Define the structure representing the coordinate

typedef struct _coordinate {
    string region;      //region of the block
    int code;           //the code for the block
} COORDINATE;

// Define the stucture representing a move

typedef struct _chessmove {
    int chessIDs[3];         // array of the IDs of chesses being moved
    int rollPoints[3];       // array of roll points
    int value;               //value of this move
} CHESSMOVE;

// Define the structure representing a chess

typedef struct _chess {
    int chessID;                // the ID of the chess
    string color;               // the color of the chess
    COORDINATE currentCoor;     // the current coordinate of the chess
} CHESS;


#endif // DEFINE_H
