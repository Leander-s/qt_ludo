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

  game = new Ludo();
  gameObjects = game->createObjects();
  for (GameObject *gameObject : gameObjects) {
    initializeGameObject(gameObject);
    gameObject->texture = loadTexture(gameObject->texturePath.toUtf8().data());
  }
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

/*
void GameOpenGLWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape) {
    emit pauseGame();
  }
}
*/
} // namespace QtLudo
