#include <QDebug>
#include <QApplication>
#include "game.h"

int main(int argc, char* argv[])
{
    QApplication snake_app(argc, argv);

    // Создание экземпляра объекта ui
    Game snake_game;

    // Установка названия окна
    snake_game.setWindowTitle("Snake!");

    // Отобразить окно
    snake_game.show();

    // Выполнение приложения
    return snake_app.exec();
}