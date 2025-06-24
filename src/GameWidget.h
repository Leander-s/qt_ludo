#include <QWidget>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtOpenGL/QOpenGLFunctions_3_3_Core>
#include <QtOpenGL/QOpenGLShaderProgram>

namespace QtLudo {
class GameWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

    public:
        explicit GameWidget(QWidget *parent = nullptr);
        ~GameWidget();

    protected:
        void initializeGL() override;

        void resizeGL(int w, int h) override;

        void paintGL() override;

    private:
        GLuint VAO, VBO, IBO;
        QOpenGLShaderProgram *shaderProgram;
};
} // namespace QtLudo
