#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QMenuBar>
#include <QLabel>
#include "mineMap.h"


namespace Ui {

class MainWindow;
class MyButton;
}


class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton( QWidget *parent = nullptr,int inde = 0);
    MyButton(const QString & text, QWidget *parent = nullptr,int inde = 0);
protected:
    void mousePressEvent(QMouseEvent *event) override;
private:
    int buttonIndex;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //function
    void OpenButton(int num,bool type = false);
    void SetGame(int rowNum,int colNum,int mineNum);
private:
    bool over;
    MyButton **m_button;
    MineMap *mymine;
    int blockSize;
    QMenu *restart;
    QAction *largeAct,*mediumAct,*smallAct;
    QLabel *endText;
    // function about open block
    void OpenRecBlock(int r,int c);// for open (r,c) block after we use openbutton
    void GameOver();
    void SetEndText();
};



#endif // MAINWINDOW_H
