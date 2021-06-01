#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDialog>
#include "myhttp.h"
#include <QListWidgetItem>

//进一步添加的需求
//1、抛出播放异常
//2、通过打开文件获取播放的视频
//3、界面缩放


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置主界面背景
    //QPixmap pixmap(":/images/background.png");
    QPixmap pixmap(":/images/background1.png");
    QPalette palette;
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);

    //设置listwidget的背景颜色
    ui->listWidget->setStyleSheet("QlistView{selection-background-color:rgba(0,0,0,20);selection-color:white;}");
    //设置listwidget的背景透明
    ui->listWidget->setStyleSheet("background-color:transparent");
    //设置listwidget的背景灰色
    ui->listWidget->setStyleSheet("background-color:gray");


    //创建mediaPlayer
    mediaPlayer = new QMediaPlayer(this);
    //设置mediaplayer的QVideoWidget 即播放窗口
    mediaPlayer->setVideoOutput(ui->widget);


    //设置播放属性
    //1、监听信号变化函数
    connect(mediaPlayer,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(mediaStateChanged(QMediaPlayer::State))); //播放状态变化
    //2、播放进度信号变化函数
    connect(mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(postionChanged(qint64))); //播放进度变化
    //3、媒体播放信号长度变化
    connect(mediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64))); //信号长度
    //4、设置播放错误关联
    connect(mediaPlayer,SIGNAL(error(QMediaPlayer::Error)),this,SLOT(handleError()));

    //设置播放内容  //调试用，程序开启时就加载文件，后面放在打开文件中按钮后播放
    //mediaPlayer->setMedia(QUrl::fromLocalFile("E:/dayu.mkv"));

    //设置播放按钮
    ui->toolButton->setToolTip("播放");
    ui->toolButton->setAutoRaise(true);//autoRaise属性表示toolButton按钮是否自动凸出
    ui->toolButton->setIcon(QPixmap(":/images/play.png"));

    //设置打开文件按钮
    ui->toolButton_2->setToolTip("打开文件");
    ui->toolButton_2->setAutoRaise(true);//autoRaise属性表示toolButton按钮是否自动凸出
    ui->toolButton_2->setIcon(QPixmap(":/images/openfile.png"));

    //设置打开文件按钮
    ui->toolButton_3->setToolTip("全屏");
    ui->toolButton_3->setAutoRaise(true);//autoRaise属性表示toolButton按钮是否自动凸出
    ui->toolButton_3->setIcon(QPixmap(":/images/fullscreen.png"));

    //从服务器获取文件列表
    getFile(); //在局域网内服务器内开启程序的情况下，可开启此函数中的myhttp，以获取服务器信息

    //设置item信号处理事件
     connect(ui->listWidget,&QListWidget::itemDoubleClicked,this,[=](QListWidgetItem  *item){
         itemDoubleClick(item);
        });

}

MainWindow::~MainWindow()
{
    delete ui;
}

//播放
void MainWindow::play()
{
    //获取播放状态
    switch(mediaPlayer->state()){
    case QMediaPlayer::PlayingState:
         mediaPlayer->pause();
         break;
    default:
         mediaPlayer->play();
        break;
    }
}

//播放状态  //mediaplay播放过程中动态调整播放进度
void MainWindow::mediaStateChanged(QMediaPlayer::State state)
{
    switch (state) {
    case QMediaPlayer::PlayingState:
        ui->toolButton->setToolTip("暂停");
        ui->toolButton->setIcon(QPixmap(":/images/pause.png"));
        break;
    default:
        ui->toolButton->setToolTip("播放");
        ui->toolButton->setIcon(QPixmap(":/images/play.png"));
        break;
    }
}

//改变播放进度位置
void MainWindow::postionChanged(qint64 position)
{
    ui->horizontalSlider->setValue(position);
}

//获取播放位置
void MainWindow::setPosition(int postion)
{
    mediaPlayer->setPosition(postion);
}

//获取播放长度（进度条的范围）
void MainWindow::durationChanged(qint64 duration)
{
    ui->horizontalSlider->setRange(0,duration);
}

//播放异常的抛出
void MainWindow::handleError()
{
    //如果出现错误播放不了
    ui->toolButton->setEnabled(false);
    qDebug() << "有错误发生了！";
}

//播放按钮动作时执行
void MainWindow::on_toolButton_clicked()
{
    play();

    //需要设置按钮暂停样式
    ui->toolButton->setToolTip("暂停");
    ui->toolButton->setIcon(QPixmap(":/images/pause.png"));


}

//进度条的变化
void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    setPosition(position);
}


//打开文件按钮
void MainWindow::on_toolButton_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName();
    //设置播放内容
    //mediaPlayer->setMedia(QUrl::fromLocalFile("E:/dayu.mkv"));
    mediaPlayer->setMedia(QUrl::fromLocalFile(filename));

    //打开立即开如播放
    play();
}

//开始全屏，暂时使用CTR+D 或 table 到桌面退出,以后有时间再添加鼠标事件
void MainWindow::on_toolButton_3_clicked()
{
    //方式一，全屏
    ui->widget->setFullScreen(true);
    //方式二
    //ui->widget->setAutoFillBackground(true);
}


//通过http请求获取服务端口server中的某个的文件列表
void MainWindow::getFile()
{
    MyHttp http;
    QString content;
    //content = http.getFileList("192.168.191.5",80); //此行在有局域网服务器的情况下开启执行
    //如果有服务器存在，刚屏蔽下行语句,使用上行语句起作用。
    content = "《魔兽世界：巫妖王之怒》开场动画CG.mkv\ndg.mkv";

    //qDebug() << content; //调试输出

    //获取到的服务器内的内容
    //将资源列表中的内容变成 listwidget中的条目 item
    QStringList ls = content.split("\n");
    for (int i=0;i<ls.count();i++) {
        qDebug() << ls[i];
        if(!ls[i].isEmpty())   //如果内容不为空，则显示
            createItem(ls[i]);
    }
}

//创建listWidget的item条目
void MainWindow::createItem(QString itemName)
{
    //创建item条目
    QListWidgetItem  * item = new QListWidgetItem(itemName);
    //设置item水平居中对齐
    item->setTextAlignment(Qt::AlignHCenter);
    //添加到界面中
    ui->listWidget->addItem(itemName);
}

//处理item的响应事件
void MainWindow::itemDoubleClick(QListWidgetItem  *item)
{
    //获取播放的url地址，根据地址打开播放的文件
    QUrl url;
    url.setUrl("http://192.168.191.5:80m/mv/" + item->text());

    //如果有服务器存在，刚屏蔽下行语句,使用上行语句起作用。本行语句仅为说明条目双击是有作用的
    url.setUrl("F:/zhao_QT/13_Qplayer/build-Qplayer-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/" + item->text());

    //设置mediaplayer播放内容
    mediaPlayer->setMedia(url);
    //打开立即开如播放
    play();
}








