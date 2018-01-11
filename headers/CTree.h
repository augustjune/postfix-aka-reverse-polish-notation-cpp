#ifndef POSTFIX_CTREE_H
#define POSTFIX_CTREE_H

#include "CNode.h"
#include "CVariable.h"
#include <string>
#include <vector>

#define EVENT_CODE_ROOT_DELETED 4
#define EVENT_CODE_ADD_ACCESSORIAL_NUMB 3
#define EVENT_CODE_ADD_EXISTING 2
#define EVENT_CODE_ADD 1
#define EVENT_CODE_TREE_CREATED 0
#define EVENT_CODE_ADD_FAILURE -1
#define EVENT_CODE_EMPTY_TREE -2
#define EVENT_CODE_NOT_EMPTY_TREE -3
#define EVENT_CODE_INPUT_PARSING_FAILURE -4
#define EVENT_CODE_AFTER_INPUT_FAILURE -5
#define EVENT_CODE_COUNT_FAILURE -6
#define EVENT_CODE_NORMILIZE_FAILURE -7
#define EVENT_CODE_UNKNOWN_FAILURE -10

#define MAX_COUNT_OF_TRIES_TO_NORMALIZE_TREE 100
#define DEFAULT_ACCESSORIAL_NUMBER 1
#define FIRST_NUMBER_IN_ASCII 48
#define LAST_NUMBER_IN_ASCII 57
#define FIRST_BIG_LETTER_IN_ASCII 65
#define LAST_BIG_LETTER_IN_ASCII 90
#define FIRST_SMALL_LETTER_IN_ASCII 97
#define LAST_SMALL_LETTER_IN_ASCII 122
#define REGISTER_DEFAULT_VALUE " "
#define VARIABLE true
#define NUMBER false


class CTree
{
public:
    CTree();
    CTree(string sInput, bool  *pbSucc = NULL);       //  !♛  * ♛ !
    ~CTree();

    bool bInitialize(string sInput);
    bool bReInitialize(string sInput);

    bool bIsEmpty();
    double dCount();

    bool bAddOperation(char cOperation);
    bool bAddOperation(char cOperation, int iCustomCountOfChildren);
    bool bAddNumber(int iValue);
    bool bAddVariable(int iValue, string sName);
    bool bAddExistingElement(CNode* poExistingElement);

    void vPrintLevels();
    void vPrintPostfix();
    void vPrintInfix();
    void vPrintLog();
    CNode* root;

private:
    vector<CVariable*> vo_variables;
    string s_log;

    bool b_initialize_body(string sInput);
    bool b_add_element_body(CNode* poCurrentElement, char cOperation, int iCountOfChildren);
    bool b_add_element_body(CNode* poCurrentElement, int iValue);
    bool b_add_element_body(CNode* poCurrentElement, int iValue, string sName);
    bool b_add_existing_element_body(CNode* poCurrentElement, CNode* poExistingElement);
    double d_count_body(CNode* poCurrentElement);
    int i_get_value_of_variable(string sName);

    void v_log_add(string sEvent);
    void v_log_add(int iEventCode, string sValue);
    void v_print_levels_body(vector<CNode*>& queue, int iLevel);
    void v_print_postfix_body(CNode* poCurrentElement);
    string s_add_accessorial_numb(int iNumb, string sInput);
    string& s_infix_body(CNode* poCurrentElement, string& sResult);

    int i_find_variable(string sName);
    bool b_test_tree(CNode* poCurrentElement);
    bool b_char_is_operator(char cChar);
    bool b_char_is_letter(char cChar);
    bool b_char_is_number(char cChar);
    bool b_char_is_space(char cChar);
};

#endif //POSTFIX_CTREE_H
