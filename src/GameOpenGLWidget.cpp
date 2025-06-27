#include "GameOpenGLWidget.h"
#include <GL/gl.h>

namespace QtLudo {
GameOpenGLWidget::GameOpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent), VAO(0), VBO(0), IBO(0), shaderProgram(nullptr) {
  this->setFocusPolicy(Qt::StrongFocus);
  grid = new GameGrid(-5.0f, 0.0f, -5.0f, 1.0f, 10, 10);
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

  glCullFace(GL_BACK);

  indices.insert(indices.end(), grid->model->indices.begin(),
                 grid->model->indices.end());
  vertices.insert(vertices.end(), grid->model->vertices.begin(),
                  grid->model->vertices.end());

  // VAO
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // VBO
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

  // IBO
  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
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

  shaderProgram->bind();
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
  shaderProgram->release();
}

void GameOpenGLWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape) {
    emit pauseGame();
  }
}
} // namespace QtLudo
