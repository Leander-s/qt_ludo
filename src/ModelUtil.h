#pragma once
#include <vector>

namespace QtLudo {
class Model {
public:
  Model(std::vector<int> indices, std::vector<float> vertices);

  std::vector<int> indices;
  std::vector<float> vertices;
};

class GameGrid {
public:
  GameGrid(float x, float y, float z, float cellSize, int xLength, int zLength);

  Model *model;
};
} // namespace QtLudo
