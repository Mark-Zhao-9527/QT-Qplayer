#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QVideoWidget>
#include <QMediaPlayer>
#include <QDebug>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QMediaPlayer *mediaPlayer; //QVideoWidget,在这个界面播放

private slots:
    //播放
    void play();
    //播放状态
    void mediaStateChanged(QMediaPlayer::State state);
    //改变播放进度位置
    void postionChanged(qint64 position);
    //获取播放位置
    void setPosition(int postion);
    //获取播放长度
    void durationChanged(qint64 duration);
    //播放异常的抛出
    void handleError();
    //从服务器获取信息
    void getFile();
    //创建listwidgett条目item 添加条目名称
    void createItem(QString itemName);
    //处理item的响应事件
    void itemDoubleClick(QListWidgetItem  *item);

    //UI自动槽函数
    void on_toolButton_clicked();
    void on_horizontalSlider_sliderMoved(int position);
    void on_toolButton_2_clicked();
    void on_toolButton_3_clicked();




};
#endif // MAINWINDOW_H
