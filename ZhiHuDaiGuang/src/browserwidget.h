#ifndef BROWSERWIDGET_H
#define BROWSERWIDGET_H

#include <QWidget>
#include<QList>
#include<QUrl>
#include<QTabWidget>
#include"webview.h"
class BrowserWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit BrowserWidget(QWidget *parent = 0);
    void addTabPage(const QUrl &url);

signals:
    void setProgress(int num);
public slots:
    void newTab(QUrl url);
    void tabCloseRequested(int index);
    void showTabName(const QString & name,QWidget * widget);
    void back();
    void forward();
    void refresh();
    void stop();
    void load(const QUrl & url);

    void loadProgress(int progress);

private:
    WebView * webView;
};

#endif // BROWSERWIDGET_H
