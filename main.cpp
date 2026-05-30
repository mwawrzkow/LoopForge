#include <Primitives/Polygon.hpp>
#include <print>
int main(int argc, char *argv[]) {
  LF::Primitives::Polygon lf({{0, 0}, {0, 1}, {.5, 1}});
  lf.freeze();
  std::println("Area:{}", *lf.area());

      return 0;
}
