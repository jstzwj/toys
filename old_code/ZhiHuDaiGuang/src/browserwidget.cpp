#include "browserwidget.h"
#include<QDebug>
BrowserWidget::BrowserWidget(QWidget *parent) : QTabWidget(parent)
{
    this->setMovable(true);
    this->setTabsClosable(true);
    this->setTabShape(QTabWidget::Triangular);

    webView=new WebView(this);
    webView->load(QUrl("https://www.zhihu.com/"));
    //webView->show();

    this->addTab(webView,QString::fromWCharArray(L"知乎"));

    connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(tabCloseRequested(int)) );
    connect(webView,SIGNAL(loadProgress(int)),this,SLOT(loadProgress(int)) );
}

void BrowserWidget::addTabPage(const QUrl &url)
{
    WebView *view=new WebView(this);
    view->load(url);
    this->addTab(view,QString::fromWCharArray(L"知乎"));
    this->setCurrentIndex(this->count()-1);
    connect(view,SIGNAL(loadProgress(int)),this,SLOT(loadProgress(int)) );
}

void BrowserWidget::newTab(QUrl url)
{
    addTabPage(url);
}

void BrowserWidget::tabCloseRequested(int index)
{
    if(this->count()==1)
    {
        exit(0);
    }
    this->removeTab(index);
}

void BrowserWidget::showTabName(const QString &name, QWidget *widget)
{
    qDebug()<<name;
    this->setTabText(this->indexOf(widget),name);
}

void BrowserWidget::back()
{
    dynamic_cast<WebView*>(this->currentWidget())->back();
}

void BrowserWidget::forward()
{
    dynamic_cast<WebView*>(this->currentWidget())->forward();
}

void BrowserWidget::refresh()
{
    dynamic_cast<WebView*>(this->currentWidget())->reload();
}

void BrowserWidget::stop()
{
    dynamic_cast<WebView*>(this->currentWidget())->stop();
}

void BrowserWidget::load(const QUrl &url)
{
    dynamic_cast<WebView*>(this->currentWidget())->load(url);
}

void BrowserWidget::loadProgress(int progress)
{
    setProgress(progress);
}


