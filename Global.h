#ifndef WORKSHOP_GLOBAL_H
#define WORKSHOP_GLOBAL_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <assert.h>
#include <cmath>
#include <unistd.h>

using namespace std;

extern string sudokupath;//初始化的数独文件路径
extern string resultpath;//最后生成的数独文件路径
extern string sudokucnf;//转化成cnf文件路径
extern string resultcnf;//minisat求解结果保存的文件路径
extern int row,col;
extern int** sudokuArray;
extern int padding;

void Start();
void ReadSudoku();
void WriteSudoku();
void DeleteSudoku();
void ShowSudoku();
void ToCnf();
void CallMiniSAT();
void ReadResult();

#endif // !WORKSHOP_GLOBAL_H