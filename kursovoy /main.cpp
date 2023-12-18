#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    SignalGenerator signalGenerator; // Создание экземпляра класса SignalGenerator, представляющего главное окно приложения
    signalGenerator.show(); // Отображение главного окна приложения

    app.setStyle("fusion"); // Установка стиля интерфейса для приложения
    QPalette m_pal; // Создание объекта палитры, который используется для настройки цветового оформления интерфейса
    m_pal.setColor(QPalette::Window, QColor(192, 235, 192));   // светло-зеленый фон
    m_pal.setColor(QPalette::WindowText, QColor(0, 0, 0));      // черный цвет текста
    m_pal.setColor(QPalette::Button, QColor(57, 130, 57));        // темно-зеленая кнопка
    m_pal.setColor(QPalette::ButtonText, QColor(255, 255, 255)); // белый цвет текста на кнопке
    m_pal.setColor(QPalette::Highlight, QColor(50, 205, 50));   // зеленое выделение
    m_pal.setColor(QPalette::HighlightedText, QColor(0, 0, 0));

    app.setPalette(m_pal); // Применение созданной палитры к приложению для установки цветового оформления
    return app.exec();
}
