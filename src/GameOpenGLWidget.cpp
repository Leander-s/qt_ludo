#include "GameOpenGLWidget.h"

namespace QtLudo {
GameOpenGLWidget::GameOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), VAO(0), VBO(0), IBO(0), shaderProgram(nullptr) {
  this->setFocusPolicy(Qt::StrongFocus);
  grid = new GameGrid(-15.0f, 0.0f, -15.0f, 2.0f, 15, 15);

  indices.insert(indices.end(), grid->model->indices.begin(),
          grid->model->indices.end());
  vertices.insert(vertices.end(), grid->model->vertices.begin(),
          grid->model->vertices.end());
}

GameOpenGLWidget::~GameOpenGLWidget() {
  makeCurrent();
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &IBO);
  glDeleteVertexArrays(1, &VAO);
  delete shaderProgram;
  doneCurrent();
}

void GameOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();

  // VAO
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // VBO
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(),
               GL_STATIC_DRAW);

  // IBO
  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(),
               GL_STATIC_DRAW);

  // Vertex attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);

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
  shaderProgram->setUniformValue("model", model);
  shaderProgram->setUniformValue("projection", projection);
  shaderProgram->setUniformValue("view", view);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
  shaderProgram->release();
}

void GameOpenGLWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape) {
    emit pauseGame();
  }
}
} // namespace QtLudo
