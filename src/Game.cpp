#include "Game.h"
#include "Players.h"

namespace QtLudo {
GameObject::GameObject(const Model &newModel, const char *texturePath)
    : model(newModel), texturePath(texturePath) {
  modelMatrix = QMatrix4x4();
  ready = false;
}

GameObject::GameObject(const Model &newModel, const QVector3D &position,
                       const char *texturePath)
    : texturePath(texturePath), model(newModel) {
  modelMatrix = QMatrix4x4();
  modelMatrix.translate(position);
  ready = false;
}

GameObject::~GameObject() { delete texture; }

void GameObject::translate(const QVector3D &translation) {
  modelMatrix.translate(translation);
}

void GameObject::rotate(float angle, const QVector3D &axis) {
  modelMatrix.rotate(angle, axis);
}

Ludo::Ludo() {
  for (int i; i < NUMBER_OF_PIECES; i++) {
    positions[i] = i % NUMBER_OF_PIECES_PER_PLAYER;
  }
}

std::vector<GameObject *> Ludo::createObjects() {
  std::vector<GameObject *> objects(NUMBER_OF_PIECES, nullptr);
  const float defaultTileSize = 1.0f;
  GameObject *board = createBoard(defaultTileSize);
  for (int startPosition = 0; startPosition < NUMBER_OF_PIECES_PER_PLAYER;
       startPosition++) {
    GameObject *redFigure = createFigure(defaultTileSize, LudoColor::red);
    GameObject *blueFigure = createFigure(defaultTileSize, LudoColor::blue);
    GameObject *greenFigure = createFigure(defaultTileSize, LudoColor::green);
    GameObject *yellowFigure = createFigure(defaultTileSize, LudoColor::yellow);

    QVector2D redPosition = positionToCoords(LudoColor::red, startPosition);
    QVector2D bluePosition = positionToCoords(LudoColor::blue, startPosition);
    QVector2D greenPosition = positionToCoords(LudoColor::green, startPosition);
    QVector2D yellowPosition =
        positionToCoords(LudoColor::yellow, startPosition);

    // All of the figures start at the calculated start position and y = 0
    redFigure->translate(QVector3D(redPosition.x(), 0.0f, redPosition.y()));
    blueFigure->translate(QVector3D(bluePosition.x(), 0.0f, bluePosition.y()));
    greenFigure->translate(
        QVector3D(greenPosition.x(), 0.0f, greenPosition.y()));
    yellowFigure->translate(
        QVector3D(yellowPosition.x(), 0.0f, yellowPosition.y()));

    objects[startPosition] = redFigure;
    objects[startPosition + greenOffset] = greenFigure;
    objects[startPosition + blueOffset] = blueFigure;
    objects[startPosition + yellowOffset] = yellowFigure;
  }

  objects.push_back(board);
  return objects;
}

QVector2D Ludo::positionToCoords(LudoColor color, uint8_t position,
                                 float tileSize) {
  QVector2D red_coords = positionMappings[position];
  QVector2D coords;
  switch (color) {
  case LudoColor::red:
    coords = red_coords;
    break;
  case LudoColor::blue:
    coords = QVector2D(-red_coords.y(), red_coords.x());
    break;
  case LudoColor::yellow:
    coords = QVector2D(-red_coords.x(), -red_coords.y());
    break;
  case LudoColor::green:
    coords = QVector2D(red_coords.y(), -red_coords.x());
    break;
  default:
    throw std::invalid_argument(
        "Color should be red, green, blue or yellow from enum LudoColor");
  };
  return coords;
}

uint8_t Ludo::getPosition(LudoColor color, int index) {
  if (index > NUMBER_OF_PIECES_PER_PLAYER - 1) {
    throw std::invalid_argument("Piece index out of range");
  }
  switch (color) {
  case LudoColor::red:
    return positions[index];
  case LudoColor::green:
    return positions[index + greenOffset];
  case LudoColor::blue:
    return positions[index + blueOffset];
  case LudoColor::yellow:
    return positions[index + yellowOffset];
  }
  throw std::invalid_argument(
      "Color should be red, green, blue or yellow from enum LudoColor");
}

GameObject *Ludo::createBoard(float tileSize) {
  std::vector<uint32_t> indices = {0, 2, 1, 2, 3, 1};
  std::vector<float> vertices = {
      -7.5f * tileSize, 0.0f, -7.5f * tileSize, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      7.5f * tileSize,  0.0f, -7.5f * tileSize, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      -7.5f * tileSize, 0.0f, 7.5f * tileSize,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      7.5f * tileSize,  0.0f, 7.5f * tileSize,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f};
  Model boardModel = Model(indices, vertices);
  QVector3D position = QVector3D(0.0f, 0.0f, 0.0f);
  GameObject *board =
      new GameObject(boardModel, position, "../assets/LudoBoard.png");
  return board;
}

GameObject *Ludo::createFigure(float tileSize, LudoColor color) {
  float r = 0.0f, g = 0.0f, b = 0.0f;
  switch (color) {
  case LudoColor::red:
    r = 1.0f;
    g = 0.0f;
    b = 0.0f;
    break;
  case LudoColor::blue:
    r = 0.0f;
    g = 0.0f;
    b = 1.0f;
    break;
  case LudoColor::green:
    r = 0.0f;
    g = 128.0f / 255.0f;
    b = 0.0f;
    break;
  case LudoColor::yellow:
    r = 0.7f;
    g = 0.7f;
    b = 0.0f;
    break;
  }
  std::vector<float> vertices = {
      -tileSize / 2 * 2 / 3,
      0.0f,
      -tileSize / 2 * 2 / 3,
      r,
      g,
      b,
      0.0f,
      0.0f,
      tileSize / 2 * 2 / 3,
      0.0f,
      -tileSize / 2 * 2 / 3,
      r,
      g,
      b,
      1.0f,
      0.0f,
      tileSize / 2 * 2 / 3,
      0.0f,
      tileSize / 2 * 2 / 3,
      r,
      g,
      b,
      0.0f,
      0.0f,
      -tileSize / 2 * 2 / 3,
      0.0f,
      tileSize / 2 * 2 / 3,
      r,
      g,
      b,
      1.0f,
      0.0f,

      -tileSize / 2 * 2 / 3,
      tileSize / 2,
      -tileSize / 2 * 2 / 3,
      r,
      g,
      b,
      0.0f,
      1.0f,
      tileSize / 2 * 2 / 3,
      tileSize / 2,
      -tileSize / 2 * 2 / 3,
      r,
      g,
      b,
      1.0f,
      1.0f,
      tileSize / 2 * 2 / 3,
      tileSize / 2,
      tileSize / 2 * 2 / 3,
      r,
      g,
      b,
      0.0f,
      1.0f,
      -tileSize / 2 * 2 / 3,
      tileSize / 2,
      tileSize / 2 * 2 / 3,
      r,
      g,
      b,
      1.0f,
      1.0f,
  };
  std::vector<uint32_t> indices = {0, 3, 7, 7, 4, 0, 3, 2, 6, 6, 7, 3, 2, 1, 5,
                                   5, 6, 2, 1, 0, 4, 4, 5, 1, 4, 7, 5, 5, 7, 6};
  Model figureModel = Model(indices, vertices);
  QVector3D position = QVector3D(0.0f, 0.0f, 0.0f);
  GameObject *figure =
      new GameObject(figureModel, position, "../assets/Figure.png");
  return figure;
};
} // namespace QtLudo
