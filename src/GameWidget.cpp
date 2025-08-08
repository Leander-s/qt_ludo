#include <GameWidget.h>

namespace QtLudo {
GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
        QStackedLayout *layout = new QStackedLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setStackingMode(QStackedLayout::StackAll);

        openglwidget = new GameOpenGLWidget;
        pausemenu = std::make_shared<PauseMenuWidget>();
        hud = std::make_unique<HUDWidget>();

        pausemenu->setContentsMargins(0, 0, 0, 0);
        paused = false;

        layout->addWidget(openglwidget);
        layout->addWidget(pausemenu.get());
        layout->addWidget(hud.get());

        pausemenu->raise();
        pausemenu->hide();
        hud->show();

        /*
        QTimer *timer = new QTimer;
        connect(timer, &QTimer::timeout, openglwidget,
                QOverload<>::of(&GameOpenGLWidget::update)); timer->start(16);
        */
        connect(openglwidget, &QOpenGLWidget::frameSwapped, openglwidget,
                QOverload<>::of(&GameOpenGLWidget::update));
        /*
        connect(openglwidget, &GameOpenGLWidget::pauseGame, this,
                &GameWidget::togglePause);
        */
        connect(pausemenu.get(), &PauseMenuWidget::resumeGameSignal, this,
                &GameWidget::togglePause);
        connect(pausemenu.get(), &PauseMenuWidget::quitGameSignal, this,
                &GameWidget::quitToMenuSlot);
}

void GameWidget::quitToMenuSlot() {
        endGame();
        emit quitToMenuSignal();
}

void GameWidget::togglePause() {
        if (paused) {
                pausemenu->hide();
                paused = false;
                QMetaObject::invokeMethod(this, &GameWidget::setNewGameState,
                                          Qt::QueuedConnection);
        } else {
                pausemenu->show();
                paused = true;
        }
}

void GameWidget::startGame() {
        game = new Ludo();
        openglwidget->initializeGame(game->map);
        game->start();
        getNewGameState();
}

void GameWidget::endGame() {
        delete openglwidget;
        delete game;
}

void GameWidget::getNewGameState() {
        game->humanMove = false;
        player.index = game->getToMove();
        player.player = &game->players[player.index];
        LOG("\n" << printLudoColor(player.player->color) << "'s turn");
        player.roll = game->roll();
        hud->update(player.roll);
        player.possibleMoves = player.player->getPossibleMoves(
            game->state.positions, player.offset, player.roll,
            game->map->getMapConfig());
        bool canMove = false;
        for (bool movePossible : player.possibleMoves) {
                if (movePossible) {
                        canMove = true;
                        break;
                }
        }
        if (!canMove) {
                player.choice = 255;
                setNewGameState();
        }
        if (player.player->human) {
                game->humanMove = true;
                return;
        }
        player.choice = game->findMove(player.index, player.roll);
        setNewGameState();
}

void GameWidget::setNewGameState() {
        if (paused)
                return;
        delay(1);
        const std::array<quint8, 2> figures =
            game->applyMove(player.index, player.choice, player.roll);

        if (figures[0] == 255) {
                QMetaObject::invokeMethod(this, &GameWidget::getNewGameState,
                                          Qt::QueuedConnection);
                return;
        }

        for (const quint8 figure : figures) {
                if (figure == 255)
                        continue;
                openglwidget->updatePosition(figure, game->getPosition(figure));
        }
        QMetaObject::invokeMethod(this, &GameWidget::getNewGameState,
                                  Qt::QueuedConnection);
}

void GameWidget::keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Escape) {
                togglePause();
        }

        // Not a very elegant way to do this...
        if (!game->humanMove) {
                return;
        }

        if (paused) {
                return;
        }

        player.choice = 255;
        switch (event->key()) {
        case Qt::Key_1:
                if (!player.possibleMoves[0]) {
                        break;
                }
                player.choice = 0;
                break;
        case Qt::Key_2:
                if (!player.possibleMoves[1]) {
                        break;
                }
                player.choice = 1;
                break;
        case Qt::Key_3:
                if (!player.possibleMoves[2]) {
                        break;
                }
                player.choice = 2;
                break;
        case Qt::Key_4:
                if (!player.possibleMoves[3]) {
                        break;
                }
                player.choice = 3;
                break;
        }

        if (player.choice == 255) {
                LOG("Not a possible move");
                return;
        }

        LOG("Player played " << (int)player.choice);
        setNewGameState();
}
} // namespace QtLudo
