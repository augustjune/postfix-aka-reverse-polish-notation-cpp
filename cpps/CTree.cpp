#include "../headers/CTree.h"
#include "../headers/CNode.h"
#include "../headers/COperator.h"
#include "../headers/CVariable.h"
#include "../headers/CNumber.h"

#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::stoi;
using std::string;
using std::vector;
using std::exception;

CTree::CTree()
{
    root = NULL;
    v_log_add(EVENT_CODE_TREE_CREATED,"");
}//CTree()

CTree::CTree(string sInput, bool  *pbSucc)             //   !♛  * ♛ !
{
    root = NULL;
    v_log_add(EVENT_CODE_TREE_CREATED,"");
    if  (pbSucc != NULL)  *pbSucc = bInitialize(sInput);
}

CTree::~CTree()
{
    if(!bIsEmpty())
        delete root;
}//~CTree()

bool CTree::bInitialize(string sInput)
{
    if  (root != NULL)
    {
        delete root;
        root = NULL;
    }//if  (root != NULL)


    if (!bIsEmpty())
    {
        v_log_add(EVENT_CODE_NOT_EMPTY_TREE, "");
        return false;
    }
    if (!b_initialize_body(sInput))
    {
        cout << "Przez niepoprawne wprowadzenie postaci postfiksowej całości wyrażenia nie dało się wczytać" << endl;
        v_log_add(EVENT_CODE_INPUT_PARSING_FAILURE, "");
        return false;
    }
    if(!b_test_tree(root))
    {
        int i_count_of_tries = 0;
        do
        {
            i_count_of_tries++;
            v_log_add(EVENT_CODE_AFTER_INPUT_FAILURE, "");
            //sInput = s_add_accessorial_numb(DEFAULT_ACCESSORIAL_NUMBER, sInput);
            v_log_add(EVENT_CODE_ADD_ACCESSORIAL_NUMB, to_string(DEFAULT_ACCESSORIAL_NUMBER));
            if (!bAddNumber(DEFAULT_ACCESSORIAL_NUMBER))
                v_log_add(EVENT_CODE_UNKNOWN_FAILURE, "");
        }while (!b_test_tree(root) && i_count_of_tries < MAX_COUNT_OF_TRIES_TO_NORMALIZE_TREE);
        if (i_count_of_tries == MAX_COUNT_OF_TRIES_TO_NORMALIZE_TREE)
            v_log_add(EVENT_CODE_NORMILIZE_FAILURE, "");
    }
    return true;
}//bool CTree::bInitialize(string sInput)

bool CTree::bReInitialize(string sInput)
{
    if (bIsEmpty())
    {
        v_log_add(EVENT_CODE_EMPTY_TREE, "");
        return false;
    }
    delete root;
    root = NULL;    //??
    v_log_add(EVENT_CODE_ROOT_DELETED, sInput);
    return bInitialize(sInput);
}//bool CTree::bReInitialize(string sInput)

bool CTree::bIsEmpty()
{
    return root == NULL;
}//bool bIsEmpty();

double CTree::dCount()
{
    if (bIsEmpty())
    {
        v_log_add(EVENT_CODE_EMPTY_TREE,"");
        return 0;
    }
    return d_count_body(root);
    //root->dCount();

}//double dCount

bool CTree::bAddOperation(char cOperation)
{
    if (bIsEmpty())
    {
        root = new COperator(cOperation);
        v_log_add(EVENT_CODE_ADD, string(1,cOperation));
        return true;
    }
    if (b_add_element_body(root, cOperation, DEFAULT_COUNT_OF_CHILDREN))
        return true;
    else
    {
        v_log_add(EVENT_CODE_ADD_FAILURE, string(1,cOperation));
        return false;
    }

}//bool bAddOperation(char cOperation);

bool CTree::bAddOperation(char cOperation, int iCountOfChildren)
{
    if (bIsEmpty())
    {
        root = new COperator(cOperation, iCountOfChildren);
        v_log_add(EVENT_CODE_ADD, string(1,cOperation));
        return true;
    }
    if (b_add_element_body(root, cOperation, iCountOfChildren))
        return true;
    else
    {
        v_log_add(EVENT_CODE_ADD_FAILURE, string(1,cOperation));
        return false;
    }

}//bool bAddOperation(char cOperation);

