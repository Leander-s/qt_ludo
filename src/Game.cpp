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
  for (int i; i < 16; i++) {
    positions[i] = i % 4;
  }
}

std::vector<GameObject *> Ludo::createObjects() {
  std::cout << "Creating objects\n";
  std::vector<GameObject *> objects(16, nullptr);
  GameObject *board = createBoard(1.0f);
  for(int i = 0; i < 4; i++){
      GameObject *redFigure = createFigure(1.0f, ludo_color::red);
      GameObject *blueFigure = createFigure(1.0f, ludo_color::blue);
      GameObject *greenFigure = createFigure(1.0f, ludo_color::green);
      GameObject *yellowFigure = createFigure(1.0f, ludo_color::yellow);

      QVector2D redPosition = positionToCoords(ludo_color::red, i);
      QVector2D bluePosition = positionToCoords(ludo_color::blue, i);
      QVector2D greenPosition = positionToCoords(ludo_color::green, i);
      QVector2D yellowPosition = positionToCoords(ludo_color::yellow, i);

      redFigure->translate(QVector3D(redPosition.x(), 0.0f, redPosition.y()));
      blueFigure->translate(QVector3D(bluePosition.x(), 0.0f, bluePosition.y()));
      greenFigure->translate(QVector3D(greenPosition.x(), 0.0f, greenPosition.y()));
      yellowFigure->translate(QVector3D(yellowPosition.x(), 0.0f, yellowPosition.y()));

      objects[i] = redFigure;
      objects[i + 4] = greenFigure;
      objects[i + 8] = blueFigure;
      objects[i + 12] = yellowFigure;
  }

  objects.push_back(board);
  return objects;
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

GameObject *Ludo::createFigure(float tileSize, ludo_color color) {
    float r = 0.0f,g = 0.0f,b = 0.0f;
    switch(color){
        case ludo_color::red:
            r = 1.0f;
            g = 0.0f;
            b = 0.0f;
            break;
        case ludo_color::blue:
            r = 0.0f;
            g = 0.0f;
            b = 1.0f;
            break;
        case ludo_color::green:
            r = 0.0f;
            g = 128.0f/255.0f;
            b = 0.0f;
            break;
        case ludo_color::yellow:
            r = 0.7f;
            g = 0.7f;
            b = 0.0f;
            break;
    }
    std::vector<float> vertices = {
        -tileSize/2 * 2/3, 0.0f, -tileSize/2 * 2/3, r, g, b, 0.0f, 0.0f,
        tileSize/2 * 2/3, 0.0f, -tileSize/2 * 2/3, r, g, b, 1.0f, 0.0f,
        tileSize/2 * 2/3, 0.0f, tileSize/2 * 2/3, r, g, b, 0.0f, 0.0f,
        -tileSize/2 * 2/3, 0.0f, tileSize/2 * 2/3, r, g, b, 1.0f, 0.0f,

        -tileSize/2 * 2/3, tileSize/2, -tileSize/2 * 2/3, r, g, b, 0.0f, 1.0f,
        tileSize/2 * 2/3, tileSize/2, -tileSize/2 * 2/3, r, g, b, 1.0f, 1.0f,
        tileSize/2 * 2/3, tileSize/2, tileSize/2 * 2/3, r, g, b, 0.0f, 1.0f,
        -tileSize/2 * 2/3, tileSize/2, tileSize/2 * 2/3, r, g, b, 1.0f, 1.0f,
    };
  std::vector<uint32_t> indices = {
      0, 3, 7, 7, 4, 0,
      3, 2, 6, 6, 7, 3,
      2, 1, 5, 5, 6, 2, 
      1, 0, 4, 4, 5, 1,
      4, 7, 5, 5, 7, 6
  };
  Model figureModel = Model(indices, vertices);
  QVector3D position = QVector3D(0.0f, 0.0f, 0.0f);
  GameObject *figure = new GameObject(figureModel, position, "../assets/Figure.png");
  return figure;
};

QVector2D Ludo::positionToCoords(ludo_color color, uint8_t position,
                                 float tileSize) {
  QVector2D red_coords = positionMappings[position];
  QVector2D coords;
  switch (color) {
  case ludo_color::red:
    coords = red_coords;
    break;
  case ludo_color::blue:
    coords = QVector2D(-red_coords.y(), red_coords.x());
    break;
  case ludo_color::yellow:
    coords = QVector2D(-red_coords.x(), -red_coords.y());
    break;
  case ludo_color::green:
    coords = QVector2D(red_coords.y(),  -red_coords.x());
    break;
  default:
    throw std::invalid_argument(
            "Color should be red, green, blue or yellow from enum ludo_color");
  };
  return coords;
}

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
