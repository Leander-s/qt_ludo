#pragma once
#include "ModelUtil.h"
#include "Players.h"
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <stdexcept>

namespace QtLudo {
const std::array<QVector2D, 66> positionMappings = {
    QVector2D(-6.0f, -6.0f), QVector2D(-3.0f, -6.0f), QVector2D(-6.0f, -3.0f),
    QVector2D(-3.0f, -3.0f), QVector2D(-7.0f, -1.0f), QVector2D(-6.0f, -1.0f),
    QVector2D(-5.0f, -1.0f), QVector2D(-4.0f, -1.0f), QVector2D(-3.0f, -1.0f),
    QVector2D(-2.0f, -1.0f), QVector2D(-1.0f, -1.0f), QVector2D(-1.0f, -2.0f),
    QVector2D(-1.0f, -3.0f), QVector2D(-1.0f, -4.0f), QVector2D(-1.0f, -5.0f),
    QVector2D(-1.0f, -6.0f), QVector2D(-1.0f, -7.0f), QVector2D(0.0f, -7.0f),
    QVector2D(1.0f, -7.0f),  QVector2D(1.0f, -6.0f),  QVector2D(1.0f, -5.0f),
    QVector2D(1.0f, -4.0f),  QVector2D(1.0f, -3.0f),  QVector2D(1.0f, -2.0f),
    QVector2D(1.0f, -1.0f),  QVector2D(2.0f, -1.0f),  QVector2D(3.0f, -1.0f),
    QVector2D(4.0f, -1.0f),  QVector2D(5.0f, -1.0f),  QVector2D(6.0f, -1.0f),
    QVector2D(7.0f, -1.0f),  QVector2D(7.0f, 0.0f),   QVector2D(7.0f, 1.0f),
    QVector2D(6.0f, 1.0f),   QVector2D(5.0f, 1.0f),   QVector2D(4.0f, 1.0f),
    QVector2D(3.0f, 1.0f),   QVector2D(2.0f, 1.0f),   QVector2D(1.0f, 1.0f),
    QVector2D(1.0f, 2.0f),   QVector2D(1.0f, 3.0f),   QVector2D(1.0f, 4.0f),
    QVector2D(1.0f, 5.0f),   QVector2D(1.0f, 6.0f),   QVector2D(1.0f, 7.0f),
    QVector2D(0.0f, 7.0f),   QVector2D(-1.0f, 7.0f),  QVector2D(-1.0f, 6.0f),
    QVector2D(-1.0f, 5.0f),  QVector2D(-1.0f, 4.0f),  QVector2D(-1.0f, 3.0f),
    QVector2D(-1.0f, 2.0f),  QVector2D(-1.0f, 1.0f),  QVector2D(-2.0f, 1.0f),
    QVector2D(-3.0f, 1.0f),  QVector2D(-4.0f, 1.0f),  QVector2D(-5.0f, 1.0f),
    QVector2D(-6.0f, 1.0f),  QVector2D(-7.0f, 1.0f),  QVector2D(-7.0f, 0.0f),
    QVector2D(-6.0f, 0.0f),  QVector2D(-5.0f, 0.0f),  QVector2D(-4.0f, 0.0f),
    QVector2D(-3.0f, 0.0f),  QVector2D(-2.0f, 0.0f),  QVector2D(-1.0f, 0.0f),
};

class GameObject {
public:
  GameObject(const Model &newModel, const char *texturePath);
  GameObject(const Model &newModel, const QVector3D &position,
             const char *texturePath);
  ~GameObject();
  void translate(const QVector3D &translation);
  void rotate(float angle, const QVector3D &axis);

  QMatrix4x4 modelMatrix;
  Model model;
  GLuint VAO, VBO, IBO;
  QString texturePath;
  QOpenGLTexture *texture = nullptr;
  bool ready;
};

class Ludo {
public:
  Ludo();
  std::vector<GameObject *> createObjects();
  void update();

  uint8_t getPosition(LudoColor color, int index);
  QVector2D positionToCoords(LudoColor color, uint8_t position,
                             float tileSize = 1.0f);

  uint8_t positions[16];

private:
  //QVector2D rotateCoords(QVector2D, LudoColor color, float tileSize);
  GameObject *createBoard(float tileSize);
  GameObject *createFigure(float tileSize, LudoColor color);

  // Offsets by color
  uint8_t red = 0;
  uint8_t green = 4;
  uint8_t blue = 8;
  uint8_t yellow = 12;
};
} // namespace QtLudo
