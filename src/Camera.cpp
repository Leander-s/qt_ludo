#include <Camera.h>
#include <qcontainerfwd.h>

namespace QtLudo {
Camera::Camera() {
        eye = QVector3D(0.0f, 8.0f, 2.0f);
        center = QVector3D(0.0f, 0.0f, 1.0f);
        up = QVector3D(0.0f, 1.0f, 0.0f);

        fov = 90.0f;
        near = 0.1f;
        far = 100.0f;
}

QMatrix4x4 Camera::getView() const {
        QMatrix4x4 view;
        view.lookAt(eye, center, up);
        return view;
}

QMatrix4x4 Camera::getProjection(const float width, const float height) const {
        QMatrix4x4 perspective;
        perspective.perspective(fov, width / height, near, far);
        return perspective;
}

QVector3D Camera::getForwardVec() const {
    return (eye - center).normalized();
}

QVector3D Camera::getRightVec() const {
    QVector3D forward = getForwardVec();
    return QVector3D::crossProduct(up, forward).normalized();
}

QVector3D Camera::getUpVec() const {
    QVector3D forward = getForwardVec();
    QVector3D right = getRightVec();
    return QVector3D::crossProduct(forward, right).normalized();
}

void Camera::move(const QVector3D &moveVec) { eye += moveVec; }

void Camera::rotateCamera(const QVector3D &axis, const float angle) {
        QVector3D eye_centered = eye - center;
        QQuaternion quat =
            QQuaternion::fromAxisAndAngle(axis.normalized(), angle);
        eye_centered = quat.rotatedVector(eye_centered);
        eye = eye_centered + center;
}

void Camera::rotateView(const QVector3D &axis, const float angle) {
        QVector3D center_centered = center - eye;
        QQuaternion quat =
            QQuaternion::fromAxisAndAngle(axis.normalized(), angle);
        center_centered = quat.rotatedVector(center_centered);
        center = center_centered + eye;
}
} // namespace QtLudo
