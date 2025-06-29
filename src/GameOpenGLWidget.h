#pragma once
#include <QWidget>
#include <QtOpenGL/QOpenGLFunctions_3_3_Core>
#include <QtOpenGL/QOpenGLShaderProgram>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QKeyEvent>
#include <iostream>
#include "ModelUtil.h"

namespace QtLudo {
class GameOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
  Q_OBJECT

public:
  explicit GameOpenGLWidget(QWidget *parent = nullptr);
  ~GameOpenGLWidget();

protected:
  void initializeGL() override;

  void resizeGL(int w, int h) override;

  void paintGL() override;

  void keyPressEvent(QKeyEvent *event) override;

signals:
  void pauseGame();

private:
  GLuint VAO, VBO, IBO;
  QOpenGLShaderProgram *shaderProgram;
  GameGrid *grid;
  std::vector<float> vertices;
  std::vector<int> indices;
};
} // namespace QtLudo
