#ifndef POSTFIX_COPERAND_H
#define POSTFIX_COPERAND_H

#include "CNode.h"

#include <string>

using std::string;

class COperand : public CNode
{
public:
    COperand(int iValue, string sName) : CNode(CHILDLESS, sName, NO_CHILDREN) {i_value = iValue;}
    int iGetValue(){ return i_value;}
private:
    int i_value;
};

#endif //POSTFIX_COPERAND_H
