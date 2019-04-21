
#include <iostream>
#include "define.h"
#include "movegenerator.h"
#include "searchengine.h"
#include "evaluator.h"
#include <stdlib.h>
#include <unistd.h>
using namespace std;

void outputChessboard(CHESS * chessboard, searchEngine * player){
    cout << "\nRoll point: " << player->rollPoint << endl;
    for(int i = 0; i < 4; i++){
        cout << "Chess: " << chessboard[i].chessID << "  " << chessboard[i].currentCoor.region << "  " << chessboard[i].currentCoor.code << endl;
    }
}



int main()
{
    moveGenerator mg = moveGenerator(5);
    evaluator eval;
    searchEngine ai_player;
    ai_player.setEvaluator(&eval);
    ai_player.setMoveGenerator(&mg);

    // initializing the chessboard
    CHESS chessboard[16];
    for(int i = 0; i < 16; i++){
        chessboard[i].chessID = i+1;
        chessboard[i].currentCoor.code = OUTSIDE;
        chessboard[i].currentCoor.region = APRON;
        if(i >= 0 && i <= 3)
            chessboard[i].color = RED;
        if(i >= 4 && i <= 7)
            chessboard[i].color = YELLOW;
        if(i >= 8 && i <= 11)
            chessboard[i].color = BLUE;
        if(i >= 12 && i <= 15)
            chessboard[i].color = GREEN;
    }

    cout << "----------------------------Game Start---------------------------" << endl;
    while(true){
        ai_player.play(chessboard, RED);
        //ai_player.play(chessboard, YELLOW);
        //ai_player.play(chessboard, BLUE);
        //ai_player.play(chessboard, GREEN);
        outputChessboard(chessboard, & ai_player);
        sleep(5);

    }


    return 0;
}
