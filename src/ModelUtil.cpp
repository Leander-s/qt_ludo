#include "ModelUtil.h"

namespace QtLudo {
Model::Model(std::vector<int> newIndices, std::vector<float> newVertices) {
  indices = newIndices;
  vertices = newVertices;
}

GameGrid::GameGrid(float x, float y, float z, float cellSize, int xLength,
                   int zLength) {
  std::vector<int> indices;
  std::vector<float> vertices;
  for (int i = 0; i < xLength; i++) {
    for (int j = 0; j < zLength; j++) {
      std::vector<float> newVertex = {
          x + cellSize * i, y, -(z + cellSize * j), 1.0f, 1.0f, 1.0f};
      vertices.insert(vertices.end(), newVertex.begin(), newVertex.end());

      if (i < xLength - 1 && j < zLength - 1) {
        int base = i * xLength + j;
        std::vector<int> newIndices = {base,           base + 1,
                                       base + xLength, base + xLength,
                                       base + 1,       base + xLength + 1};
        indices.insert(indices.end(), newIndices.begin(), newIndices.end());
      }
    }
  }

  model = new Model(indices, vertices);
}
} // namespace QtLudo
