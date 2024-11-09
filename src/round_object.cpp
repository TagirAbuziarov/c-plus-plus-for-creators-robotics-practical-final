#include "round_object.h"

RoundObject::RoundObject()
{
}

RoundObject::RoundObject(const QPoint &coordinates, const QSize &size)
{
    this->locate(coordinates, size);
}

void RoundObject::locate(const QPoint &coordinates, const QSize &size)
{
    this->coordinates_ = coordinates;
    QRect rect(this->coordinates_, size);
    this->collision_ = QRegion(rect, QRegion::Ellipse);
}

const QPoint &RoundObject::getCoordinates() const
{
    return this->coordinates_;
}

const QRegion &RoundObject::getCollision() const
{
    return this->collision_;
}
