#ifndef POSTFIX_CVARIABLE_H
#define POSTFIX_CVARIABLE_H

#include "COperand.h"

#include <string>

using std::string;

class CVariable : public COperand
{
public:
    CVariable(int iValue, string sName) : COperand(iValue, sName){}
};

#endif //POSTFIX_CVARIABLE_H
