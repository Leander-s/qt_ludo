#pragma once
#include "ModelUtil.h"
#include "Players.h"
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <stdexcept>

#define NUMBER_OF_PLAYERS 4
#define NUMBER_OF_PIECES_PER_PLAYER 4
#define NUMBER_OF_PIECES (NUMBER_OF_PIECES_PER_PLAYER * NUMBER_OF_PLAYERS)

namespace QtLudo {
// This should be in a config file
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

struct GameState {
  int positions[NUMBER_OF_PIECES];
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

  uint8_t positions[NUMBER_OF_PIECES];

private:
  // QVector2D rotateCoords(QVector2D, LudoColor color, float tileSize);
  GameObject *createBoard(float tileSize);
  GameObject *createFigure(float tileSize, LudoColor color);

  // Offsets by color
  uint8_t redOffset = 0;
  uint8_t greenOffset = redOffset + NUMBER_OF_PIECES_PER_PLAYER;
  uint8_t blueOffset = greenOffset + NUMBER_OF_PIECES_PER_PLAYER;
  uint8_t yellowOffset = blueOffset + NUMBER_OF_PIECES_PER_PLAYER;
};
} // namespace QtLudo
