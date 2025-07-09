#pragma once
#include "ModelUtil.h"
#include <QMatrix4x4>
#include <QOpenGLTexture>

namespace QtLudo {
class GameObject {
public:
  GameObject(const Model &newModel, const char *texturePath);
  GameObject(const Model &newModel, const QVector3D &position,
             const char *texturePath);
  ~GameObject();
  void setPosition(const QVector3D &newPosition);
  void translate(const QVector3D &translation);
  void rotate(float angle, const QVector3D &axis);

  QMatrix4x4 modelMatrix;
  Model model;
  QVector3D position;
  GLuint VAO, VBO, IBO;
  QString texturePath;
  QOpenGLTexture *texture = nullptr;
  bool ready;
};

} // namespace QtLudo
