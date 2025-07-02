#include "Game.h"

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
  for (int i; i < 16; i++) {
    positions[i] = i % 4;
  }
};

std::vector<GameObject *> Ludo::createObjects() {
  std::vector<GameObject *> objects;
  GameObject *board = createBoard(1.0f);

  objects.push_back(board);
  return objects;
}

GameObject *Ludo::createBoard(float tileSize) {
  std::vector<uint32_t> indices = {0, 2, 1, 2, 3, 1};
  std::vector<float> vertices = {
      -7.5f * tileSize, 0.0f, -7.5f * tileSize, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      7.5f * tileSize,  0.0f, -7.5f * tileSize, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
      -7.5f * tileSize, 0.0f, 7.5f * tileSize,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      7.5f * tileSize,  0.0f, 7.5f * tileSize,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f};
  Model boardModel = Model(indices, vertices);
  QVector3D position = QVector3D(0.0f, 0.0f, 0.0f);
  GameObject *board =
      new GameObject(boardModel, position, "../assets/LudoBoard.png");
  return board;
}

GameObject *Ludo::createFigure(float tileSize) {};

std::array<float, 2> Ludo::rotateCoords(std::array<float, 2> coords,
                                        ludo_color color, float tileSize){
    switch(color){
        case ludo_color::red:
            return coords;
        case ludo_color::blue:
            coords = {coords[1], coords[0]};
            return coords;
        case ludo_color::green:
            coords = {150 * tileSize - coords[0], 150 * tileSize - coords[1]};
            return coords;
        case ludo_color::yellow:
            coords = {150 * tileSize - coords[1], 150 * tileSize - coords[0]};
            return coords;
    };
  throw std::invalid_argument(
      "Color should be red, green, blue or yellow from enum ludo_color");
}

std::array<float, 2> Ludo::positionToCoords(ludo_color color, uint8_t position,
                                            float tileSize) {
  std::array<float, 2> coords;
  if (position < 4) {
    switch (position) {
    case 0:
      coords = {1.0f * tileSize, 1.0f * tileSize};
      break;
    case 1:
      coords = {4.0f * tileSize, 1.0f * tileSize};
      break;
    case 2:
      coords = {1.0f * tileSize, 4.0f * tileSize};
      break;
    case 3:
      coords = {4.0f * tileSize, 4.0f * tileSize};
      break;
    }
    return rotateCoords(coords, color, tileSize);
  }
};

uint8_t Ludo::getPosition(ludo_color color, int index) {
  if (index > 3) {
    throw std::invalid_argument("There are only 4 pieces per color");
  }
  switch (color) {
  case ludo_color::red:
    return positions[index];
  case ludo_color::green:
    return positions[index + 4];
  case ludo_color::blue:
    return positions[index + 8];
  case ludo_color::yellow:
    return positions[index + 12];
  }
  throw std::invalid_argument(
      "Color should be red, green, blue or yellow from enum ludo_color");
}
} // namespace QtLudo
