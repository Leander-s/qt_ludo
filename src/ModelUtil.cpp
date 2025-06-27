#include "ModelUtil.h"

namespace QtLudo {
Model::Model(std::vector<int> newIndices, std::vector<float> newVertices) {
  indices = newIndices;
  vertices = newVertices;
}

GameGrid::GameGrid(float x, float y, float z, float cellSize, int xLength,
                   int zLength) {
  std::vector<int> indices = {
      0, 1, 2, 2, 3, 0
  };
  std::vector<float> vertices{
      -xLength * cellSize, y, -zLength * cellSize, 1.0f, 1.0f, 1.0f,
       xLength * cellSize, y, -zLength * cellSize, 1.0f, 1.0f, 1.0f,
       xLength * cellSize, y,  zLength * cellSize, 1.0f, 1.0f, 1.0f,
      -xLength * cellSize, y,  zLength * cellSize, 1.0f, 1.0f, 1.0f,
  };
  /*
  for (int i = 0; i < xLength; i++) {
    for (int j = 0; j < zLength; j++) {
      std::vector<float> newVertex = {
          x + cellSize * i, y, -z + cellSize * j, 1.0f, 1.0f, 1.0f};
      vertices.insert(vertices.end(), newVertex.begin(), newVertex.end());

      float base = j * xLength + i;
      std::vector<float> newIndices = {base,           base + 1,
                                       base + xLength, base + xLength,
                                       base + 1,       base + xLength + 1};
      indices.insert(indices.end(), newIndices.begin(), newIndices.end());
    }
  }
  */

  model = new Model(indices, vertices);
}
} // namespace QtLudo
