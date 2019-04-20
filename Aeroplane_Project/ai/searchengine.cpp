// TODO: file description

#include "searchengine.h"
#include "define.h"
#include "movegenerator.h"
#include "evaluator.h"

searchEngine::searchEngine()
{

}


searchEngine::~searchEngine(){
    delete pMG;
    delete pEval;
}



/*
 * Implementation note: genOuterMove
 * ---------------------------------
 *
 */

void searchEngine::genOuterMove(CHESS &chess, int rollPoint, int off, int turn, int flyBegin, int flyEnd){

}

/*
 * Implementation note: genInnerMove
 * ---------------------------------
 *
 */

void searchEngine::genInnerMove(CHESS &chess, int rollPoint, int turn){

}
