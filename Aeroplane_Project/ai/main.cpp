
#include <iostream>
#include "define.h"
#include "movegenerator.h"
#include "searchengin.h"
#include "evaluator.h"
#include <stdlib.h>
#include <unistd.h>
using namespace std;

void outputChessboard(CHESS * chessboard, searchEngine * player){
    cout << "\nRoll point: " << player->rollPoint << endl;
    for(int i = 0; i < 16; i++){
        if(i % 4 == 0)
            cout << endl;
        cout << "Chess: " << chessboard[i].chessID << "  " << chessboard[i].currentCoor.region << "  " << chessboard[i].currentCoor.code << endl;
    }
}



int main()
{
    moveGenerator * mg = new moveGenerator(5);
    evaluator * eval = new evaluator();
    searchEngine ai_player;
    ai_player.setEvaluator(eval);
    ai_player.setMoveGenerator(mg);

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
    int roundCount = 0;
    cout << "*******************************Game Start*******************************\n" << endl;
    while(!ai_player.isGameOver(chessboard)){
        cout << "\n\n====================Begin of this round=======================" << endl;

        cout << "\n[[[[[[[[[[[[[[[[[[[[Begin of RED's round]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
        ai_player.play(chessboard, RED);
        outputChessboard(chessboard, & ai_player);
        cout << "[[[[[[[[[[[[[[[[[[[[End of RED's round]]]]]]]]]]]]]]]]]]]]]]]]\n" << endl;

        cout << "\n[[[[[[[[[[[[[[[[[[[[Begin of YELLOW's round]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
        ai_player.play(chessboard, YELLOW);
        outputChessboard(chessboard, & ai_player);
        cout << "[[[[[[[[[[[[[[[[[[[[End of YELLOW's round]]]]]]]]]]]]]]]]]]]]]]]]\n" << endl;

        cout << "\n[[[[[[[[[[[[[[[[[[[[Begin of BLUE's round]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
        ai_player.play(chessboard, BLUE);
        outputChessboard(chessboard, & ai_player);
        cout << "[[[[[[[[[[[[[[[[[[[[End of BLUE's round]]]]]]]]]]]]]]]]]]]]]]]]\n" << endl;

        cout << "\n[[[[[[[[[[[[[[[[[[[[Begin of GREEN's round]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
        ai_player.play(chessboard, GREEN);
        outputChessboard(chessboard, & ai_player);
        cout << "[[[[[[[[[[[[[[[[[[[[End of GREEN's round]]]]]]]]]]]]]]]]]]]]]]]]\n" << endl;

        cout << "=====================End of this round========================\n\n" << endl;
        // sleep(1);
        roundCount ++;

    }
    std::cout << "******************************Game is Finished!***************************" << std::endl;
    cout << "Final roun count: " << roundCount  << ", jinx count:" << ai_player.jinxCount<<"\n" << endl;

    return 0;
}
