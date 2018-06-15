#include "webview.h"
#include<QDebug>
WebView::WebView(QWidget *parent):
        QWebEngineView(parent),parent(parent)
{
    connect(this,SIGNAL(newTab(QUrl)),parent,SLOT(newTab(QUrl)));
    connect(this->page(),SIGNAL(linkHovered(const QString &)),this,SLOT(linkHovered(const QString &)));
    connect(this->page(),SIGNAL(loadFinished(bool)),this,SLOT(loadFinished(bool)));
    connect(this,SIGNAL(showTabName(const QString &,QWidget *)),parent,SLOT(showTabName(const QString &,QWidget *)));
}

void WebView::linkHovered(const QString &url)
{
    hoveredUrl=url;
}

void WebView::loadFinished(bool ok)
{
    qDebug()<<ok;
    if(ok)
    {
        if(this->title().length()>10)
        {
            showTabName(this->title().left(7)+"...",this);
        }
        else
        {
            showTabName(this->title(),this);
        }
    }

}

QWebEngineView *WebView::createWindow(QWebEnginePage::WebWindowType type)
{

    if(type==QWebEnginePage::WebBrowserWindow)
    {

    }
    else if(type==QWebEnginePage::WebBrowserTab)
    {
        QWebEngineView * newView=new QWebEngineView(parent);
        newTab(hoveredUrl);
        return newView;
    }
    else if(type==QWebEnginePage::WebDialog)
    {
        WebDialog * webDialog;
        webDialog=new WebDialog(parent,this->page()->url());
        webDialog->show();
        return webDialog->webDialog;
    }
    else if(type==QWebEnginePage::WebBrowserBackgroundTab)
    {

    }
}

