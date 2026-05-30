#include "Primitives/Polygon.hpp"
#include "Primitives/Point.hpp"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <optional>
#include <ranges>
#include <vector>

using namespace LF::Primitives;

struct Polygon::Impl {
  using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
  using CGALPoint = Kernel::Point_2;
  using CGALPolygon = CGAL::Polygon_2<Kernel>;
  std::unique_ptr<CGALPolygon> polygon = nullptr;
  std::vector<Point2D> points;
  Impl() = default;
  Impl(std::initializer_list<Point2D> data) : points(data) {}
  Impl(std::size_t reserve) { points.reserve(reserve); }

  bool remove(std::size_t idx) {
    if (frozen())
      return false;
    if (idx >= points.size())
      return false;
    points.erase(points.begin() + idx);
    return true;
  }
  bool add(const Point2D &p) {
    if (frozen())
      return false;
    points.push_back(p);
    return true;
  }

  bool update(std::size_t idx, const Point2D &p) {
    if (frozen())
      return false;
    if (idx >= points.size())
      return false;
    points[idx] = p;
    return true;
  }
  std::size_t size() const { return points.size(); }
  bool frozen() const { return polygon.get(); }
  void freeze() {
    if (frozen())
      return;

    auto cgal_points = points | std::views::transform([](const Point2D &p) {
                         return CGALPoint{p.x, p.y};
                       }) |
                       std::ranges::to<std::vector>();
    polygon =
        std::make_unique<CGALPolygon>(cgal_points.begin(), cgal_points.end());
  }

  void unfreeze() { polygon.reset(); }
  std::optional<double> area() const {
    if (!frozen())
      return std::nullopt;
    return std::abs(polygon->area());
  }
};

Polygon::Polygon() : impl_(std::make_unique<Impl>()) {}
Polygon::~Polygon() = default;
Polygon::Polygon(std::size_t size) : impl_(std::make_unique<Impl>(size)) {}

Polygon::Polygon(std::initializer_list<Point2D> points)
    : impl_(std::make_unique<Impl>(points)) {}

Polygon::Polygon(Polygon &&) noexcept = default;
Polygon &Polygon::operator=(Polygon &&) noexcept = default;

const std::optional<double> Polygon::area() const { return impl_->area(); }

bool Polygon::add(const Point2D &p) { return impl_->add(p); }
bool Polygon::remove(std::size_t idx) { return impl_->remove(idx); }
bool Polygon::update(std::size_t idx, const Point2D &p) {
  return impl_->update(idx, p);
}
void Polygon::freeze() { impl_->freeze(); }
void Polygon::unfreeze() { impl_->unfreeze(); }
