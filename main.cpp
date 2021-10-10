#include "Global.h"

int main(int argc,char** argv){
    Start();
    ReadSudoku();
    ShowSudoku();
    ToCnf();
    CallMiniSAT();
    ReadResult();
    ShowSudoku();
    DeleteSudoku();
    return 0;
}