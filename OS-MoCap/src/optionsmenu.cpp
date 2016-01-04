#include "optionsmenu.h"
#include "ui_optionsmenu.h"
#include <QDebug>
OptionsMenu::OptionsMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsMenu)
{
    ui->setupUi(this);
}

OptionsMenu::~OptionsMenu()
{
    delete ui;
}

//Slots
void OptionsMenu::on_flipVideoBtn_clicked()
{
    //Video Flipped Transformation Code goes here.
    emit(rotate180());
    qDebug() << "Flip Video Slot";
}

void OptionsMenu::on_rotatePosBtn_clicked()
{
    //Video Rotated +90 Transformation Code goes here.
    emit(rotatePos());
    qDebug() << "Rotate Video +90 Slot";
}

void OptionsMenu::on_rotateNegBtn_clicked()
{
    //Video Rotated -90 Transformation Code goes here.
    emit(rotateNeg());
    qDebug() << "Rotate Video -90 Slot";
}

void OptionsMenu::on_mirrorVideoBtn_clicked()
{
    //Mirror Video Transformation Code goes here.
    emit(mirror());
    qDebug() << "Mirror Video Slot";
}

//Signals
//void OptionsMenu::flipVideo(bool flip){}
//void OptionsMenu::rotatePos(bool rotPos){}
//void OptionsMenu::rotateNeg(bool rotNeg){}
//void OptionsMenu::mirrorVideo(bool mirror){}
