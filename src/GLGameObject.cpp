#include "GLGameObject.h"

namespace QtLudo {
GameObject::GameObject(const Model &newModel, const char *texturePath)
    : model(newModel), texturePath(texturePath) {
  modelMatrix = QMatrix4x4();
  position = QVector3D(0.0f, 0.0f, 0.0f);
  ready = false;
}

GameObject::GameObject(const Model &newModel, const QVector3D &newPosition,
                       const char *texturePath)
    : texturePath(texturePath), model(newModel) {
  modelMatrix = QMatrix4x4();
  position = newPosition;
  modelMatrix.translate(position);
  ready = false;
}

GameObject::~GameObject() { delete texture; }

void GameObject::setPosition(const QVector3D &newPosition) {
    position = newPosition;
    QMatrix4x4 newModelMat = QMatrix4x4();
    newModelMat.translate(position);
    modelMatrix = newModelMat;
}

void GameObject::translate(const QVector3D &translation) {
  position += translation;
  modelMatrix.translate(translation);
}

void GameObject::rotate(float angle, const QVector3D &axis) {
  modelMatrix.rotate(angle, axis);
}
} // namespace QtLudo
