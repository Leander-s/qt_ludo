#pragma once
#include <iostream>
#include <QColor>
#include <vector>

namespace QtLudo {
class Model {
public:
  Model();
  Model(const Model &other);
  Model(const std::vector<uint32_t> indices, const std::vector<float> vertices);

  std::vector<uint32_t> indices;
  std::vector<float> vertices;
};

class GroundTile {
public:
  GroundTile(float size, const QColor &color);
  Model model;
};
} // namespace QtLudo
