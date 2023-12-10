#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Создайте экземпляр CustomWidget и установите его как основной виджет главного окна
    CustomWidget *customWidget = new CustomWidget(this);
    setCentralWidget(customWidget);
}

MainWindow::~MainWindow(){}// Деструктор MainWindow

#include <QPainter>
#include <QMouseEvent>

CustomWidget::CustomWidget(QWidget *parent) : QWidget(parent), isDragging(false)
{
    setFixedSize(500, 500);// Устанавливаем фиксированный размер виджета
    squareRect = QRect(50, 50, 100, 100);// Инициализируем прямоугольник с начальными координатами и размерами
}

void CustomWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setBrush(QColor(16, 135, 28));// Устанавливаем кисть для заливки цветом (изумрудный цвет)
    painter.drawRect(squareRect);// Рисуем прямоугольник на виджете
}

void CustomWidget::mousePressEvent(QMouseEvent *event)
{
    if (squareRect.contains(event->pos()))
    {
        isDragging = true;
        dragStartPosition = event->pos() - squareRect.topLeft();// Запоминаем начальное положение мыши при начале перетаскивания
    }
    else
    {
        isDragging = false;// Если мышь не находится над прямоугольником, отключаем режим перетаскивания
    }
}

void CustomWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging)
    {
        squareRect.moveTo(event->pos() - dragStartPosition);// Перемещаем прямоугольник в соответствии с перемещением мыши
        update(); // Обновляем виджет для отображения изменений
    }
}

void CustomWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    isDragging = false;// При отпускании кнопки мыши завершаем перетаскивание
}
