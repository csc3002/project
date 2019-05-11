
#include <iostream>
#include "define.h"
#include "movegenerator.h"
#include "searchengin.h"
#include "evaluator.h"
#include <stdlib.h>
#include <unistd.h>
using namespace std;

void outputChessboard(CHESS * chessboard, searchEngine * player){
    cout << "\nRoll point: " << player->rollPoint  << " , my card: " << player->myCard<< endl;
    for(int i = 0; i < 16; i++){
        if(i % 4 == 0)
            cout << endl;
        cout << "Chess: " << chessboard[i].chessID << "  " << chessboard[i].currentCoor.region << "  " << chessboard[i].currentCoor.code <<
                "  buff: " << chessboard[i].buff_state << " round left: " << chessboard[i].round_left << endl;
    }
}



int main()
{
    moveGenerator * mg = new moveGenerator(6,1);
    evaluator * eval = new evaluator();
    searchEngine ai_player1;searchEngine ai_player2;searchEngine ai_player3; searchEngine ai_player4;
    ai_player1.setEvaluator(eval);
    ai_player1.setMoveGenerator(mg);
    ai_player2.setEvaluator(eval);
    ai_player2.setMoveGenerator(mg);
    ai_player3.setEvaluator(eval);
    ai_player3.setMoveGenerator(mg);
    ai_player4.setEvaluator(eval);
    ai_player4.setMoveGenerator(mg);

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
    while(!ai_player1.isGameOver(chessboard) || !ai_player2.isGameOver(chessboard) || !ai_player3.isGameOver(chessboard) || !ai_player4.isGameOver(chessboard) ){

        cout << "\n\n====================Begin of this round=======================" << endl;

        cout << "\n[[[[[[[[[[[[[[[[[[[[Begin of RED's round]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
        for(int i = 0; i < 16; i++){
            if(chessboard[i].round_left > 0)
                chessboard[i].round_left -= 1;
            else
                chessboard[i].buff_state = "";

        }
        ai_player1.play(chessboard, RED);
        outputChessboard(chessboard, & ai_player1);
        cout << "[[[[[[[[[[[[[[[[[[[[End of RED's round]]]]]]]]]]]]]]]]]]]]]]]]\n" << endl;

        cout << "\n[[[[[[[[[[[[[[[[[[[[Begin of YELLOW's round]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
        for(int i = 0; i < 16; i++){
            if(chessboard[i].round_left > 0)
                chessboard[i].round_left -= 1;
            else
                chessboard[i].buff_state = "";

        }
        ai_player2.play(chessboard, YELLOW);
        outputChessboard(chessboard, & ai_player2);
        cout << "[[[[[[[[[[[[[[[[[[[[End of YELLOW's round]]]]]]]]]]]]]]]]]]]]]]]]\n" << endl;

        cout << "\n[[[[[[[[[[[[[[[[[[[[Begin of BLUE's round]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
        for(int i = 0; i < 16; i++){
            if(chessboard[i].round_left > 0)
                chessboard[i].round_left -= 1;
            else
                chessboard[i].buff_state = "";

        }
        ai_player3.play(chessboard, BLUE);
        outputChessboard(chessboard, & ai_player3);
        cout << "[[[[[[[[[[[[[[[[[[[[End of BLUE's round]]]]]]]]]]]]]]]]]]]]]]]]\n" << endl;

        cout << "\n[[[[[[[[[[[[[[[[[[[[Begin of GREEN's round]]]]]]]]]]]]]]]]]]]]]]]]" << endl;
        for(int i = 0; i < 16; i++){
            if(chessboard[i].round_left > 0)
                chessboard[i].round_left -= 1;
            else
                chessboard[i].buff_state = "";

        }
        ai_player4.play(chessboard, GREEN);
        outputChessboard(chessboard, & ai_player4);
        cout << "[[[[[[[[[[[[[[[[[[[[End of GREEN's round]]]]]]]]]]]]]]]]]]]]]]]]\n" << endl;

        cout << "=====================End of this round========================\n\n" << endl;
        // sleep(1);
        roundCount ++;

    }
    std::cout << "******************************Game is Finished!***************************" << std::endl;
    cout << "Final roun count: " << roundCount  << endl;

    return 0;
}
