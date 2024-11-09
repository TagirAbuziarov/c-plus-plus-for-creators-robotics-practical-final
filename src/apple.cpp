#include "apple.h"

#include <math.h>
#include <stdexcept>


Apple::Apple(const QSize &cell_size) : RoundObject(), cell_size_(cell_size)
{
    // Загрузка изображения яблока
    this->image_.load(SNAKE_APPLE_IMAGE_ALIAS);

    // Масштабирование изображения яблока
    this->image_ = this->image_.scaled(this->cell_size_);
}

void Apple::locateInRandomCell(
        const int x_cell_number, 
        const int y_cell_number)
{
    if (x_cell_number <= 0)
    {
        throw std::invalid_argument(
            "Apple::locateInRandomCell: x_cell_number must be positive value");
    }

    if (y_cell_number <= 0)
    {
        throw std::invalid_argument(
            "Apple::locateInRandomCell: y_cell_number must be positive value");
    }

    int apple_x_cell =
        std::rand() / ((RAND_MAX + 1u) / (x_cell_number));
    int apple_y_cell =
        std::rand() / ((RAND_MAX + 1u) / (y_cell_number));

    QPoint apple_coordinates(
        apple_x_cell * this->cell_size_.width(), 
        apple_y_cell * this->cell_size_.height());

    this->locate(apple_coordinates, this->cell_size_);
}

void Apple::draw(QPainter &painter)
{
    painter.drawImage(this->coordinates_, this->image_);
}
