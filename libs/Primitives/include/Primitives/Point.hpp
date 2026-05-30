#pragma once

namespace LF::Primitives {
template <typename Scalar = double> struct Point {
  Scalar x, y;
};
using Point2D = Point<double>;
} // namespace LF::Primitives
