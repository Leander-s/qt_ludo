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

  // Not a very elegant way to do this...
  if (!game->humanMove) {
    return;
  }

  LudoColor color = game->state->toMove;
  Player *player = game->players[game->getPlayer(color)];
  uint8_t offset = game->getPosition(color, 0);
  std::vector<bool> possibleMoves = player->getPossibleMoves(
      game->state->positions + offset, lastDieRoll, game->config);

  bool canMove = false;
  for (bool movePossible : possibleMoves) {
    if (movePossible) {
      canMove = true;
    }
  }

  if (!canMove) {
    game->applyMove(255, lastDieRoll);
    updateGameState();
    return;
  }
  switch (event->key()) {
  case Qt::Key_1:
    if (!possibleMoves[0]) {
      break;
    }
    game->applyMove(offset + 0, lastDieRoll);
    openglwidget->updatePosition(game->state->toMove, offset + 0);
    updateGameState();
    break;
  case Qt::Key_2:
    if (!possibleMoves[1]) {
      break;
    }
    game->applyMove(offset + 1, lastDieRoll);
    openglwidget->updatePosition(game->state->toMove, offset + 1);
    updateGameState();
    break;
  case Qt::Key_3:
    if (!possibleMoves[2]) {
      break;
    }
    game->applyMove(offset + 2, lastDieRoll);
    openglwidget->updatePosition(game->state->toMove, offset + 2);
    updateGameState();
    break;
  case Qt::Key_4:
    if (!possibleMoves[3]) {
      break;
    }
    game->applyMove(offset + 3, lastDieRoll);
    openglwidget->updatePosition(game->state->toMove, offset + 3);
    updateGameState();
    break;
  }
}

void GameWidget::startGame() {
  game->start();
  updateGameState();
}

void GameWidget::updateGameState() {
  game->humanMove = false;
  std::cout << printLudoColor(game->state->toMove) << "'s turn\n";
  Player *player = game->players[game->getPlayer(game->state->toMove)];
  uint32_t seed = std::time(0);
  lastDieRoll = game->roll(seed);
  if (player->human) {
    game->humanMove = true;
    return;
  }

  uint8_t *positions = game->state->positions;
  uint8_t pieceToMove = game->findMove(player, lastDieRoll);
  game->applyMove(pieceToMove, lastDieRoll);

  openglwidget->updatePosition(game->state->toMove, pieceToMove);
  updateGameState();
}

} // namespace QtLudo
