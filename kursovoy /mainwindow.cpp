#include "mainwindow.h"
#include <QPainter>
#include <QFileDialog>
#include <QGraphicsLineItem>
#include <QtMath>
#include <QGraphicsPixmapItem>
#include <QMovie>
#include <QMessageBox>

SignalGenerator::SignalGenerator(QWidget *parent) : QWidget(parent) {

    this->setMinimumSize(800, 600); // Установка минимального размера окна
    signalGenerated = false;
    frequencyLabel = new QLabel("Частота:"); // Создание метки и поля ввода для частоты
    frequencySpinBox = new QDoubleSpinBox;
    frequencySpinBox->setRange(0.1, 1000.0);
    frequencySpinBox->setValue(1.0);
    frequencySpinBox->setFixedWidth(80);// Установка фиксированной ширины кнопки

    amplitudeLabel = new QLabel("Амплитуда:"); // Создание метки и поля ввода для амплитуды
    amplitudeSpinBox = new QDoubleSpinBox;
    amplitudeSpinBox->setRange(0.1, 100.0);
    amplitudeSpinBox->setValue(1.0);
    amplitudeSpinBox->setFixedWidth(80);

    phaseLabel = new QLabel("Сдвиг фазы:"); // Создание метки и поля ввода для сдвига фазы
    phaseSpinBox = new QDoubleSpinBox;
    phaseSpinBox->setRange(0.0, 360.0);
    phaseSpinBox->setValue(0.0);
    phaseSpinBox->setFixedWidth(80);

    generateButton = new QPushButton("Генерация сигнала"); // Создание кнопок "Генерация сигнала" и "Сохранить сигнал" и установка соответствующих соединений с функциями
    connect(generateButton, &QPushButton::clicked, this, &SignalGenerator::generateSignal);
    generateButton->setFixedWidth(120);

    saveButton = new QPushButton("Сохранить сигнал");
    connect(saveButton, &QPushButton::clicked, this, &SignalGenerator::saveSignal);
    saveButton->setFixedWidth(120);// Установка фиксированной ширины кнопки

    QVBoxLayout *layout = new QVBoxLayout; // Создание вертикального компоновщика и добавление виджетов в окно
    layout->addWidget(frequencyLabel);
    layout->addWidget(frequencySpinBox);
    layout->addWidget(amplitudeLabel);
    layout->addWidget(amplitudeSpinBox);
    layout->addWidget(phaseLabel);
    layout->addWidget(phaseSpinBox);
    layout->addWidget(generateButton);
    layout->addWidget(saveButton);

    graphicsView = new QGraphicsView; // Создание элементов для вывода графика
    graphicsScene = new QGraphicsScene;
    graphicsView->setScene(graphicsScene);

    graphicsScene->setBackgroundBrush(QBrush(QColor("#f4fcf2"))); // Настройка цветов для элементов интерфейса
    QString spinBoxStyle = "QDoubleSpinBox { background-color: #f4fcf2 }";
    frequencySpinBox->setStyleSheet(spinBoxStyle);
    amplitudeSpinBox->setStyleSheet(spinBoxStyle);
    phaseSpinBox->setStyleSheet(spinBoxStyle);

    layout->addWidget(graphicsView);

    gifItem = new QGraphicsPixmapItem;// Создание элемента графической сцены для гифки
    graphicsScene->addItem(gifItem);

    movie = new QMovie(":/images/1.gif");// Загрузка анимированный GIF
    gifItem->setPixmap(movie->currentPixmap());

    movie->start();// Начало анимации и установка таймера для обновления кадров
    connect(movie, &QMovie::frameChanged, this, &SignalGenerator::updateGifFrame);

    setLayout(layout);
    setWindowTitle("Signal Generator");
}

void SignalGenerator::updateGifFrame(int frameNumber) {
    gifItem->setPixmap(movie->currentPixmap());
}

