#include "Global.h"

//读取初始数独
void ReadSudoku(){
    ifstream fin(sudokupath.c_str());
    assert(fin.is_open());
    for(int i=0;i<row;i++){
        sudokuArray[i]=new int[col];
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            fin >> sudokuArray[i][j];
            if(sudokuArray[i][j]!=0) padding++;
        }
    }
    fin.close();
}

//写入最终的数独
void WriteSudoku(){
    ofstream fout(resultpath.c_str());
    assert(fout.is_open());
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            fout<<sudokuArray[i][j]<<" ";
        }
        fout<<endl;
    }
    fout.close();
}

//删除动态开辟的空间
void DeleteSudoku(){
    for(int i=0;i<row;i++){
        delete[] sudokuArray[i];
    }
    delete[] sudokuArray;
}

//将数独打印在屏幕上
void ShowSudoku(){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cout<<sudokuArray[i][j]<<" ";
        }
        cout<<endl;
    }
}

//转化成SAT输入格式文件
void ToCnf(){
    ofstream cnfout(sudokucnf.c_str());
    assert(cnfout.is_open());
    long valNum=row*row*row;
    long clauseNum=padding+row*row*3+row*row*row*row;
    cnfout<<"p"<<" "<<"cnf"<<" "<<valNum<<" "<<clauseNum<<" "<<endl;
    //已经给出的数字，单子句需要被满足。
    for(int x=0;x<row;x++){
        for(int y=0;y<col;y++){
            if(sudokuArray[x][y]!=0){
                cnfout<<x*row*row+y*row+sudokuArray[x][y]<<" "<<0<<endl;
            }
        }
    }
    //每一行需要出现所有1到row的数字编码
    for(int x=0;x<row;x++){
        for(int n=1;n<=row;n++){
            for(int y=0;y<col;y++){
                cnfout<<x*row*row+y*row+n<<" ";
            }
            cnfout<<0<<endl;
        }
    }
    //每一列需要出现所有1到row的数字编码
    for(int y=0;y<col;y++){
        for(int n=1;n<=row;n++){
            for(int x=0;x<row;x++){
                cnfout<<x*row*row+y*row+n<<" ";
            }
            cnfout<<0<<endl;
        }
    }
    //每一个小正方形的区域需要出现所有1到row的数字编码
    int c=sqrt(row);
    for(int r=0;r<c;r++){
        for(int s=0;s<c;s++){
            for(int n=1;n<=row;n++){
                for(int i=0;i<c;i++){
                    for(int j=0;j<c;j++){
                        int x=c*r+i;
                        int y=c*s+j;
                        cnfout<<x*row*row+y*row+n<<" ";
                    }
                }
                cnfout<<0<<endl;
            }
        }
    }
    //每一个单元都不会出现超过一个数字
    for(int x=0;x<row;x++){
        for(int y=0;y<col;y++){
            for(int n=1;n<=row;n++){
                for(int m=1;m<=row;m++){
                    if(m!=n){
                        cnfout<<0-(row*row*x+row*y+n)<<" "<<0-(row*row*x+row*y+m)<<" "<<0<<endl;
                    }
                }
            }
        }
    }
    cnfout.close();
}

void CallMiniSAT(){
    ofstream resultout(resultcnf.c_str());
    assert(resultout.is_open());
    resultout.close();
    string toolName="minisat";
    string cmdstring=toolName+" "+sudokucnf+" "+resultcnf;
    int status=system(cmdstring.c_str());
    if(status==-1){//创建子进程失败
        perror("system error!\n");
        exit(EXIT_FAILURE);
    }else{
        if(WIFEXITED(status)){//shell脚本子进程正确退出
            if(WEXITSTATUS(status) == 0){//操作成功
                cout<<"run shell script successfully!"<<endl;
            }else{//操作失败
                cout<<"run shell script fail,script exit code is "<<WEXITSTATUS(status)<<endl;
            }
        }else{//shell脚本子进程错误退出
            cout<<"exit status = "<<WEXITSTATUS(status)<<endl;
        }
    }
}

void ReadResult(){
    ifstream fin(resultcnf.c_str());
    assert(fin.is_open());
    string res;
    getline(fin,res);
    if(res=="SAT"){
        long num,tmp;
        while(!fin.eof()){
            fin>>num;
            tmp=num;
            int x,y,z;
            if(num>0){
                if(num%(row*row)==0){
                    x=num/(row*row)-1;
                }else x=num/(row*row);
                num-=x*(row*row);
                if(num%row==0){
                    y=num/row-1;
                }else y=num/row;
                z=tmp-x*(row*row)-y*row;
                sudokuArray[x][y]=z;
            }
        }
        WriteSudoku();
    }
    fin.close();
}


