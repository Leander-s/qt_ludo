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

GroundTile::GroundTile(float size, const QColor &color){
    model.vertices = {
        -size, 0.0f, -size, color.redF(), color.greenF(), color.blueF(),
        -size, 0.0f, size, color.redF(), color.greenF(), color.blueF(), 
        size, 0.0f, -size, color.redF(), color.greenF(), color.blueF(),
        size, 0.0f, size, color.redF(), color.greenF(), color.blueF(),
    };
    model.indices = {
        0, 1, 2, 2, 1, 3
    };
}
} // namespace QtLudo
