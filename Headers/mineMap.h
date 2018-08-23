#ifndef MINE_HEADER_FILE
#define MINE_HEADER_FILE
#include <string>
#define MINEEXIST 64 //1000000
#define GETTYPE 3//0000011
#define OTHERNUM 124//1111100
#define GETNUM 60//0111100

class MineMap{
    public:
    //construct
        MineMap();
        MineMap(int rowNum,int colNum,int mineNum);
        MineMap(std::string sizeName);
        MineMap(bool* array,int rowNum,int colNum,int mineNum);// for test use
    //get function
        int GetRow();
        int GetCol();
        int GetGameState();
        int GetCloseNum();
        int GetBlockType(int r,int c);
        int GetBlockNum(int r, int c);
        int GetBlockType(int ind);
        int GetBlockNum(int ind);
        int GetStatic(int r,int c);// get r * col + c
    //set function
        void SetNewGame(int rowNum,int colNum,int mineNum);//reset a New minemap
        void SetType(int r,int c,int type);//set the (r,c) block (close/mark to)open or (close to)mark
    //destruct
        ~MineMap();
    private:
    // value we need
        int closeNum;// the number of block that is not mine
        char gameState;//0 continue, 01 game over 10 success end 
        int row,col;//the size of minemap
        char* block;
        /* 0(not use) 0(mine) 0000(number) 00(type) from last, the first 2 bit is close(00)/open(01)/mark(10),
          the last three bit is the number of mine near block(0~8)
          the seventh bit mean that it's mine or not
        */
    // method
        void PushMine(int mineNum);//random push MineNum mines into Minemap
        void CalculateMine();//After initating the minemap, calculate the number mine near this block for every block
        bool GetMineorNot(int r,int c);//Check (r,c) is mine or not
        void OpenBlock(int r,int c);//open the (r,c) block, if no mine near this block, open them
};
#endif
