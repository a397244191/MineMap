#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mineMap.h"
#include <iostream>
#include <QString>
#include <QMouseEvent>

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_button(nullptr),mymine(nullptr),blockSize(0)
{
    endText = new QLabel("WWWWW",this);
    endText->setGeometry(0,30,400,100);
    restart = menuBar()->addMenu(tr("&Restart"));
    largeAct = new QAction(tr("&Large"), this);
    mediumAct = new QAction(tr("&Medium"), this);
    smallAct = new QAction(tr("&Small"), this);
    connect(largeAct, &QAction::triggered, this, [ = ] {SetGame(16,30,99);});
    connect(mediumAct, &QAction::triggered, this, [ = ] {SetGame(16,16,40);});
    connect(smallAct, &QAction::triggered, this, [ = ] {SetGame(9,9,10);});
    restart->addAction(largeAct);
    restart->addAction(mediumAct);
    restart->addAction(smallAct);
    SetGame(16,30,99);
}


void MainWindow :: SetGame(int rowNum,int colNum,int mineNum){
    over = false;
    endText->setText("");
    int sizeEveryBlock = 30;
    for(int i = 0;i<blockSize ; i++) {
        delete m_button[i];
    }
    delete m_button;
    delete mymine;
    int leftup[2] = {10,100};
    this->resize(colNum*sizeEveryBlock+2*leftup[0],rowNum*sizeEveryBlock+leftup[1]+10);
    mymine = new MineMap(rowNum,colNum,mineNum);
    blockSize = rowNum * colNum;
    m_button = new MyButton*[blockSize];
    for(int i = 0 ; i < blockSize ; i++){
        m_button[i] = new MyButton("",this,i);
        m_button[i]->setGeometry(QRect(QPoint(leftup[0]+(i%colNum)*sizeEveryBlock, leftup[1]+(i/colNum)*sizeEveryBlock),QSize(sizeEveryBlock, sizeEveryBlock)));
        m_button[i]->setCheckable(true);
        m_button[i]->show();
    }
}

MainWindow::~MainWindow()
{
    for(int i = 0;i<blockSize ; i++) delete m_button[i];
    delete m_button;
    delete mymine;
}
void MainWindow:: OpenButton(int num,bool type){
    int r = num / mymine->GetCol(),c = num % mymine->GetCol();
    if(!type){
        mymine->SetType(r,c,1);
        OpenRecBlock(r,c);
    } else if(type) {
        if(mymine->GetBlockType(num) == 0){
            mymine->SetType(r,c,2);
            m_button[num]->setText("O");
        }else {
            mymine->SetType(r,c,3);
            m_button[num]->setText("");
        }
    }
}
void  MainWindow:: OpenRecBlock(int r,int c){
    int rNum = mymine->GetRow(),cNum = mymine->GetCol();
    int ind = mymine->GetStatic(r,c);
    if(r < 0 || r >= rNum || c < 0 || c >= cNum || !(m_button[ind]->isEnabled()))return;//have opened
    m_button[ind]->setEnabled(false);
    m_button[ind]->setChecked(true);
    int dispNum = mymine->GetBlockNum(r,c);
    if(dispNum == -1) {
        m_button[ind]->setText("X");
        GameOver();
    }
    else if(dispNum != 0) m_button[ind]->setText(QString((char)(dispNum+'0')));
    else{
        m_button[ind]->setText("");
        for(int i = 0 ; i < 9 ; i++) OpenRecBlock( r+(i/3-1),c +(i%3-1));
    }
    if(mymine->GetCloseNum() == 0) GameOver();
}

void MainWindow :: GameOver() {
    if(over) return;
    over = true;
    SetEndText();
    for(int i = 0 ; i < blockSize ; i++)
        OpenButton(i);
}

void MainWindow :: SetEndText()
{
    if(mymine->GetCloseNum() == 0){
        endText->setFont(QFont("Timer", 28, QFont::Bold));
        endText->setText("Congratulation!");
        endText->setStyleSheet("color:green;");
    }else{
        endText->setFont(QFont("Timer", 28, QFont::Bold));
        endText->setText("Game Over");
        endText->setStyleSheet("color:red;");
    }
}

MyButton :: MyButton( QWidget *parent,int inde) : QPushButton(parent), buttonIndex(inde){}
MyButton :: MyButton(const QString & text, QWidget *parent,int inde) : QPushButton(text,parent), buttonIndex(inde){}



void MyButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        ((MainWindow*)parentWidget())->OpenButton(buttonIndex);
    } else if(event->button() == Qt::RightButton){
        ((MainWindow*)parentWidget())->OpenButton(buttonIndex,true);
    }

}