void SignalGenerator::generateSignal() {


    graphicsScene->setBackgroundBrush(QBrush(QColor("#f4fcf2"))); // Очистка сцены и установка фона
    graphicsScene->clear();

    const double frequency = frequencySpinBox->value();
    const double amplitude = amplitudeSpinBox->value();
    const double phaseShift = phaseSpinBox->value();

    if (frequency >= 100.0 || amplitude >= 100.0 || phaseShift >= 100.0) {// Отображение сообщения об ошибке
        QMessageBox::critical(this, "Ошибка", "Одно из значений больше 100. Пожалуйста, введите значения до 100.");
        return;
    }

    QList<QGraphicsItem*> items = graphicsScene->items(); // Удаление предыдущих линий перед созданием новых
    for (QGraphicsItem* item : items) {
        if (item->type() == QGraphicsLineItem::Type || item->type() == QGraphicsTextItem::Type) {
            graphicsScene->removeItem(item);
            delete item;
        }
    }



    QPen xAxisPen(QColor(57, 130, 57)); // Ось X
    xAxisPen.setWidth(4);
    QGraphicsLineItem *xAxis = new QGraphicsLineItem(0, 0, graphicsView->width(), 0);
    xAxis->setPen(xAxisPen);
    graphicsScene->addItem(xAxis);

    // Ось Y
           QPen yAxisPen(QColor(57, 130, 57)); // фиолетовый цвет
               yAxisPen.setWidth(4);
               QGraphicsLineItem *yAxis = new QGraphicsLineItem(0, -graphicsView->height() * 0.5,
                                                                0, graphicsView->height() * 0.5);
               yAxis->setPen(yAxisPen);
               graphicsScene->addItem(yAxis);

    QPen graphPen(QColor(187, 0, 255)); // Создание пера для рисования графика
    graphPen.setWidth(6);

    const int numPoints = 1000; //Создание и добавление графика на графическую сцену

    for (int i = 0; i < numPoints - 1; ++i) { //numPoints представляет собой количество точек на графике
        double t1 = i / 1000.0; //t1 и t2 представляют временные значения для текущей и следующей точек
        double t2 = (i + 1) / 1000.0;
        double value1 = amplitudeSpinBox->value() * qSin(2 * M_PI * frequencySpinBox->value() * t1 + phaseSpinBox->value());
        double value2 = amplitudeSpinBox->value() * qSin(2 * M_PI * frequencySpinBox->value() * t2 + phaseSpinBox->value()); //начения value1 и value2 представляют значения сигнала в моменты времени t1 и t2 вычисляются, используя синусоидальную функцию с учетом частоты, амплитуды и сдвига фазы.

        QGraphicsLineItem *line = new QGraphicsLineItem(t1 * graphicsView->width(), -value1 * graphicsView->height() * 0.1, t2 * graphicsView->width(), -value2 * graphicsView->height() * 0.1);

        line->setPen(graphPen);
        graphicsScene->addItem(line); //Создается линейный сегмент между текущей и следующей точкой, устанавливается цвет пера (graphPen)


        signalGenerated = true;

        if (std::fmod(t1, 0.25) == 0) {
            QGraphicsTextItem *coordLabel = new QGraphicsTextItem(QString::number(t1, 'f', 2));
            coordLabel->setPos(t1 * graphicsView->width(), 10);
            graphicsScene->addItem(coordLabel);
        }
 //       if (std::fmod(t1, 0.25) == 0) {
 //           int integerValue = static_cast<int>(value1);
  //          QGraphicsTextItem *coordLabel = new QGraphicsTextItem(QString::number(integerValue));
  //          coordLabel->setPos(0, -value1 * graphicsView->height() * 0.1);
   //         graphicsScene->addItem(coordLabel);
   //     }
        }

}

void SignalGenerator::saveSignal() {
    if (!signalGenerated) { // Проверка, был ли сгенерирован сигнал
           QMessageBox::critical(this, "Ошибка", "Сначала сгенерируйте сигнал!");
           return;
    }

    const QString fileName = QFileDialog::getSaveFileName(this, "Save Signal Image", "", "Images (*.png *.jpg *.bmp)");

    if (!fileName.isEmpty()) {
        QPixmap pixmap(graphicsView->width(), graphicsView->height()); // Создаем изображение
        pixmap.fill(Qt::white); // Заполняем белым фоном
        QPainter painter(&pixmap);// Создаем QPainter и рисуем на нем сцену
        graphicsScene->render(&painter);

        if (pixmap.save(fileName)) {// Сохраняем изображение
            QMessageBox::information(this, "Отлично!", "Изображение сохранено!");
        } else {
            QMessageBox::critical(this, "Ошибка", "Не удалось сохранить изображение!");
        }
    }
}
