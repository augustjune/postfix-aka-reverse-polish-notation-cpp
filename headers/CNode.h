#ifndef POSTFIX_CNODE_H
#define POSTFIX_CNODE_H

#include <string>
#include <vector>

#define CHILDLESS false
#define DEFAULT_COUNT_OF_CHILDREN 2
#define NO_CHILDREN 0
#define ADDITION "+"
#define SUBTRACTION "-"
#define MULTIPLICATION "*"
#define DIVISION "/"
#define TILDE "~"


using std::string;
using std::vector;

class CNode
{
public:
    CNode(bool bCanHaveChild, string sName, int iCountOfChildren);
    CNode(CNode& oOtherNode);
    ~CNode();

    vector<CNode*>& vecGetChildren();
    bool bAddChild(CNode* poChild);
    int iGetCountOfChildren();
    string sGetName();
    bool bIsChildLess();

    bool bIsOperator();
    bool bIsNumber();
    bool bIsVariable();

protected:
    vector<CNode*> vo_children;      //begins from the right side (*in the tree*)   //??
    int i_count_of_children;        //??
    bool b_can_have_child;
    string s_name;

};


#endif //POSTFIX_CNODE_H
