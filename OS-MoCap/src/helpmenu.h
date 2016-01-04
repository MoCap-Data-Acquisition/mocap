#ifndef HELPMENU_H
#define HELPMENU_H

#include <QWidget>
#include <QWebView>
#include <QUrl>
namespace Ui {
class Helpmenu;
}

class Helpmenu : public QWidget
{
    Q_OBJECT

public:
    explicit Helpmenu(QWidget *parent = 0);
    ~Helpmenu();

private:
    Ui::Helpmenu *ui;
};

#endif // HELPMENU_H
