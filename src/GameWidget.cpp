#include "GameWidget.h"

namespace QtLudo {
GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
  QStackedLayout *layout = new QStackedLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);

  // I want to load maps from yaml/json/whatever in future
  config = (MapConfig){.numberOfPlayers = 4,
                       .numberOfPiecesPerPlayer = 4,
                       .numberOfPieces = 16,
                       .lengthOfPath = 66};

  game = new Ludo(config);

  openglwidget = new GameOpenGLWidget;
  pausemenu = new PauseMenuWidget;

  openglwidget->initializeGame(config, game->state);
  openglwidget->show();
  pausemenu->hide();
  paused = false;
  pausemenu->setContentsMargins(0, 0, 0, 0);

  layout->addWidget(openglwidget);
  layout->addWidget(pausemenu);
  pausemenu->raise();

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
  connect(pausemenu, &PauseMenuWidget::resumeGameSignal, pausemenu,
          &QWidget::hide);
  connect(pausemenu, &PauseMenuWidget::quitGameSignal, this,
          &GameWidget::quitToMenu);

  game->start();
  // updateGameState();
}

void GameWidget::togglePause() {
  if (paused) {
    pausemenu->hide();
    paused = false;
  } else {
    pausemenu->show();
    paused = true;
  }
}

void GameWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape) {
    togglePause();
  }

  if (!game->humanMove) {
    return;
  }
  LudoColor color = game->state->toMove;
  uint8_t offset = game->getPosition(color, 0);
  Player *player = &game->players[game->getPlayer(color)];
  uint8_t roll = game->roll(clock());
  std::vector<bool> possibleMoves = player->getPossibleMoves(
      game->state->positions, roll, game->config, game->getPosition(color, 0));

  if (event->key() == Qt::Key_1) {
      if(!possibleMoves[0]){
          return;
      }
      game->state->positions[0] += roll;
  }

  if (event->key() == Qt::Key_2) {
      if(!possibleMoves[1]){
          return;
      }
  }

  if (event->key() == Qt::Key_3) {
      if(!possibleMoves[2]){
          return;
      }
  }

  if (event->key() == Qt::Key_4) {
      if(!possibleMoves[3]){
          return;
      }
  }
}

void GameWidget::updateGameState() {
  std::array<uint8_t, 2> turnResult = game->update();
  uint8_t movedPiece = turnResult[0];
  uint8_t roll = turnResult[1];
  bool humansTurn = movedPiece == 255;
  if (humansTurn) {
    return;
  }

  openglwidget->updatePosition(game->state->toMove, movedPiece);
  updateGameState();
}

} // namespace QtLudo
