#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;// Интерфейс главного окна
};

#include <QWidget>

class CustomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomWidget(QWidget *parent = nullptr);// Конструктор виджета

protected:
    void paintEvent(QPaintEvent *event);// Событие отрисовки виджета
    void mousePressEvent(QMouseEvent *event);// Событие нажатия кнопки мыши
    void mouseMoveEvent(QMouseEvent *event);// Событие перемещения мыши
    void mouseReleaseEvent(QMouseEvent *event);// Событие отпускания кнопки мыши

private:
    QRect squareRect;// Прямоугольник для отрисовки
    QPoint dragStartPosition;// Начальная позиция для определения смещения при перетаскивании
    bool isDragging;// Флаг для определения состояния перетаскивания
};


#endif // MAINWINDOW_H
