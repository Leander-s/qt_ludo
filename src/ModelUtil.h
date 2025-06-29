#pragma once
#include <QColor>
#include <vector>

namespace QtLudo {
class Model {
public:
  Model();
  Model(const Model &other);
  Model(const std::vector<int> indices, const std::vector<float> vertices);

  std::vector<int> indices;
  std::vector<float> vertices;
};

class GroundTile {
public:
  GroundTile(float size, const QColor &color);
  Model model;
};
} // namespace QtLudo
