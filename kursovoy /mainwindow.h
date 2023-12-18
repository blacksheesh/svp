#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMovie>
#include <QGraphicsPixmapItem>

class SignalGenerator : public QWidget {
    Q_OBJECT


public:
    SignalGenerator(QWidget *parent = nullptr);
  //     ~SignalGenerator();

private slots:
    void generateSignal();
    void saveSignal();
    void updateGifFrame(int frameNumber);

private:
    bool signalGenerated;
    QGraphicsPixmapItem *gifItem;
    QMovie *movie;
    QLabel *frequencyLabel;
    QDoubleSpinBox *frequencySpinBox;
    QLabel *amplitudeLabel;
    QDoubleSpinBox *amplitudeSpinBox;
    QLabel *phaseLabel;
    QDoubleSpinBox *phaseSpinBox;
    QPushButton *generateButton;
    QPushButton *saveButton;
    QGraphicsView *graphicsView;
    QGraphicsScene *graphicsScene;
    QGraphicsScene *scene;
};
#endif // MAINWINDOW_H
