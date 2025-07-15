#include "GameWidget.h"

namespace QtLudo {
GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
  QStackedLayout *layout = new QStackedLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);

  map.initializeMap();

  game = std::make_unique<Ludo>(Ludo(&map));

  openglwidget = new GameOpenGLWidget;
  pausemenu = std::make_shared<PauseMenuWidget>(new PauseMenuWidget);

  openglwidget->initializeGame(&map, &game->state);
  openglwidget->show();
  pausemenu->hide();
  paused = false;
  pausemenu->setContentsMargins(0, 0, 0, 0);

  layout->addWidget(openglwidget);
  layout->addWidget(pausemenu.get());
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
  connect(pausemenu.get(), &PauseMenuWidget::resumeGameSignal, pausemenu.get(),
          &QWidget::hide);
  connect(pausemenu.get(), &PauseMenuWidget::quitGameSignal, this,
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

  const Player *player = &game->players[game->state.toMoveIndex];
  const quint8 playerIndex = game->state.toMoveIndex;
  const quint8 offset = game->getFigure(playerIndex, 0);
  const std::vector<bool> possibleMoves = player->getPossibleMoves(
      game->state.positions + offset, lastDieRoll, game->config);

  bool canMove = false;
  for (const bool movePossible : possibleMoves) {
    if (movePossible) {
      canMove = true;
    }
  }

  if (!canMove) {
    game->applyMove(playerIndex, 255, lastDieRoll);
    updateGameState();
    return;
  }
  quint8 playerFigure = 255;
  switch (event->key()) {
  case Qt::Key_1:
    if (!possibleMoves[0]) {
      break;
    }
    playerFigure = 0;
    break;
  case Qt::Key_2:
    if (!possibleMoves[1]) {
      break;
    }
    playerFigure = 1;
    break;
  case Qt::Key_3:
    if (!possibleMoves[2]) {
      break;
    }
    playerFigure = 2;
    break;
  case Qt::Key_4:
    if (!possibleMoves[3]) {
      break;
    }
    playerFigure = 3;
    break;
  }

  if (playerFigure == 255) {
    return;
  }

  game->applyMove(playerIndex, playerFigure, lastDieRoll);
  quint8 figure = game->getFigure(playerIndex, playerFigure);
  openglwidget->updatePosition(figure);
  updateGameState();
}

void GameWidget::startGame() {
  game->start();
  updateGameState();
}

void GameWidget::updateGameState() {
  game->humanMove = false;

  const quint8 playerIndex = game->state.toMoveIndex;
  const Player *player = &game->players[playerIndex];
  const LudoColor color = player->color;
  LOG(printLudoColor(color) << "'s turn\n");
  const quint32 seed = std::time(0);
  lastDieRoll = game->roll(seed);
  LOG("Rolled");
  if (player->human) {
    game->humanMove = true;
    return;
  }

  const quint8 *positions = game->state.positions;
  LOG("Finding move");
  const quint8 playerFigure = game->findMove(playerIndex, lastDieRoll);
  LOG("Applying move");
  game->applyMove(playerIndex, playerFigure, lastDieRoll);
  LOG("Getting figure");
  const quint8 figure = game->getFigure(playerIndex, playerFigure);

  LOG("Updating position");
  openglwidget->updatePosition(figure);
  updateGameState();
}

} // namespace QtLudo
