#include "Global.h"

string sudokupath=R"(./Assignment1_InputOutput/Problem_6.txt)";
string resultpath=R"(./Assignment1_InputOutput/Result_6.txt)";
string sudokucnf=R"(./Assignment1_InputOutput/sudokucnf_6.cnf)";
string resultcnf=R"(./Assignment1_InputOutput/resultcnf_6.cnf)";

int row=16;
int col=16;

int padding=0;

int** sudokuArray=new int*[row];