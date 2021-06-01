#ifndef MYHTTP_H
#define MYHTTP_H

#include <QTcpSocket>

class MyHttp : public QTcpSocket
{
public:
    MyHttp();
    ~MyHttp();

public:
    //获取网络中文件列表，URF+端口
    QString getFileList(QString URL,int port);



};

#endif // MYHTTP_H
