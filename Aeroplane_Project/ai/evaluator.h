#include "define.h"

#ifndef EVALUATOR_H
#define EVALUATOR_H


class evaluator
{
public:
    evaluator();
    virtual ~evaluator();

    virtual int evaluate(const CHESS chessboard[], int side);
};

#endif // EVALUATOR_H
