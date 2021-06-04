#ifndef UTILTOOL_H
#define UTILTOOL_H

#include "point.h"

namespace Shape2D {

template <typename T>
struct PointPair
{
    typedef Point<T> PointType;

    PointType ptLefttop;
    PointType ptRightBottom;
};

template <typename T>
class Box : public PointPair<T>
{
private:
    bool valid {false};
    typedef PointPair<T> Base;
    typedef typename PointPair<T>::PointType BasePointType;

public:
    Box() = default;
    Box(const BasePointType& p0, const BasePointType& p1)
        : Base::ptLefttop(std::min(p0.x, p1.x), std::min(p0.y, p1.y))
        , Base::ptRightBottom(std::max(p0.x, p1.x), std::max(p0.y, p1.y))
        , valid(true)
    {}

    Box(const Box<T>& box)
        : valid(box.valid)
    {
        this->ptLefttop = box.ptLefttop;
        this->ptRightBottom = box.ptRightBottom;
    }

    void set(const BasePointType& p0, const BasePointType& p1)
    {
        this->ptLefttop = {std::min(p0.x, p1.x), std::min(p0.y, p1.y)};
        this->ptRightBottom = {std::max(p0.x, p1.x), std::max(p0.y, p1.y)};
        valid = true;
    }

    void append(const BasePointType& pt)
    {
        if(valid)
        {
            if(left() > pt.x)
                left() = pt.x;
            else if(right() < pt.x)
                right() = pt.x;

            if(top() > pt.y)
                top() = pt.y;
            if(bottom() < pt.y)
                bottom() = pt.y;
        }
        else
        {
            set(pt, pt);
        }
    }

    operator bool() const {
        return valid;
    }

    T width() const{
        return this->ptRightBottom.x - this->ptLefttop.x;
    }

    T height() const{
        return this->ptRightBottom.y - this->pptLefttop.y;
    }

    T left() const{
        return this->ptLefttop.x;
    }

    T right() const{
        return this->ptRightBottom.x;
    }


    T top() const{
        return this->ptLefttop.y;
    }

    T bottom() const{
        return this->ptRightBottom.y;
    }

    T& left(){
        return this->ptLefttop.x;
    }

    T& right() {
        return this->ptRightBottom.x;
    }


    T& top() {
        return this->ptLefttop.y;
    }

    T& bottom() {
        return this->ptRightBottom.y;
    }

    Box<T> operator | (const Box<T>& box) {
        Box copy = *this;
        copy |= box;
        return copy;
    }

    Box<T>& operator = (const Box<T>& box) {
        this->ptLefttop = box.ptLefttop;
        this->ptRightBottom = box.ptRightBottom;
        this->valid = box.valid;
        return *this;
    }

    Box<T>& operator |= (const Box<T>& box) {

        if(valid && box.valid)
        {
            if(this->left()  > box.left())
                this->left() = box.left();

            if(this->right()  < box.right())
                this->right() = box.right();

            if(this->top()  > box.top())
                this->top() = box.top();

            if(this->bottom()  < box.bottom())
                this->bottom() = box.bottom();
        }
        else
        {
            *this = box;
        }

        return *this;
    }


};

typedef Box<double> Box2D;

struct Tools {
    static Box2D calcBoundingBox(const Path2D & path) {
        Box2D box;

        if(!path.empty())
        {
            for(const Point2D &pt: path)
            {
                box.append(pt);
            }
        }

        return box;
    }
};


}

#endif // UTILTOOL_H
