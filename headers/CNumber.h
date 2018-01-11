#ifndef POSTFIX_CNUMBER_H
#define POSTFIX_CNUMBER_H

#include "COperand.h"

using std::to_string;

class CNumber : public COperand
{
public:
    CNumber(int iValue) : COperand(iValue, to_string(iValue)){}
};

#endif //POSTFIX_CNUMBER_H
