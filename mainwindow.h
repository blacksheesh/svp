#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>

class MyWindow : public QWidget
{
    Q_OBJECT

public:
    MyWindow(QWidget *parent=nullptr);
    ~MyWindow();

private:
    QPushButton *showErrorButton;
    QPushButton *showWarningButton;
    QPushButton *showInformationButton;
    QHBoxLayout *m_hLayout;

private slots:
    void errorButtonClicked();
    void warningButtonClicked();
    void informationButtonClicked();

};

#endif // WIDGET_H
