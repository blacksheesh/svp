#include "mainwindow.h"

MyWindow ::MyWindow(QWidget  *parent)
    : QWidget(parent)
{
    showErrorButton= new  QPushButton("Show Error");
    showWarningButton = new QPushButton("Show Warning");
    showInformationButton = new  QPushButton("Show Information");
    m_hLayout = new QHBoxLayout(this);

    m_hLayout->addWidget(showErrorButton);
    m_hLayout->addWidget(showWarningButton);
    m_hLayout->addWidget(showInformationButton);

    connect(showErrorButton, &QPushButton::clicked,this,  &MyWindow::errorButtonClicked);
    connect(showWarningButton, &QPushButton::clicked,this,  &MyWindow::warningButtonClicked);
    connect(showInformationButton, &QPushButton::clicked,this,  &MyWindow::informationButtonClicked);

}

MyWindow::~MyWindow() {}

void MyWindow::errorButtonClicked(){
    QMessageBox::critical(this, "Чернышова", "Ошибка 404");
}

void MyWindow::warningButtonClicked(){
    QMessageBox::warning(this, "Чернышова","Предупреждение! Скоро сессия!");
}

void MyWindow::informationButtonClicked(){
    QMessageBox::information(this, "Чернышова", "Информация: Политех самый лучший");
}
