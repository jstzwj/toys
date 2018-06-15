#ifndef WEBDIALOG_H
#define WEBDIALOG_H

#include<QUrl>
#include<QWebEngineView>
#include<QMainWindow>
#include<QGridLayout>
class WebDialog : public QMainWindow
{
    Q_OBJECT
public:
    WebDialog(QWidget * parent=Q_NULLPTR,const QUrl &url=QUrl("https://www.zhihu.com/"));
    QWebEngineView * webDialog;
    QGridLayout * gridlayout;
public slots:
    void readyClose();
};

#endif // WEBDIALOG_H
