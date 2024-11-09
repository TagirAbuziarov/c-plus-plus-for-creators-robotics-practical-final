#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QImage>
#include <QPoint>
#include <QList>
#include <QRect>
#include <QRegion>

#include "apple.h"
#include "snake.h"

#define SNAKE_APPLE_IMAGE_ALIAS ":/apple.png"
#define SNAKE_BODY_IMAGE_ALIAS ":/body.png"
#define SNAKE_HEAD_IMAGE_ALIAS ":/head.png"
#define SNAKE_GAME_OVER_IMAGE_ALIAS ":/game_over.png"

#define GAME_CELL_SIZE 20
#define GAME_X_CELLS 30
#define GAME_Y_CELLS 30
#define GAME_WINDOW_WIDTH (GAME_X_CELLS*GAME_CELL_SIZE)
#define GAME_WINDOW_HEIGHT (GAME_Y_CELLS*GAME_CELL_SIZE)

#define SNAKE_INIT_LENGTH 3
#define SNAKE_INIT_HEAD_CELL_X 14  // 0-based
#define SNAKE_INIT_HEAD_CELL_Y 14  // 0-based

#define SNAKE_UPDATE_PERIOD_MS 400

class Game : public QWidget
{
public:
    Game(QWidget* parent = 0);

protected:

    /// @brief Загрузка изображений змейки и яблока
    void loadImages();

    /** 
     * @brief Создает змейку, случайным образом располагает яблоко на игровом
     * поле и запускает игру 
     **/
    void initGame();

    /// @brief Обработка нажатий кнопок клавиатуры. Наследовано от QWidget
    void keyPressEvent(QKeyEvent *event) override;

    /// @brief Обработка события таймера. Наследовано от QWidget
    void timerEvent(QTimerEvent *event) override;

    /// @brief Располагает яблоко на игровом поле
    void locateApple();


    /**
     * @brief Обработка игрового цикла: перемещение тела змейки, проверка 
     * и обработка коллизий, вызов перерисовки игрового поля
     **/
    void updateGame();

    /// @brief Проверка коллизий игровых объектов друг с другом
    bool checkCollision();

    /// @brief Останавливает игру
    void onEndGame();

    /// @brief Перерисовка окна. Наследовано от QWidget
    void paintEvent(QPaintEvent *event) override;


    /// @brief Яблоко на игровом поле
    Apple apple_;

    /// @brief Змейка на игровом поле
    Snake snake_;

    /// @brief Игровое поле
    QRect field_;
    
    /// @brief Изображение надписи конца игры
    QImage game_over_image_;


    /** 
     * @brief Флаг конца игры. Если true, выводится надпись "game over", новые
     * игровые циклы не происходят
     **/
    bool is_game_over_;

    /** 
     * @brief Флаг запроса перемещения змейки.
     **/
    bool is_snake_move_requested_;

    /// @brief id таймера времени циклов
    int timerId_;

    /// @brief Размер ячеек игрового поля
    static const QSize cell_size_;
};