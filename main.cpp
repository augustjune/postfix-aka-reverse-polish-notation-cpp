#include "headers/CTree.h"
#include "headers/CNode.h"
#include "headers/COperator.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    CTree tree;
    tree.bInitialize("1 13 ku+ ku MEd -+*-");
    //CTree tree("1 13 ku+ ku MEd -+*-");
    cout << "Wynik wyrazenia jest rowny: " << tree.dCount()<<endl;
    tree.vPrintLevels();
    tree.vPrintLog();


    //tree.vPrintInfix();


    /*Pytania:
     * modyfikacja dostepu -> CNode::CNode(CNode& oOtherNode)
     * kopiowanie i nie kopiowanie zmiennej bez dzieci -> EVENT_CODE_ADD_EXISTING
     *
     *
     *
     * */
    return 15;
}