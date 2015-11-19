#include "helpmenu.h"
#include "ui_helpmenu.h"
#include <QVBoxLayout>
#include <QDebug>
Helpmenu::Helpmenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Helpmenu)
{
    ui->setupUi(this);
    //ui->webView->load(QUrl("/html/help.html"));
    QWebView *webView = new QWebView;
    QVBoxLayout *layout = new QVBoxLayout;
    this->setLayout(layout);
    layout->addWidget(webView);
   // Helpmenu::setCentralWidget(layout);
    webView->load(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/html/help.html"));
    qDebug() << QApplication::applicationDirPath();

}

Helpmenu::~Helpmenu()
{
    delete ui;
}
