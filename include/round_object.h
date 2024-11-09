#pragma once

#include <memory>

#include <QImage>
#include <QPoint>
#include <QSize>
#include <QRegion>

/**
 * @brief Класс круглого объекта, обладающего координатами и областью коллизии
 */
class RoundObject
{
public:

    RoundObject();

    RoundObject(const QPoint &coordinates, const QSize &size);

    /**
     * @brief Распологает круглый объект размера size по координатам 
     * coordinates
     */
    void locate(const QPoint &coordinates, const QSize &size);

    /**
     * @brief Возвращает ссылку на координаты круглого объекта
     */
    const QPoint &getCoordinates() const;

    /**
     * @brief Возвращает true, если объект пересекается с другим объектом
     */
    const QRegion &getCollision() const;

protected:
    /// @brief Координаты объекта, левый верхний угол, пиксели
    QPoint coordinates_;

    /// @brief Форма объекта для проверки на коллизии
    QRegion collision_;
};