#include "webdialog.h"

WebDialog::WebDialog(QWidget *parent, const QUrl &url):
    QMainWindow(parent)
{
    this->setWindowFlags(Qt::Dialog|Qt::WindowMinMaxButtonsHint|Qt::WindowCloseButtonHint);
    this->resize(300,300);

    webDialog=new QWebEngineView(this);
    webDialog->load(url);

    QWidget* widget = new QWidget(this);
    gridlayout=new QGridLayout(this);
    gridlayout->addWidget(webDialog);
    widget->setLayout(gridlayout);
    this->setCentralWidget(widget);

    connect(webDialog->page(),SIGNAL(windowCloseRequested()),this,SLOT(readyClose()));
}

void WebDialog::readyClose()
{
    this->hide();
    this->close();
}
