#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(QString::fromWCharArray(L"知乎带逛"));

    centerWidget=new QWidget(this);
    gridLayout=new QGridLayout(this);
    centerWidget->setLayout(gridLayout);
    browser= new BrowserWidget(this);

    pageCrtl=new QGridLayout(this);
    back=new QPushButton("<-",this);
    connect(back,SIGNAL(clicked()),browser,SLOT(back()));
    forward=new QPushButton("->",this);
    connect(forward,SIGNAL(clicked()),browser,SLOT(forward()));
    refreshAndStop=new QPushButton("O",this);
    connect(refreshAndStop,SIGNAL(clicked()),browser,SLOT(refresh()));
    lineEdit=new QLineEdit(this);
    connect(lineEdit,SIGNAL(editingFinished()),this,SLOT(editingFinished()));

    pageCrtl->addWidget(back,0,0);
    pageCrtl->addWidget(refreshAndStop,0,1);
    pageCrtl->addWidget(forward,0,2);
    pageCrtl->addWidget(lineEdit,0,3);

    gridLayout->addLayout(pageCrtl,0,0);
    gridLayout->addWidget(browser,1,0);
    this->setCentralWidget(centerWidget);

    progressBar=new QProgressBar(this);
    progressBar->setMaximumHeight(20);
    statusBar()->addWidget(progressBar);
    connect(browser,SIGNAL(setProgress(int)),this,SLOT(setProgress(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::editingFinished()
{
    /*
    if(lineEdit->text().left(5)=="http:"||lineEdit->text().left(6)=="https:")
    {
        browser->load(QUrl(lineEdit->text()));
    }
    else
    {
        lineEdit->setText("http://"+lineEdit->text());
        browser->load(QUrl(lineEdit->text()));
    }
    */
    browser->load(QUrl::fromUserInput(lineEdit->text()));
    lineEdit->setText(QUrl::fromUserInput(lineEdit->text()).toString());
}

void MainWindow::setProgress(int num)
{
    progressBar->setValue(num);
    if(num==100)
    {
        progressBar->hide();
    }
    else
    {
        progressBar->show();
    }
}