bool CTree::bAddNumber(int iValue)
{
    if (bIsEmpty())
    {
        root = new CNumber(iValue);
        v_log_add(EVENT_CODE_ADD, to_string(iValue));
        return true;
    }
    if (b_add_element_body(root, iValue))
        return true;
    else
    {
        v_log_add(EVENT_CODE_ADD_FAILURE, to_string(iValue));
        return false;
    }
}//bool bAddNumber(int iValue);

bool CTree::bAddVariable(int iValue, string sName)
{
    if (bIsEmpty())
    {
        root = new CVariable(iValue, sName);
        v_log_add(EVENT_CODE_ADD, sName);
        return true;
    }
    if (b_add_element_body(root, iValue, sName))
        return true;
    else
    {
        v_log_add(EVENT_CODE_ADD_FAILURE, sName);
        return false;
    }
}//bool bAddVariable(int iValue, stirng sName);

bool CTree::bAddExistingElement(CNode* poExistingElement)
{
    if (bIsEmpty())
    {
        root = poExistingElement;
        v_log_add(EVENT_CODE_ADD, poExistingElement->sGetName());
        return true;
    }
    if (b_add_existing_element_body(root, poExistingElement))
        return true;
    else
    {
        v_log_add(EVENT_CODE_ADD_FAILURE, poExistingElement->sGetName());
        return false;
    }
}//bool CTree::bAddVariable(CVariable* poVariable)

void CTree::vPrintLevels()
{
    vector<CNode*> vec = {root};
    v_print_levels_body(vec, 0);
}//void CTree::vPrintLevels()

void CTree::vPrintPostfix()
{
    if (bIsEmpty())
        v_log_add(EVENT_CODE_EMPTY_TREE, "");
    else
    {
        v_print_postfix_body(root);
    }
}//void CTree::vPrintPostfix()

void CTree::vPrintInfix()
{
    if (bIsEmpty())
        v_log_add(EVENT_CODE_EMPTY_TREE, "");
    else
    {
        string result = "";
        cout << s_infix_body(root, result) << endl;
    }
}

