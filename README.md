# QT-Qplayer
**快播播放器的小DEMO**  
程序功能：可以播放本地视频;也可以播放远程服务器的视频。    
**本程序在QT5上运行成功。如果您运行不成功，请修改下项目文件（Qplayer.pro）中的编译位置，当然一般什么都不用修改。**     

运行中错误及修正办法：    
1）选择视频时出错如下错误代码：  
doRender: Unresolved error code 0x80040266   
请解压安装《2.Gadgets》中的小插件，它是个DirectShow解码器。    
安装后就能正常播放各类视频。
  
2）如下错误代码：  
doSetUrlSource: Unresolved error code 0x80004005  
请检查文件路径。注意文件路径不能有中文。
  
***如果您下载了，请帮忙在本页右上角点下star哈!***  

写在最后：为了方便各位朋友的对比借鉴引用，本程序后期不再更新。若想结合某视频学习，这个版本是最适合的。  
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 若想要功能更完善且完全不一样的播放器，请关注本人主页另一个仓库“Qt-XtPlayer"。
