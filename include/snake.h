#pragma once

#include <QPoint>
#include <QSize>
#include <QRect>
#include <QPainter>
#include <QList>
#include <QImage>

#include "round_object.h"

#define SNAKE_INIT_LENGTH 3

#define SNAKE_BODY_IMAGE_ALIAS ":/body.png"
#define SNAKE_HEAD_IMAGE_ALIAS ":/head.png"

class Snake
{
public:
    Snake(const QSize &cell_size);
    ~Snake() = default;

    /**
     * @brief Располагает змейку на игровом поле. Голова располагатеся в ячейке
     * с координатами cell_x, cell_y. Остальное тело располагается ниже 
     */
    void locate(const int cell_x, const int cell_y);

    /**
     * @brief Возвращает true, если змейка пересекает головой собственное тело.
     */
    bool isCollideItself() const;

    /**
     * @brief Возвращает true, если змейка пересекает другой объект.
     * 
     * @param another Объект, на пересечение с которым проверяется змейка.
     */
    bool isCollideWith(const RoundObject &another) const;

    /**
     * @brief Возвращает true, если координаты головы змейки находятся вне
     * игрового поля.
     */
    bool isOutOfBounds(const QRect &field) const;

    /**
     * @brief Вращает голову змейки на заданный угол.
     * 
     * @param angle Угол поворота головы змейки, рад.
     */
    void rotateHead(const double angle);

    /**
     * @brief Проверяет не съела ли змейка яблоко (если да, нужно удлинниться в
     * следующий игровой цикл)
     */
    bool isEatingApple(const RoundObject &object);

    /**
     * @brief Перемещает змейку на шаг вперед
     */
    void move();

    /**
     * @brief Рисует изображение змейки
     */
    void draw(QPainter &painter) const;

protected:
    /** 
     * @brief Список объектов, из которых состоит тело змейки. Голова змейки
     * хранится в начале списка.
     */ 
    QList<RoundObject> bodyparts_;

    /// @brief Изображение головы змейки
    QImage head_image_;

    /// @brief Изображение тела змейки
    QImage body_image_;

    /// @brief Размер ячейки игрового поля
    QSize cell_size_;

    /// @brief Направление движения змейки
    double direction_;

    /// @brief true, если яблоко было съедено
    bool is_apple_eaten_;
};