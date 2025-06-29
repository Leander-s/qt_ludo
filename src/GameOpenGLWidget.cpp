#include "GameOpenGLWidget.h"

namespace QtLudo {
GameObject::GameObject(const GameObject &other) {
    modelMatrix = other.modelMatrix;
    model = other.model;
    VAO = other.VAO;
    VBO = other.VBO;
    IBO = other.IBO;
    ready = other.ready;
}
GameObject::GameObject(const Model &newModel) : model(newModel) {
  modelMatrix = QMatrix4x4();
  ready = false;
}

GameObject::GameObject(const Model &newModel, const QVector3D &position) : model(newModel) {
  modelMatrix = QMatrix4x4();
  modelMatrix.translate(position);
  ready = false;
}

void GameObject::translate(const QVector3D &translation) {
  modelMatrix.translate(translation);
}

void GameObject::rotate(float angle, const QVector3D &axis) {
  modelMatrix.rotate(angle, axis);
}

GameOpenGLWidget::GameOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), VAO(0), VBO(0), IBO(0), shaderProgram(nullptr) {
  this->setFocusPolicy(Qt::StrongFocus);
}

GameOpenGLWidget::~GameOpenGLWidget() {
  makeCurrent();
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &IBO);
  glDeleteVertexArrays(1, &VAO);
  delete shaderProgram;
  doneCurrent();
}

void GameOpenGLWidget::initializeGameObject(GameObject &gameObject) {
  // VAO
  glGenVertexArrays(1, &gameObject.VAO);
  glBindVertexArray(gameObject.VAO);

  // Vertex attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // VBO
  glGenBuffers(1, &gameObject.VBO);
  glBindBuffer(GL_ARRAY_BUFFER, gameObject.VBO);
  glBufferData(GL_ARRAY_BUFFER,
               gameObject.model.vertices.size() * sizeof(float),
               gameObject.model.vertices.data(), GL_STATIC_DRAW);

  // IBO
  glGenBuffers(1, &gameObject.IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gameObject.IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               gameObject.model.indices.size() * sizeof(int),
               gameObject.model.indices.data(), GL_STATIC_DRAW);

  glBindVertexArray(0);
  gameObject.ready = true;
}

void GameOpenGLWidget::initializeGL() {
  if (!initializeOpenGLFunctions()) {
    std::cout << "Failed to initialize GL functions" << std::endl;
  }

  for (float i = -5.0f; i < 5.5f; i += 1.0f) {
    for (float j = -5.0f; j < 5.5f; j += 1.0f) {
      QColor tileColor;
      if (int(i + j) % 2 == 0) {
        tileColor.setRgbF(1.0f, 1.0f, 1.0f, 1.0f);
      } else {
        tileColor.setRgbF(0.5f, 0.5f, 0.5f, 1.0f);
      }
      GroundTile tile = GroundTile(1.0f, tileColor);
      QVector3D position = QVector3D(i, 0.0f, j);
      GameObject tileObject = GameObject(tile.model, position);
      initializeGameObject(tileObject);
      gameObjects.push_back(tileObject);
    }
  }

  glCullFace(GL_BACK);

  shaderProgram = new QOpenGLShaderProgram();
  shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                         "./shaders/vert.glsl");

  shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                         "./shaders/frag.glsl");
  shaderProgram->link();
}

void GameOpenGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GameOpenGLWidget::paintGL() {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glCullFace(GL_BACK);

  QMatrix4x4 view, projection, model;

  view.lookAt(QVector3D(0.0f, 25.0f, 2.0f), QVector3D(0.0f, 0.0f, -1.0f),
              QVector3D(0.0f, 1.0f, 0.0f));
  projection.ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 50.0f);

  shaderProgram->bind();
  shaderProgram->setUniformValue("projection", projection);
  shaderProgram->setUniformValue("view", view);

  for (GameObject &gameObject : gameObjects) {
    if (!gameObject.ready) {
      continue;
    }
    shaderProgram->setUniformValue("model", gameObject.modelMatrix);
    glBindVertexArray(gameObject.VAO);
    glDrawElements(GL_TRIANGLES, gameObject.model.indices.size(),
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
