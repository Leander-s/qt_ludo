#pragma once
// Mine
#include <Game.h>
#include <GameOpenGLWidget.h>
#include <HUDWidget.h>
#include <PauseMenuWidget.h>

// Qt
#include <QSizePolicy>
#include <QStackedLayout>
#include <QTimer>
#include <QWidget>
#include <qevent.h>

namespace QtLudo {
struct currentPlayer {
        quint8 index;
        quint8 offset;
        Player *player;
        QVector<bool> possibleMoves;
        quint8 roll;
        quint8 choice;
};

class GameWidget : public QWidget {
        Q_OBJECT

      public:
        GameWidget(QWidget *parent = nullptr);
        void startGame();
        void endGame();

      private:
        GameOpenGLWidget *openglwidget;
        std::shared_ptr<PauseMenuWidget> pausemenu;
        std::unique_ptr<HUDWidget> hud;
        Ludo *game;
        Map map;
        Camera camera;
        bool paused;
        currentPlayer player;

        bool mouseHeld;
        std::optional<QVector2D> lastMousePos;

        void keyPressEvent(QKeyEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void getNewGameState();
        void setNewGameState();

      signals:
        void quitToMenuSignal();

      private slots:
        // void humanCommitted();
        void togglePause();
        void quitToMenuSlot();
};
} // namespace QtLudo
