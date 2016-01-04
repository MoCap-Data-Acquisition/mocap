#include "help.h"
#include "ui_help.h"
#include <QVBoxLayout>

Help::Help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(ui->textBrowser);
    this->setLayout(layout);
}

Help::~Help()
{
    delete ui;
}
