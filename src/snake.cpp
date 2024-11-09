#include <complex>

#include <math.h>

#include "snake.h"

Snake::Snake(const QSize &cell_size) 
    : cell_size_(cell_size),
      is_apple_eaten_(false),
      direction_(-M_PI_2)
{
    // Загрузка изображений змейки
    this->head_image_.load(SNAKE_HEAD_IMAGE_ALIAS);
    this->body_image_.load(SNAKE_BODY_IMAGE_ALIAS);

    // Масштабирование изображений змейки
    this->head_image_ = this->head_image_.scaled(this->cell_size_);
    this->body_image_ = this->body_image_.scaled(this->cell_size_);
}

void Snake::locate(const int cell_x, const int cell_y)
{
    this->direction_ = -M_PI_2;
    this->bodyparts_.clear();

    for (int i=0; i<SNAKE_INIT_LENGTH; i++)
    {
        QPoint bodypart_coordinates_(
            cell_x * this->cell_size_.width(), 
            (cell_y + i) * this->cell_size_.height());

        this->bodyparts_.append(RoundObject(
            bodypart_coordinates_, this->cell_size_));
    }
}

bool Snake::isCollideItself() const
{
    const QRegion &head = this->bodyparts_.at(0).getCollision();

    for (int i=2; i < this->bodyparts_.size(); i++)
    {
        if (head.intersects(this->bodyparts_.at(i).getCollision()))
        {
            return true;
        }
    }
    return false;
}

bool Snake::isCollideWith(const RoundObject &another) const
{
    const QRegion &head = this->bodyparts_.at(0).getCollision();

    for (auto bodypart: this->bodyparts_)
    {
        if (head.intersects(another.getCollision()))
        {
            return true;
        }
    }
    return false;
}

bool Snake::isOutOfBounds(const QRect &field) const
{
    QRegion region = this->bodyparts_.at(0).getCollision().subtracted(field);
    return !region.isEmpty();
}

void Snake::rotateHead(const double angle)
{
    // Базовое перемещение головы змейки - на величину GAME_CELL_SIZE
    std::complex<double> unit_vector_x(this->cell_size_.width(), 0.);

    // Новое направление движения змейки
    double new_direction {this->direction_ + angle};

    /* 
    Вращение базового перемещения головы змейки на угол direction_ [рад]
    с использованием библиотеки комплексных чисел
    */
    std::complex<double> delta{
        unit_vector_x * std::polar(1., new_direction)};

    // Приведение перемещения к типу QPoint с округлением
    QPoint coordinate_delta(
        static_cast<int>(round(delta.real())), 
        static_cast<int>(round(delta.imag()))
    );

    // Вычисление новых абсолютных координат головы змейки
    QPoint new_head_coordinates = 
        this->bodyparts_.at(1).getCoordinates() + coordinate_delta;

    // Новая голова змейки
    RoundObject new_snake_head(new_head_coordinates, this->cell_size_);

    // Проверка на коллизии
    if (new_snake_head.getCollision().intersects(
        this->bodyparts_.at(2).getCollision()))
    {
        /*
        Слишком крутой поворот головы недопустим: змейка врезается сама в себя
        */
        return;
    }

    // Замена головы змейки
    this->bodyparts_.pop_front();
    this->bodyparts_.push_front(new_snake_head);

    // Сохранение направления движения змейки
    this->direction_ = new_direction;
}

bool Snake::isEatingApple(const RoundObject &object)
{
    if (this->bodyparts_.at(0).getCollision().intersects(
            object.getCollision()))
    {
        this->is_apple_eaten_ = true;
        return true;
    }
    return false;
}

void Snake::move()
{
    // Базовое перемещение головы змейки - на величину GAME_CELL_SIZE
    std::complex<double> unit_vector_x(this->cell_size_.width(), 0.);

    /* 
    Вращение базового перемещения головы змейки на угол direction_ [рад]
    с использованием библиотеки комплексных чисел
    */
    std::complex<double> delta{
        unit_vector_x * std::polar(1., this->direction_)};

    // Приведение перемещения к типу QPoint с округлением
    QPoint coordinate_delta(
        static_cast<int>(round(delta.real())), 
        static_cast<int>(round(delta.imag()))
    );

    // Вычисление новых абсолютных координат головы змейки
    QPoint new_head_coordinates = 
        this->bodyparts_.at(0).getCoordinates() + coordinate_delta;

    // Новая голова змейки
    RoundObject new_snake_head(new_head_coordinates, this->cell_size_);

    // Добавление "новой головы" в начало списка
    this->bodyparts_.push_front(new_snake_head);

    // Если яблоко съедено, тело растет на одну ячейку
    if (this->is_apple_eaten_)
    {
        this->is_apple_eaten_ = false;
    }
    else
    {
        this->bodyparts_.pop_back();
    }

}

void Snake::draw(QPainter &painter) const
{
    // Отрисовка тела змейки
    for(int i{1}; i < this->bodyparts_.size(); i++)
    {
        painter.drawImage(
            this->bodyparts_.at(i).getCoordinates(), 
            this->body_image_);
    }

    // Отрисовка головы змейки
    painter.drawImage(bodyparts_.first().getCoordinates(), this->head_image_);
}
