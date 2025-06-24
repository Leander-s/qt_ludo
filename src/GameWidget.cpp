#include "GameWidget.h"

namespace QtLudo {
GameWidget::GameWidget(QWidget *parent)
    : QOpenGLWidget(parent), VAO(0), VBO(0), IBO(0), shaderProgram(nullptr) {}

GameWidget::~GameWidget() {
    makeCurrent();
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteVertexArrays(1, &VAO);
    delete shaderProgram;
    doneCurrent();
}

void GameWidget::initializeGL() { 
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); 
}

void GameWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GameWidget::paintGL() { glClear(GL_COLOR_BUFFER_BIT); }
} // namespace QtLudo
