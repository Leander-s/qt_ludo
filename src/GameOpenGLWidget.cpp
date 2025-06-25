#include "GameOpenGLWidget.h"

namespace QtLudo {
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

void GameOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();

  // some test vertices
  float vertices[] = {
      -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f,
      1.0f,  0.0f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
  };

  GLuint indices[] = {0, 1, 2};

  // VAO
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // VBO
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // IBO
  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  // Vertex attributes
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
          (void *)(2 * sizeof(float)));
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

void GameOpenGLWidget::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_Escape){
        emit pauseGame();
    }
}
} // namespace QtLudo
