#include <DisplayTree.h>
#include "ui_DisplayTree.h"
#include <QtOpenGL>
#include <iostream>

vector<node*> tree;
int dep;
int w=800;
int h=600;
std::vector<std::string> attributes;

void paintNode(QPainter &p, int x, int y,bool isLeaf);
int paintTree(QPainter &p,int x, int y,int index);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(w,h);
}


void MainWindow::getTree(vector<node*> &t,int d){
    tree = t;
    dep=d;
    cout<<dep<<endl;
    /*for(int i=0;i<(int)tree.size();i++){
        cout<<tree[i]->median<<endl;
    }*/
}

void MainWindow::getAttributes(std::vector<std::string> att){
    attributes=att;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void QWidget::paintEvent(QPaintEvent*){
    QPainter p;
    p.begin(this);
    paintTree(p,w/2,10,0);
    p.end();
}

int paintTree(QPainter &p,int x, int y,int index){
    bool isLeaf=tree[index]->median==-1;
    paintNode(p,x-45,y,isLeaf);
    if(isLeaf){
        return index;
    }else{
        int left=paintTree(p,x-45,y+90,index+1);
        return paintTree(p,x+45,y+90,left+1);
    }
}

void paintNode(QPainter &p, int x, int y,bool isLeaf){
    p.drawEllipse(x+15,y+10,60,60);
    p.drawLine(x+45,y,x+45,y+10);
    QRectF rectangle(0,y+20,90,40);
    p.fillRect(rectangle,Qt::white);
    if(!isLeaf){
        p.drawLine(x+45,y+70,x+45,y+90);
    }

}