void CTree::vPrintLog()
{
    cout << "~~LOG~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << s_log;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}//void CTree::vPrintLog()


//private:

bool CTree::b_initialize_body(string sInput)
{
    string reg = REGISTER_DEFAULT_VALUE;
    bool reg_is_string = true;
    bool error_held = true;         //zmienna odpowiada za przerwanie dzialania funkcji przy wystapieniu pierwszego bledu
    for (int i=sInput.size();error_held && i>=0; i--)
    {
        if (b_char_is_space(sInput[i]) || b_char_is_operator(sInput[i]))
            if (reg!=REGISTER_DEFAULT_VALUE)
            {
                if (reg_is_string)
                {
                    int position = i_find_variable(reg);
                    if (position != -1)
                        error_held *= bAddExistingElement(vo_variables[position]);
                    else error_held *= bAddVariable(i_get_value_of_variable(reg), reg);
                } else error_held *= bAddNumber(stoi(reg));
                reg = REGISTER_DEFAULT_VALUE;
            }
        if (b_char_is_operator(sInput[i]))
            if(sInput[i]=='~')
                error_held *= bAddOperation(sInput[i], 1);
            else error_held *= bAddOperation(sInput[i]);
        else if (b_char_is_number(sInput[i]))
            if (reg!=REGISTER_DEFAULT_VALUE)
                if (reg_is_string)
                {
                    int position = i_find_variable(reg);
                    if (position != -1)
                        error_held *= bAddExistingElement(vo_variables[position]);
                    else error_held *= bAddVariable(i_get_value_of_variable(reg), reg);
                    reg = string(1, sInput[i]);
                    reg_is_string = NUMBER;
                } else reg = sInput[i] + reg;
            else
            {
                reg = string(1, sInput[i]);
                if (reg_is_string)
                    reg_is_string = NUMBER;
            }
        else if (b_char_is_letter(sInput[i]))
            if (reg!=REGISTER_DEFAULT_VALUE)
                if (reg_is_string)
                    reg = sInput[i] + reg;
                else
                {
                    error_held *= bAddNumber(stoi(reg));
                    reg = string(1, sInput[i]);
                    reg_is_string = VARIABLE;
                }
            else
            {
                reg = string(1, sInput[i]);
                if (reg_is_string!=VARIABLE)
                    reg_is_string = VARIABLE;
            }
    }
    if (reg!=REGISTER_DEFAULT_VALUE)
        if(reg_is_string)
        {
            int position = i_find_variable(reg);
            if (position != -1)
                error_held *= bAddExistingElement(vo_variables[position]);
            else error_held *= bAddVariable(i_get_value_of_variable(reg), reg);
        }else error_held *= bAddNumber(stoi(reg));
    return error_held;
}//bool CTree::b_initialize_body(string sInput)

bool CTree::b_add_element_body(CNode* poCurrentElement, char cOperation, int iCustomCountOfChildren)
{
    if(poCurrentElement==NULL)
    {
        v_log_add("OPAPAPA: NULL przy dodawaniu elementu");
        return false;
    }
    if (poCurrentElement->bIsChildLess())
        return false;
    for (int i=0; i<poCurrentElement->iGetCountOfChildren(); i++)
    {
        if (poCurrentElement->vecGetChildren()[i]==NULL)
        {
            v_log_add(EVENT_CODE_ADD, string(1,cOperation));
            poCurrentElement->vecGetChildren()[i] = new COperator(cOperation, iCustomCountOfChildren);
            return true;
        }
        else if (b_add_element_body(poCurrentElement->vecGetChildren()[i], cOperation, iCustomCountOfChildren))
            return true;
    }
    return false;
}//bool b_add_element_body(char cOperation);

bool CTree::b_add_element_body(CNode* poCurrentElement, int iValue)
{
    if(poCurrentElement==NULL)
    {
        v_log_add("OPAPAPA: NULL przy dodawaniu");
        return false;
    }
    if (poCurrentElement->bIsChildLess())
        return false;
    for (int i=0; i<poCurrentElement->iGetCountOfChildren(); i++)
        if (poCurrentElement->vecGetChildren()[i]==NULL)
        {
            v_log_add(EVENT_CODE_ADD, to_string(iValue));
            poCurrentElement->vecGetChildren()[i] = new CNumber(iValue);
            return true;
        }
        else if (b_add_element_body(poCurrentElement->vecGetChildren()[i], iValue))
            return true;
    return false;
}//bool b_add_element_body(int iValue);

bool CTree::b_add_element_body(CNode* poCurrentElement, int iValue, string sName)
{
    if(poCurrentElement==NULL)
    {
        v_log_add("OPAPAPA: NULL przy dodawaniu");
        return false;
    }
    if (poCurrentElement->bIsChildLess())
        return false;
    for (int i=0; i<poCurrentElement->iGetCountOfChildren(); i++)
    {
        if (poCurrentElement->vecGetChildren()[i]==NULL)
        {
            CVariable* temp = new CVariable(iValue, sName);
            poCurrentElement->vecGetChildren()[i] = temp;
            v_log_add(EVENT_CODE_ADD, sName);
            vo_variables.push_back(temp);
            return true;
        }
        else if (b_add_element_body(poCurrentElement->vecGetChildren()[i], iValue, sName))
            return true;
    }
    return false;
}//bool b_add_element_body(int iValue, string sName);

bool CTree::b_add_existing_element_body(CNode* poCurrentElement, CNode* poExistingElement)
{
    if(poCurrentElement==NULL)
    {
        v_log_add("OPAPAPA: NULL przy dodawaniu");
        return false;
    }
    if (poCurrentElement->bIsChildLess())
        return false;
    for (int i=0; i<poCurrentElement->iGetCountOfChildren(); i++)
    {
        if (poCurrentElement->vecGetChildren()[i]==NULL)
        {
            poCurrentElement->vecGetChildren()[i] = new CVariable(((CVariable*)poExistingElement)->iGetValue(), ((CVariable*)poExistingElement)->sGetName());
            v_log_add(EVENT_CODE_ADD_EXISTING, poExistingElement->sGetName());
            return true;
        }
        else if (b_add_existing_element_body(poCurrentElement->vecGetChildren()[i], poExistingElement))
            return true;
    }
    return false;
}//bool CTree::b_add_existing_element_body(CNode* poCurrentElement, CNode* poExistingElement)

double CTree::d_count_body(CNode* poCurrentElement)
{
    if (poCurrentElement!=NULL)
    {
        if (poCurrentElement->bIsOperator())
        {
            if (poCurrentElement->sGetName()==ADDITION)
                return d_count_body(poCurrentElement->vecGetChildren()[1]) + d_count_body(poCurrentElement->vecGetChildren()[0]);
            if (poCurrentElement->sGetName()==SUBTRACTION)
                return d_count_body(poCurrentElement->vecGetChildren()[1]) - d_count_body(poCurrentElement->vecGetChildren()[0]);
            if (poCurrentElement->sGetName()==MULTIPLICATION)
                return d_count_body(poCurrentElement->vecGetChildren()[1]) * d_count_body(poCurrentElement->vecGetChildren()[0]);
            if (poCurrentElement->sGetName()==DIVISION)
                return d_count_body(poCurrentElement->vecGetChildren()[1]) / d_count_body(poCurrentElement->vecGetChildren()[0]);
            if (poCurrentElement->sGetName()==TILDE)
                return d_count_body(poCurrentElement->vecGetChildren()[0]) * -1;
        }
        if (poCurrentElement->bIsVariable())
            return ((CVariable*)poCurrentElement)->iGetValue();
        if (poCurrentElement->bIsNumber())
            return ((CNumber*)poCurrentElement)->iGetValue();
    }
    v_log_add(EVENT_CODE_COUNT_FAILURE, "");
    return 0;
}//double CTree::d_count_body(CNode* poCurrentElement)

int CTree::i_get_value_of_variable(string sName)
{
    cout << "Prosze wpisac znaczenie zmiennej '" + sName + "': ";
    string s_answer;
    cin >> s_answer;
    int i_answer;
    try
    {
        i_answer = stoi(s_answer);
        return i_answer;
    }catch (exception)
    {
        cout << "Wpisane znaczenie jest niepoprawne. Sproboj jeszcze raz." << endl;
        return i_get_value_of_variable(sName);
    }
}//int CTree::i_get_value_of_variable(string sName)

void CTree::v_log_add(string sEvent)
{
    s_log+="~~" + sEvent + "\n";
}//void v_log_add

void CTree::v_log_add(int iEventCode, string sValue)
{
    if (iEventCode == EVENT_CODE_ROOT_DELETED)
        v_log_add("Korzen drzewa zostal usuniety, zeby utworzyc nowe drzewo z wyrazu '" + sValue + "'");
    if (iEventCode == EVENT_CODE_ADD_ACCESSORIAL_NUMB)
        v_log_add("Wyraz zostal dopelniony przez dodawania elementu '" + sValue + "'");
    if (iEventCode == EVENT_CODE_ADD_EXISTING)
        v_log_add("Juz istniejacy element '" + sValue + "' zostal skopiowany w inne miejsce");
    if (iEventCode == EVENT_CODE_ADD)
        v_log_add("Element '" + sValue + "' zostal dodany");

    if (iEventCode == EVENT_CODE_TREE_CREATED)
        v_log_add("Zostalo utworzone puste drzewo");

    if (iEventCode == EVENT_CODE_ADD_FAILURE)
        v_log_add("Nieudana proba dodawania elementu '" + sValue + "'");
    if (iEventCode == EVENT_CODE_EMPTY_TREE)
        v_log_add("Zostala wykonana proba operacji na pustym drzewie");
    if (iEventCode == EVENT_CODE_NOT_EMPTY_TREE)
        v_log_add("Zostala wykonana proba operacji na niepustym drzewie");
    if (iEventCode == EVENT_CODE_INPUT_PARSING_FAILURE)
        v_log_add("Zostal pokonany blad przy odczycie wyrazu -> Inicjalizacja przerwana");
    if (iEventCode == EVENT_CODE_AFTER_INPUT_FAILURE)
        v_log_add("Brak zmiennych lub/oraz liczb w wyrazeniu");
    if (iEventCode == EVENT_CODE_COUNT_FAILURE)
        v_log_add("Przy obliczeniu wystapil NULL -> zamieszczony przez 0");
    if (iEventCode == EVENT_CODE_NORMILIZE_FAILURE)
        v_log_add("Przekroczony zakres prob dla normalizacji drzewa");
    if (iEventCode == EVENT_CODE_UNKNOWN_FAILURE)
        v_log_add("WYSTAPIL NIEWIADOMY DOTYCHCZAS BLAD");
}//void CTree::v_log_add(int iEventCode, string sValue)

string CTree::s_add_accessorial_numb(int iNumb, string sInput)
{
    return to_string(iNumb) + " " + sInput;
}//void CTree::v_add_accessorial_numb(int iNumb)

void CTree::v_print_levels_body(vector<CNode*>& queue, int iLevel)
{

    int i_count = queue.size();
    cout << iLevel << ".  ";
    int i_index;
    while(--i_count>=0)
    {
        cout << "'" << queue[0]->sGetName() << "'  ";
        if (!queue[0]->bIsChildLess())
            for (i_index=queue[0]->iGetCountOfChildren()-1; i_index>=0; i_index--)
                queue.push_back(queue[0]->vecGetChildren()[i_index]);
        queue.erase(queue.begin());
    }
    cout << endl;
    if (!queue.empty())
        v_print_levels_body(queue, iLevel + 1);

}//void CTree::v_print_levels_body(vector<CNode*>& queue, int iLevel)

void CTree::v_print_postfix_body(CNode* poCurrentElement)
{
    if (poCurrentElement!=NULL)
    {
        for (int i=poCurrentElement->iGetCountOfChildren()-1; i>=0; i--)
            v_print_postfix_body(poCurrentElement->vecGetChildren()[i]);
        cout << poCurrentElement->sGetName() + " ";
    }
}//void CTree::v_print_postfix_body(CNode* poCurrentElement)

string& CTree::s_infix_body(CNode* poCurrentElement, string& sResult)
{
   if (poCurrentElement->iGetCountOfChildren()==0)
       sResult+=poCurrentElement->sGetName();
    else
   {
       sResult+='(';
       s_infix_body(poCurrentElement->vecGetChildren()[poCurrentElement->iGetCountOfChildren()-1], sResult);
       sResult+=poCurrentElement->sGetName();
       for (int i=poCurrentElement->iGetCountOfChildren()-2; i>=0; i--)
           s_infix_body(poCurrentElement->vecGetChildren()[i],sResult);
       sResult+=')';
   }
    return sResult;
}//string CTree::s_infix_body(CNode *poCurrentElement)

int CTree::i_find_variable(string sName)
{
    int position = -1;
    for (int i=0; position==-1 && i<vo_variables.size(); i++)
        if (vo_variables[i]->sGetName() == sName)
            position = i;
    return position;
}//bool CTree::b_variable_insist(string sName)

bool CTree::b_test_tree(CNode* poCurrentElement)
{
    bool b_tree_is_ok = true;
    if (poCurrentElement == NULL)
        return false;
    if (poCurrentElement->bIsChildLess())
        return true;
    //cout << "Ilosc dzieci operatora '" << poCurrentElement->sGetName() << "' wynosi:" << poCurrentElement->iGetCountOfChildren() << endl;
    for (int i=0; i<poCurrentElement->iGetCountOfChildren(); i++)
        b_tree_is_ok = b_tree_is_ok && b_test_tree(poCurrentElement->vecGetChildren()[i]);
    return b_tree_is_ok;
}//bool CTree::b_test_tree(CNode* poCurrentElement)

bool CTree::b_char_is_operator(char cChar)
{
    return cChar == '-' || cChar ==  '+' || cChar ==  '/' || cChar == '~' || cChar == '*';
}//bool b_char_is_operator(char cChar);

bool CTree::b_char_is_number(char cChar)
{
    return cChar >=FIRST_NUMBER_IN_ASCII && cChar <= LAST_NUMBER_IN_ASCII;
}//bool b_char_is_letter(char cChar);

bool CTree::b_char_is_letter(char cChar)
{
    return (cChar >= FIRST_BIG_LETTER_IN_ASCII && cChar <= LAST_BIG_LETTER_IN_ASCII) || (cChar >= FIRST_SMALL_LETTER_IN_ASCII && cChar <= LAST_SMALL_LETTER_IN_ASCII);
}//bool b_char_is_number(char cChar);

bool CTree::b_char_is_space(char cChar)
{
    return cChar == ' ';
}//bool b_char_is_space(char cChar)