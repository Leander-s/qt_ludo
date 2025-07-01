#include "GameOpenGLWidget.h"

namespace QtLudo {
QOpenGLTexture *loadTexture(const char *path) {
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
  }
  return texture;
}

GameObject::GameObject(const Model &newModel, const char *texturePath)
    : model(newModel), texturePath(texturePath) {
  modelMatrix = QMatrix4x4();
  texturePath = "";
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

void GameOpenGLWidget::createBoard(float tileSize) {
  std::vector<int> indices = {0, 2, 1, 2, 3, 1};
  std::vector<float> vertices = {
      -7.5f * tileSize, 0.0f, -7.5f * tileSize, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      7.5f * tileSize,  0.0f, -7.5f * tileSize, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
      -7.5f * tileSize, 0.0f, 7.5f * tileSize,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      7.5f * tileSize,  0.0f, 7.5f * tileSize,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f};
  Model boardModel = Model(indices, vertices);
  QVector3D position = QVector3D(0.0f, 0.0f, 0.0f);
  GameObject *board =
      new GameObject(boardModel, position, "./assets/LudoBoard.png");
  initializeGameObject(board);
  gameObjects.push_back(board);
}

void GameOpenGLWidget::initializeGameObject(GameObject *gameObject) {
  if (!gameObject->texturePath.isEmpty()) {
    gameObject->texture = loadTexture(gameObject->texturePath.toUtf8().data());
  }
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
               gameObject->model.indices.size() * sizeof(int),
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
  if (!initializeOpenGLFunctions()) {
    std::cout << "Failed to initialize GL functions" << std::endl;
  }
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);

  createBoard(1.0f);

  shaderProgram = new QOpenGLShaderProgram();
  shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         "./shaders/vert.glsl");

  shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         "./shaders/frag.glsl");
  if (!shaderProgram->link()) {
    std::cout << "Linking shader program failed" << std::endl;
  }
}

void GameOpenGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GameOpenGLWidget::paintGL() {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QMatrix4x4 view, projection, model;

  view.lookAt(QVector3D(0.0f, 20.0f, 2.0f), QVector3D(0.0f, 0.0f, 1.0f),
              QVector3D(0.0f, 1.0f, 0.0f));
  projection.perspective(90, float(this->width()) / float(this->height()), 0.1f,
                         100.0f);

  shaderProgram->bind();
  shaderProgram->setUniformValue("projection", projection);
  shaderProgram->setUniformValue("view", view);

  for (GameObject *gameObject : gameObjects) {
    if (!gameObject->ready) {
      std::cout << "Object not ready\n";
      continue;
    }
    if (gameObject->texture == nullptr) {
      std::cout << "No texture\n";
      continue;
    }
    glActiveTexture(GL_TEXTURE0);
    gameObject->texture->bind();
    shaderProgram->setUniformValue("tex", 0);
    shaderProgram->setUniformValue("model", gameObject->modelMatrix);
    glBindVertexArray(gameObject->VAO);
    glDrawElements(GL_TRIANGLES, gameObject->model.indices.size(),
                   GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
  }
  shaderProgram->release();
}

void GameOpenGLWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape) {
    emit pauseGame();
  }
}
} // namespace QtLudo
