#pragma once
#include <QMatrix4x4>
#include <QVector3D>

namespace QtLudo {
class Camera {
      public:
        Camera();
        QMatrix4x4 getView() const;
        QMatrix4x4 getProjection(const float width, const float height) const;
        QVector3D getForwardVec() const;
        QVector3D getRightVec() const;
        QVector3D getUpVec() const;

        void move(const QVector3D &moveVec);
        void rotateCamera(const QVector3D &axis, const float angle);

        // probably won't need this tbh
        void rotateView(const QVector3D &axis, const float angle);

      private:
        QVector3D eye;
        QVector3D center;
        QVector3D up;
        float fov;
        float near;
        float far;
};
} // namespace QtLudo
