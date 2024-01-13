// SPDX-License-Identifier: Apache-2.0

#include <scratchcpp/rect.h>
#include <cmath>
#include "rect_p.h"

using namespace libscratchcpp;

/*! Constructs Rect. */
Rect::Rect(double left, double top, double right, double bottom) :
    impl(spimpl::make_impl<RectPrivate>(left, top, right, bottom))
{
}

/*! \copydoc Rect() */
Rect::Rect() :
    impl(spimpl::make_impl<RectPrivate>())
{
}

/*! Returns the x-coordinate of the left edge. */
double Rect::left() const
{
    return impl->left;
}

/*! Sets the x-coordinate of the left edge. */
void Rect::setLeft(double left)
{
    impl->left = left;
}

/*! Returns the y-coordinate of the top edge. */
double Rect::top() const
{
    return impl->top;
}

/*! Sets the y-coordinate of the top edge. */
void Rect::setTop(double top)
{
    impl->top = top;
}

/*! Returns the x-coordinate of the right edge. */
double Rect::right() const
{
    return impl->right;
}

/*! Sets the x-coordinate of the right edge. */
void Rect::setRight(double right)
{
    impl->right = right;
}

/*! Returns the y-coordinate of the bottom edge. */
double Rect::bottom() const
{
    return impl->bottom;
}

/*! Sets the y-coordinate of the bottom edge. */
void Rect::setBottom(double bottom)
{
    impl->bottom = bottom;
}

/*! Returns the width of the rectangle. */
double Rect::width() const
{
    return std::abs(impl->right - impl->left);
}

/*! Returns the height of the rectangle. */
double Rect::height() const
{
    return std::abs(impl->top - impl->bottom);
}

/*! Returns true if the rectangle intersects the given rectangle. */
bool Rect::intersects(const Rect &rect) const
{
    // Get the sorted coordinates for the current rectangle
    double x1 = std::min(impl->left, impl->right);
    double x2 = std::max(impl->left, impl->right);
    double y1 = std::min(impl->top, impl->bottom);
    double y2 = std::max(impl->top, impl->bottom);

    // Get the sorted coordinates for the other rectangle
    double rectX1 = std::min(rect.impl->left, rect.impl->right);
    double rectX2 = std::max(rect.impl->left, rect.impl->right);
    double rectY1 = std::min(rect.impl->top, rect.impl->bottom);
    double rectY2 = std::max(rect.impl->top, rect.impl->bottom);

    // Check if the rectangles intersect
    return !(x2 < rectX1 || rectX2 < x1 || y2 < rectY1 || rectY2 < y1);
}
