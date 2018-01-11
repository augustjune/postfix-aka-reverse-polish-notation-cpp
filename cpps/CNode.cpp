#include "../headers/CNode.h"

#include <string>
#include <vector>

using std::string;
using std::vector;
using std::stoi;
using std::exception;

CNode::CNode(bool bCanHaveChild, string sName, int iCountOfChildren)
{
    b_can_have_child = bCanHaveChild;
    s_name = sName;
    i_count_of_children = iCountOfChildren;
    for (int i=0; i<iCountOfChildren; i++)
        vo_children.push_back(NULL);
}//CNode(bool bCanHaveChild, string sName, int iCountOfChildren)

CNode::CNode(CNode& oOtherNode)
{
    b_can_have_child = oOtherNode.b_can_have_child;
    s_name = oOtherNode.sGetName();
    i_count_of_children = oOtherNode.iGetCountOfChildren();     //oOtherNode.i_count_of_children?    modyfikacji dostepu
    for (int i=0; i<i_count_of_children; i++)
        vo_children.push_back(NULL);
}//CNode::CNode(CNode& oOtherNode)

CNode::~CNode()
{
    for (int i=0; i<i_count_of_children; i++)
        if(vo_children[i]!=NULL)
            delete vo_children[i];
}//~CNode()

vector<CNode*>& CNode::vecGetChildren()
{
    return vo_children;
}//vector<CNode*>& vecGetChildren();

int CNode::iGetCountOfChildren()
{
    return i_count_of_children;
}//int CNode::iGetCountOfChildren()

bool CNode::bAddChild(CNode* poChild)
{
    bool b_added = false;
    for (int i=0;!b_added && i<poChild->iGetCountOfChildren(); i++)
        if (poChild->vecGetChildren()[i]==NULL)
        {
            poChild->vecGetChildren()[i] = poChild;
            b_added = true;
        }
    return b_added;
}//bool bAddChild(CNode* poChild);

string CNode::sGetName()
{
    return s_name;
}//string sGetName();

bool CNode::bIsChildLess()
{
    return !b_can_have_child;
}//bool bCanHaveChild();

bool CNode::bIsOperator()
{
    return s_name == ADDITION || s_name == SUBTRACTION || s_name == MULTIPLICATION || s_name == DIVISION || s_name == TILDE;
}//bool CNode::bIsOperator()

bool CNode::bIsNumber()
{
    try
    {
        stoi(s_name);
        return false;
    }catch (exceptionŚ) { return true;}
}//bool CNode::bIsNumber()

bool CNode::bIsVariable()
{
    return !bIsNumber() && !bIsOperator();
}//bool CNode::bIsVariable()