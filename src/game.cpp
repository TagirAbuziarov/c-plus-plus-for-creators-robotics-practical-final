#include <chrono>
#include <complex>
#include <math.h>

#include <QApplication>
#include <QDir>
#include <QString>
#include <QImage>
#include <QPainter>
#include <QDebug>

#include "game.h"
#include "apple.h"

const QSize Game::cell_size_{GAME_CELL_SIZE, GAME_CELL_SIZE};

// Наследование от базового класса объектов ui
Game::Game(QWidget * parent) 
    : QWidget(parent), 
    snake_(Game::cell_size_),
    apple_(Game::cell_size_),
    field_(0, 0, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT),
    is_snake_move_requested_(false),
    is_game_over_(false),
    timerId_(0)
{
    // Загрузка изображений змейки и яблока
    this->loadImages();
    
    /* 
    Создает змейку, случайным образом располагает яблоко на игровом поле и 
    запускает игру 
    */
    this->initGame();

    // Фиксация размера окна
    this->setFixedSize(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
    
}

    
void Game::loadImages()
{
    // Все используемые изображения масштабируются в квадратные
    this->game_over_image_.load(SNAKE_GAME_OVER_IMAGE_ALIAS);
    int image_size {std::min(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT)};
    QSize image_qsize {image_size, image_size};
    this->game_over_image_ = this->game_over_image_.scaled(image_qsize);
}

void Game::initGame()
{
    // Сброс флага окончания игры
    this->is_game_over_ = false;

    /*
    Использование текущего времени в качестве seed для генератора случайных 
    чисел 
    */
    std::srand(std::time(nullptr));

    // Расположение змейки
    this->snake_.locate(SNAKE_INIT_HEAD_CELL_X, SNAKE_INIT_HEAD_CELL_Y);

    // Случайное расположение яблока
    this->locateApple();

    // Создание таймера игрового цикла
    if (!this->timerId_)
    {
        this->timerId_ = startTimer(std::chrono::milliseconds(SNAKE_UPDATE_PERIOD_MS));
    }
}

void Game::keyPressEvent(QKeyEvent *event)
{
    // Флаг нажатия кнопки управления
    bool control_key_pressed {false};
    double angle{0};

    // Обработка нажатия кнопок
    switch (event->key())
    {
    // Продолжение игры по кнопке Esc
    case Qt::Key_Escape:
        if (this->is_game_over_)
        {
            this->initGame();
        }
        break;

    // Обработка нажатия кнопок управления змейкой
    case Qt::Key_Up:
        // Флаг запроса перемещения змейки
        this->is_snake_move_requested_ = true;
        control_key_pressed = true;
        break;

    case Qt::Key_Left:
        angle = -0.3;
        control_key_pressed = true;
        break;

    case Qt::Key_Right:
        angle = 0.3;
        control_key_pressed = true;
        break;
    }

    // Запрет движения змейки, если игра окончена
    if (!this->is_game_over_ && control_key_pressed)
    {
        // Перемещение змейки, не дожидаясь таймера
        if (this->timerId_ && control_key_pressed)
        {
            this->killTimer(this->timerId_);
            this->timerId_ = 0;
        }

        // Вращение головы змейки
        snake_.rotateHead(angle);

        // Обновить состояние объекто игры
        this->updateGame();

        // Обновить таймер
        if (!this->timerId_ && !this->is_game_over_)
        {
            this->timerId_ = startTimer(
                std::chrono::milliseconds(SNAKE_UPDATE_PERIOD_MS));
        }
    }
}

void Game::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);

    // Флаг запроса перемещения змейки
    this->is_snake_move_requested_ = true;

    this->updateGame();
}

void Game::locateApple()
{
    do 
    {
        this->apple_.locateInRandomCell(GAME_X_CELLS, GAME_Y_CELLS);
    }
    while(this->snake_.isCollideWith(this->apple_));
}

void Game::updateGame()
{
    // Переместить змейку, если есть запрос от таймера или кнопки "вперед"
    if (this->is_snake_move_requested_)
    {
        this->snake_.move();

        // Сброс флага запроса перемещения змейки
        this->is_snake_move_requested_ = false;
    }

    /*
    Проверка на столкновение змейки с другими объектами и вместимость
    змейки в игровое поле 
    */
    if (this->checkCollision())
    {
        this->onEndGame();
    }

    // Перерисовать игровое поле
    QWidget::repaint();
}


bool Game::checkCollision()
{
    if (this->snake_.isOutOfBounds(this->field_))
    {
        return true;
    }
    
    if (this->snake_.isCollideItself())
    {
        return true;
    }

    if (this->snake_.isEatingApple(this->apple_))
    {
        this->locateApple();
    }
    
    return false;
}


void Game::onEndGame()
{
    this->is_game_over_ = true;
    if (this->timerId_)
    {
        this->killTimer(this->timerId_);
        this->timerId_ = 0;
    }
}

void Game::paintEvent(QPaintEvent * e)
{
    Q_UNUSED(e);

    // Отрисовка фона
    QPainter painter(this);
    painter.fillRect(this->field_, Qt::GlobalColor::black);

    // Отрисовка яблока
    this->apple_.draw(painter);

    // Отрисовка змейки
    this->snake_.draw(painter);

    // Отрисовка надписи "Game over" в случае конца игры
    if (this->is_game_over_)
    {
        int image_size {this->game_over_image_.height()};
        int x_pos {(GAME_WINDOW_WIDTH - image_size)/2};
        int y_pos {(GAME_WINDOW_HEIGHT - image_size)/2};
        painter.drawImage(x_pos, y_pos, this->game_over_image_);
    }

}




