#ifndef WEBPAGE_H
#define WEBPAGE_H

#include<QWebEnginePage>
#include<QUrl>
class WebPage : public QWebEnginePAge
{
    Q_OBJECT
public:
    WebPage(QWidget * parent=Q_NULLPTR);
    QUrl hoveredUrl;
};

#endif // WEBPAGE_H
