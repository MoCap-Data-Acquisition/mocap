#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include <QWidget>

namespace Ui {
class OptionsMenu;
}

class OptionsMenu : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsMenu(QWidget *parent = 0);
    ~OptionsMenu();

signals:
    void rotate180();
    void rotatePos();
    void rotateNeg();
    void mirror();

private slots:
    void on_flipVideoBtn_clicked();

    void on_rotatePosBtn_clicked();

    void on_rotateNegBtn_clicked();

    void on_mirrorVideoBtn_clicked();

private:
    Ui::OptionsMenu *ui;
};

#endif // OPTIONSMENU_H
