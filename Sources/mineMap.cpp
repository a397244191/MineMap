#include "mineMap.h"
#include <iostream>
#include <locale>
#include <cstdlib>

using namespace std;

MineMap :: MineMap():closeNum(0),gameState(false),row(0),col(0),block(NULL){}
MineMap :: MineMap(int rowNum,int colNum,int mineNum){
    if(mineNum >= rowNum * colNum){
        cerr << "All blocks are mine." << endl;
        mineNum = (rowNum * colNum) / 8;
        cerr << "we set the mineNum = " << mineNum << "." << endl;
    } else if(rowNum < 5 || colNum < 5) {
        cerr << "Too small, set the small size." << endl;
        rowNum = colNum = 9;
        mineNum = 10;
    } else if(rowNum >100 || colNum > 100) {
        cerr << "Too large, set the large size." << endl;
        rowNum = 30;
        colNum = 16;
        mineNum = 99;
    }
    this->SetNewGame(rowNum, colNum, mineNum);
}
// small 9*9 in 10, medium 16*16 in 40, large 16*30 in 99
MineMap :: MineMap(string sizeName){
    for(int i = 0 ; i < (int)sizeName.length() ; i++)
        if(sizeName[i]<='Z' && sizeName[i] >= 'A')
            sizeName[i] = tolower(sizeName[i]);
    if(!sizeName.compare(1,6,"medium"))
        this->SetNewGame(16, 16, 40);
    else if(!sizeName.compare(1,5,"large"))
        this->SetNewGame(16, 30, 99);
    else{// other all is define to small
            if(!sizeName.compare(1,5,"small"))
                cerr << "the name is not small/medium/large, we define the size is small" << endl;
            this->SetNewGame(9, 9, 10);   
    }
}

MineMap :: MineMap(bool* array,int rowNum,int colNum,int mineNum) {
    this->closeNum = rowNum * colNum - mineNum;
    this->gameState = false;
    this->row = rowNum;
    this->col = colNum;
    this->block = new char[rowNum * colNum];
    for(int i = 0 ; i < rowNum*colNum ; i++)
        if(array[i])this->block[i] = (char)MINEEXIST;
        else this->block[i] = (char)0;
    this->CalculateMine();
}
//get function
int MineMap :: GetRow(){return this->row;}
int MineMap :: GetCol(){return this->col;}
int MineMap :: GetGameState(){return this->gameState;}
int MineMap :: GetCloseNum(){return this->closeNum;}
int MineMap :: GetBlockType(int r,int c){return (int)(this->block[GetStatic(r,c)] & GETTYPE);}
int MineMap :: GetBlockNum(int r, int c){
    if(this->block[GetStatic(r,c)]&MINEEXIST)
        return -1;
    else
        return (int)(((this->block[GetStatic(r,c)] & GETNUM)>>2));
}
int MineMap :: GetBlockType(int ind){return (int)(this->block[ind] & GETTYPE);}
int MineMap :: GetBlockNum(int ind){
    if(this->block[ind]&MINEEXIST)
        return -1;
    else
        return (int)(((this->block[ind] & GETNUM)>>2));
}
int MineMap :: GetStatic(int r,int c){return r * this->GetCol() + c;}
//set function
void MineMap :: SetNewGame(int rowNum,int colNum,int mineNum){
    this->closeNum = rowNum * colNum - mineNum;
    this->gameState = false;
    this->row = rowNum;
    this->col = colNum;
    this->block = new char[rowNum * colNum];
    this->PushMine(mineNum);
    this->CalculateMine();
}
void MineMap :: SetType(int r,int c,int type){//type 1 to open 2 to mark, 3 to clean
    if((this->block[GetStatic(r,c)] & 1)){
    } else {
        if(type == 1) OpenBlock(r,c);
        else if(type == 2) this->block[GetStatic(r,c)] |= 2;//10 mark
        else if(type == 3) this->block[GetStatic(r,c)] &= OTHERNUM;
    }
}
//destruct
MineMap :: ~MineMap(){
    delete []this->block;
}
// method
void MineMap :: PushMine(int mineNum){
    int total = this->GetRow() * this->GetCol();
    for(int i = 0 ; i < total ; i++)
        if(i < mineNum)this->block[i] = (char)MINEEXIST;
        else this->block[i] = (char)0;
    for(int i = 0 ; i < total ; i++) swap(this->block[i],this->block[(rand() % (total - i)) + i]);
}

void MineMap :: CalculateMine(){
    int total = this->GetRow() * this->GetCol();
    for(int i = 0 ; i < total ; i++) {
        int r = i/this->GetCol(),c = i%this->GetCol();
        int mineNum = 0;
        for(int j = 0 ; j < 9 ; j++)
            if(j == 4);//(r,c) block, nothing
            else if(GetMineorNot(r + j%3-1,c + j/3-1)) mineNum ++;
        this->block[i] |= (char)((mineNum)<<2);
    }
}

bool MineMap :: GetMineorNot(int r,int c) {
    if(r < 0 || r >= this->row || c < 0 || c >= this->col) return false;
    else return (this->block[GetStatic(r,c)] & MINEEXIST );
}


void MineMap :: OpenBlock(int r,int c) {
    if(r < 0 || r >= this->row || c < 0 || c >= this->col || (this->block[GetStatic(r,c)] & 1)) return;
    this->block[GetStatic(r,c)] = (this->block[GetStatic(r,c)] & OTHERNUM) | 1;//01 open
    if ((this->block[GetStatic(r,c)] & MINEEXIST)){
        this->gameState = (char)1;// 1 == gameover
        return;
    }
    
    closeNum --;// open a block
    if((this->block[GetStatic(r,c)] & GETNUM)) return ;
    for(int i = 0 ; i < 9 ; i++)
        OpenBlock(r + i%3-1,c + i/3-1);
}
