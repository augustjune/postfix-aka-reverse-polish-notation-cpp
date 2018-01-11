#ifndef POSTFIX_COPERATOR_H
#define POSTFIX_COPERATOR_H

#include "CNode.h"
#include <string>

using std::string;

class COperator : public CNode
{
public:
    COperator(char cOperation) : CNode(!CHILDLESS, string(1,cOperation), DEFAULT_COUNT_OF_CHILDREN)
    {
        c_operation = cOperation;
    }
    COperator(char cOperation, int iCustomCountOfChildren) : CNode(!CHILDLESS, string(1,cOperation), iCustomCountOfChildren)
    {
        c_operation = cOperation;
    }
private:
    char c_operation;
};

#endif //POSTFIX_COPERATOR_H
