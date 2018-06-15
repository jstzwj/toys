#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QWebEngineView>
#include<QWebEnginePage>
#include<QTabWidget>
#include<QUrl>
#include<QGridLayout>
#include<QPushButton>
#include<QLineEdit>
#include<QProgressBar>

#include"webview.h"
#include"browserwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void editingFinished();
    void setProgress(int num);
private:
    Ui::MainWindow *ui;
    BrowserWidget * browser;
    QWidget * centerWidget;
    QGridLayout * gridLayout;
    QGridLayout * pageCrtl;
    QPushButton *forward;
    QPushButton *back;
    QPushButton *refreshAndStop;
    QLineEdit * lineEdit;
    QProgressBar * progressBar;
};

#endif // MAINWINDOW_H
