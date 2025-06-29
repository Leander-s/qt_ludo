#include "ModelUtil.h"

namespace QtLudo {
Model::Model(const Model& other) {
    indices = other.indices;
    vertices = other.vertices;
}

Model::Model() {}

Model::Model(const std::vector<int> newIndices, const std::vector<float> newVertices) {
  indices = newIndices;
  vertices = newVertices;
}

<<<<<<< HEAD
GroundTile::GroundTile(float size, const QColor &color){
    model.vertices = {
        -size, 0.0f, -size, color.redF(), color.greenF(), color.blueF(), color.alphaF(),
        -size, 0.0f, size, color.redF(), color.greenF(), color.blueF(), color.alphaF(),
        size, 0.0f, -size, color.redF(), color.greenF(), color.blueF(), color.alphaF(),
        size, 0.0f, size, color.redF(), color.greenF(), color.blueF(), color.alphaF(),
    };
    model.indices = {
        0, 1, 2, 2, 1, 3
    };
=======
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
>>>>>>> refs/remotes/origin/main
}
} // namespace QtLudo
