/*
 * File: evaluator.cpp
 * -----------------
 * This is the implementatio of evaluator.
 */

#include "evaluator.h"
#include "define.h"

// the constructor and destructor
evaluator::evaluator()
{

}

evaluator::~evaluator()
{

}

/*
 * Implementation note: evaluate
 * ------------------------------
 * This evaluator work like this:
 * 1. Counts the benefit from a move. Benefit cases include taking off, moving, crashing enemies, going to track,
 *    winning, etc. When one of those case happens, the benefit point will increase accordingly.
 * 2. Counts the damage. Damage cases include overlapping and being threatened by enemies. When one of those
 *    cases happens, the damage point will increase accordingly.
 * 3. Finally, subtract benefit by damage and returns the result as the value.
 */

int evaluator::evaluate(const CHESS oldChessboard[],const CHESS newChessboard[], int side)
{
    int off = 0;
    int head = 0;
    int tail = 0;
    switch(side){
    case RED:{
        head = RED1;
        tail = RED4;
        off = RED_OFF;
        break;
    }

    case YELLOW:{
        head = YELLOW1;
        tail = YELLOW4;
        off = YELLOW_OFF;
        break;
        }
    case BLUE:{
        head = BLUE1;
        tail = BLUE4;
        off = BLUE_OFF;
        break;
        }
    case GREEN:{
        head = GREEN1;
        tail = GREEN4;
        off = GREEN_OFF;
        break;
        }
    }

    // counting benefits
    int benefit = 0;
    for(int i = 0; i < 16; i++){
        const CHESS * oldChess = & oldChessboard[i];
        const CHESS * newChess = & newChessboard[i];
        // count the benefit from using abilities
        if(newChess->color != side) {   // use debuff or eliminate buff on enemy chesses
            if(oldChess->buff_state == DEFENSED && oldChess->round_left > 1 && newChess->buff_state != DEFENSED){
                benefit += 200;
                return benefit;
            }
            else if(oldChess->buff_state != INTERFERRED && newChess->buff_state == INTERFERRED){
                benefit += 400;
                return benefit;
            }
        }
        else{       // use eliminate to own chess
            if(oldChess->buff_state == INTERFERRED  && oldChess->round_left > 1 && newChess->buff_state != INTERFERRED){
                benefit += 400;
                return benefit;
            }
            else if(oldChess->buff_state != DEFENSED && newChess->buff_state == DEFENSED){
                benefit += 200;
                return benefit;
            }
        }

        // count the benefit from crashing enemies
        if(newChess->color != side && oldChess->currentCoor.region == OUTERLOOP && newChess->currentCoor.region == APRON){
            benefit += 300;
        }
        // count the benefit from moving own chesses
        else{
            if(oldChess->currentCoor.region == APRON && newChess->currentCoor.region == OFF){
                benefit += 1000;
            }
            else if(oldChess->currentCoor.region == OUTERLOOP && newChess->currentCoor.region == TRACK){
                benefit += 5000;
            }
            else if(oldChess->currentCoor.region != WIN && newChess->currentCoor.region == WIN){
                benefit += 100000;
            }
            else{
                if(oldChess->currentCoor.region == OUTERLOOP && newChess->currentCoor.region == OUTERLOOP){
                    benefit += pow((newChess->currentCoor.code-off+52) % 52, 2) - pow((oldChess->currentCoor.code-off+52) % 52, 2);
                }
                else if(oldChess->currentCoor.region == OFF && newChess->currentCoor.region == OUTERLOOP){
                    benefit += pow((newChess->currentCoor.code-off+52) % 52, 2) + 25;
                }
            }
        }
    }

    // counting damage
    int damage = 0;
    int overlap[52] = {0};
    for(int i = head; i <= tail; i++){
        const CHESS * newChess1 = & newChessboard[i-1];     // mark own chess on a overlap board
        if(newChess1->currentCoor.region == OUTERLOOP){
            overlap[newChess1->currentCoor.code] += 1;
        }

        double threat_rate = 0.0;               // check if the chess is threatened by enemies
        for(int j = 0; j < 16; j++){
            const CHESS * newChess2 = & newChessboard[j];
            int direct_distance = 0;
            int pos1 = 0;
            int pos2 = 0;

            // enemies can only threat own chess when on the outer loop or taking off state
            if (newChess1->currentCoor.region == OUTERLOOP &&
                (newChess2->currentCoor.region == OUTERLOOP ||
                 newChess2->currentCoor.region == OFF) &&
                newChess1->color != newChess2->color) {
                if(newChess2->currentCoor.region == OUTERLOOP){     // distance calculation when enemy is on outer loop
                    pos1 = newChess1->currentCoor.code;
                    pos2 = newChess2->currentCoor.code;
                    direct_distance = (pos1 - pos2 + 52) % 52;
                }
                else if (newChess2->currentCoor.region == OFF) {    // distance calculation when enemy is on taking off state
                    int enemyOff = -1;
                    switch (newChess2->color) {
                        case RED:{
                            enemyOff = RED_OFF;
                            break;
                        }
                        case YELLOW:{
                            enemyOff = YELLOW_OFF;
                            break;
                        }
                        case BLUE:{
                            enemyOff = BLUE_OFF;
                            break;
                        }
                        case GREEN:{
                            enemyOff = GREEN_OFF;
                            break;
                        }
                    }
                    direct_distance = (newChess1->currentCoor.code - enemyOff + 52) % 52;   // calculate distance base on the enemy's taking off point

                }

                // calculating threat rate base on direct distance, own chess' position and enemy chess' color
                   if(direct_distance > 0  && direct_distance <= 6){    // direct threat within one roll
                       threat_rate += 1/6;
                   }
                   if(direct_distance > 6  && direct_distance <= 12){   // direct threat within two rolls
                       threat_rate += 1/36;
                   }
                   if(pos1 % 4 == newChess2->color){        // threat when the position's color is the same as the enemy
                       if(direct_distance > 4  && direct_distance <= 10){
                           threat_rate += 1/6;
                       }
                       if(direct_distance > 10  && direct_distance <= 16){
                           threat_rate += 1/36;
                       }
                       if(pos1 == RED_FLY_END || pos1 == YELLOW_FLY_END || pos1 == BLUE_FLY_END || pos1 == GREEN_FLY_END){  // threat when it is at the fly end
                           if(direct_distance > 16  && direct_distance <= 22){
                               threat_rate += 1/6;
                           }
                           if(direct_distance > 22  && direct_distance <= 28){
                               threat_rate += 1/36;
                           }
                       }
                   }
            }
        }
        damage += int(threat_rate * pow((newChess1->currentCoor.code-off+52) % 52, 2));
    }

    // adding overlap punishment
    for(int i = 0; i < 52; i++){
        if(overlap[i] == 2){
            damage += 200;
        }
        else if (overlap[i] == 3) {
            damage += 400;
        }
        else if(overlap[i] == 4){
            damage += 600;
        }
    }

    return benefit - damage;
}








