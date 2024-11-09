#pragma once

#include <QPainter>

#include "round_object.h"

#define SNAKE_APPLE_IMAGE_ALIAS ":/apple.png"

/**
 * @brief Класс яблока, размещаемого на игровом поле
 */
class Apple : public RoundObject
{
public:
    /**
     * @brief Конструктор
     * 
     * @param cell_size Размер клетки игрового поля
     */
    Apple(const QSize &cell_size);
    ~Apple() = default;

    /**
     * @brief Случайное расположение яблока на клеточном игровом поле.
     * 
     * @param x_cell_number Число клеток игрового поля по оси x.
     * @param y_cell_number Число клеток игрового поля по оси y.
     * @param cell_size Размер ячейки в пикселях.
     */
    void locateInRandomCell(
        const int x_cell_number, 
        const int y_cell_number);

    /**
     * @brief Рисует изображение яблока
     */
    void draw(QPainter &painter);

protected:
    /// @brief Изображение яблока
    QImage image_;

    /// @brief Размер ячейки игрового поля
    QSize cell_size_;
};