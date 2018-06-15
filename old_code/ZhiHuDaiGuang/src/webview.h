#ifndef WEBVIEW_H
#define WEBVIEW_H

#include<QWidget>
#include<QDialog>
#include<QUrl>
#include <QWebEngineView>
#include"webdialog.h"
class WebView:public QWebEngineView
{
    Q_OBJECT
public:
    WebView(QWidget * parent=Q_NULLPTR);
    virtual ~WebView(){}
signals:
    void newTab(QUrl url);
    void showTabName(const QString & name,QWidget * widget);
public slots:
    void linkHovered(const QString &url);
    void loadFinished(bool ok);
protected:
    virtual QWebEngineView *createWindow(QWebEnginePage::WebWindowType type);
    QWidget *parent;
    QUrl hoveredUrl;
};

#endif // WEBVIEW_H
