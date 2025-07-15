#include "GameOpenGLWidget.h"

namespace QtLudo {
GameOpenGLWidget::GameOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), shaderProgram(nullptr) {
  this->setFocusPolicy(Qt::StrongFocus);
}

GameOpenGLWidget::~GameOpenGLWidget() {
  makeCurrent();
  for (GameObject *gameObject : gameObjects) {
    glDeleteBuffers(1, &gameObject->VBO);
    glDeleteBuffers(1, &gameObject->IBO);
    glDeleteVertexArrays(1, &gameObject->VAO);
    delete gameObject;
  }
  delete shaderProgram;
  doneCurrent();
}

QOpenGLTexture *GameOpenGLWidget::loadTexture(const char *path) {
  QImage image(path);
  if (image.isNull()) {
    qDebug() << "Failed to load texture!";
    return nullptr;
  }

  QImage formattedImage = image.convertToFormat(QImage::Format_RGBA8888);

  QOpenGLTexture *texture = new QOpenGLTexture(formattedImage);
  texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
  texture->setMagnificationFilter(QOpenGLTexture::Linear);
  texture->setWrapMode(QOpenGLTexture::Repeat);
  if (!texture->isCreated()) {
    std::cout << "Texture not created properly!\n";
    delete texture;
    return nullptr;
  }
  return texture;
}

void GameOpenGLWidget::initializeGameObject(GameObject *gameObject) {
  // VAO
  glGenVertexArrays(1, &gameObject->VAO);
  glBindVertexArray(gameObject->VAO);

  // VBO
  glGenBuffers(1, &gameObject->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, gameObject->VBO);
  glBufferData(GL_ARRAY_BUFFER,
               gameObject->model.vertices.size() * sizeof(float),
               gameObject->model.vertices.data(), GL_STATIC_DRAW);

  // IBO
  glGenBuffers(1, &gameObject->IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gameObject->IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               gameObject->model.indices.size() * sizeof(uint32_t),
               gameObject->model.indices.data(), GL_STATIC_DRAW);

  // Vertex attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);
  gameObject->ready = true;
}

void GameOpenGLWidget::initializeGL() {
  std::cout << "Initializing GL\n";
  if (!initializeOpenGLFunctions()) {
    std::cout << "Failed to initialize GL functions" << std::endl;
  }

  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);

  shaderProgram = new QOpenGLShaderProgram();
  shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         "./shaders/vert.glsl");

  shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         "./shaders/frag.glsl");
  if (!shaderProgram->link()) {
    std::cout << "Linking shader program failed" << std::endl;
  }
  // :)
  for (GameObject *gameObject : gameObjects) {
    initializeGameObject(gameObject);
    gameObject->texture = loadTexture(gameObject->texturePath.toUtf8().data());
  }
}

void GameOpenGLWidget::initializeGame(Map *_map, GameState *_state) {
  map = _map;
  gameState = _state;
  config = map->getMapConfig();
  gameObjects = createObjects();
}

void GameOpenGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GameOpenGLWidget::paintGL() {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QMatrix4x4 view, projection, model;

  view.lookAt(QVector3D(0.0f, 8.0f, 2.0f), QVector3D(0.0f, 0.0f, 1.0f),
              QVector3D(0.0f, 1.0f, 0.0f));
  projection.perspective(90, float(this->width()) / float(this->height()), 0.1f,
                         100.0f);

  shaderProgram->bind();
  shaderProgram->setUniformValue("projection", projection);
  shaderProgram->setUniformValue("view", view);
  shaderProgram->setUniformValue("tex", 0);
  glActiveTexture(GL_TEXTURE0);

  for (GameObject *gameObject : gameObjects) {
    if (!gameObject || !gameObject->ready || !gameObject->texture) {
      std::cout << "Object not ready\n";
      continue;
    }

    gameObject->texture->bind();
    shaderProgram->setUniformValue("model", gameObject->modelMatrix);
    glBindVertexArray(gameObject->VAO);
    glDrawElements(GL_TRIANGLES, gameObject->model.indices.size(),
                   GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
    gameObject->texture->release();
  }
  shaderProgram->release();
}

void GameOpenGLWidget::updatePosition(const quint8 totalFigureIndex) {
  quint8 position = gameState->positions[totalFigureIndex];
  QVector2D coords = map->getCoords(totalFigureIndex, position);
  GameObject *object = gameObjects[totalFigureIndex];
  object->setPosition(QVector3D(coords.x(), 0.0f, coords.y()));
}

void GameOpenGLWidget::updateAllPositions() {
  for (int playerIndex = 0; playerIndex < config.numberOfPlayers;
       playerIndex++) {
    for (int figureIndex = 0; figureIndex < config.numberOfPiecesPerPlayer;
         figureIndex++) {

      QVector2D figureCoords = map->getCoords(figureIndex, playerIndex);
      GameObject *figureObject = gameObjects[playerIndex];
      figureObject->setPosition(
          QVector3D(figureCoords.x(), 0.0f, figureCoords.y()));
    }
  }
}

std::vector<GameObject *> GameOpenGLWidget::createObjects() {
  std::vector<GameObject *> objects(config.numberOfPieces, nullptr);
  const float defaultTileSize = 1.0f;
  GameObject *board = createBoard();
  // For now we just give all the colors to the players in order
  LudoColor color = LudoColor::red;
  for (int playerIndex = 0; playerIndex < config.numberOfPlayers;
       playerIndex++) {
    for (int figureIndex = 0; figureIndex < config.numberOfPiecesPerPlayer;
         figureIndex++) {
      GameObject *figure = createFigure(color);

      QVector2D figureCoords = map->getCoords(figureIndex, playerIndex);

      // All of the figures start at the calculated start position and y = 0
      figure->translate(QVector3D(figureCoords.x(), 0.0f, figureCoords.y()));
      objects.push_back(figure);
    }
    color++;
  }

  objects.push_back(board);
  return objects;
}

GameObject *GameOpenGLWidget::createFigure(LudoColor color) {
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
      -1.0f / 2 * 2 / 3, 0.0f,     -1.0f / 2 * 2 / 3, r, g, b, 0.0f, 0.0f,
      1.0f / 2 * 2 / 3,  0.0f,     -1.0f / 2 * 2 / 3, r, g, b, 1.0f, 0.0f,
      1.0f / 2 * 2 / 3,  0.0f,     1.0f / 2 * 2 / 3,  r, g, b, 0.0f, 0.0f,
      -1.0f / 2 * 2 / 3, 0.0f,     1.0f / 2 * 2 / 3,  r, g, b, 1.0f, 0.0f,

      -1.0f / 2 * 2 / 3, 1.0f / 2, -1.0f / 2 * 2 / 3, r, g, b, 0.0f, 1.0f,
      1.0f / 2 * 2 / 3,  1.0f / 2, -1.0f / 2 * 2 / 3, r, g, b, 1.0f, 1.0f,
      1.0f / 2 * 2 / 3,  1.0f / 2, 1.0f / 2 * 2 / 3,  r, g, b, 0.0f, 1.0f,
      -1.0f / 2 * 2 / 3, 1.0f / 2, 1.0f / 2 * 2 / 3,  r, g, b, 1.0f, 1.0f};
  std::vector<uint32_t> indices = {0, 3, 7, 7, 4, 0, 3, 2, 6, 6, 7, 3, 2, 1, 5,
                                   5, 6, 2, 1, 0, 4, 4, 5, 1, 4, 7, 5, 5, 7, 6};
  Model figureModel = Model(indices, vertices);
  QVector3D position = QVector3D(0.0f, 0.0f, 0.0f);
  GameObject *figure =
      new GameObject(figureModel, position, "../assets/Figure.png");
  return figure;
};

GameObject *GameOpenGLWidget::createBoard() {
  std::vector<uint32_t> indices = {0, 2, 1, 2, 3, 1};
  std::vector<float> vertices = {
      -7.5f * 1.0f, 0.0f, -7.5f * 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      7.5f * 1.0f,  0.0f, -7.5f * 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      -7.5f * 1.0f, 0.0f, 7.5f * 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      7.5f * 1.0f,  0.0f, 7.5f * 1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f};
  Model boardModel = Model(indices, vertices);
  QVector3D position = QVector3D(0.0f, 0.0f, 0.0f);
  GameObject *board =
      new GameObject(boardModel, position, "../assets/LudoBoard.png");
  return board;
}
/*
void GameOpenGLWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape) {
    emit pauseGame();
  }
}
*/
} // namespace QtLudo
