#include "GameWidget.h"

namespace QtLudo {
GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
  QStackedLayout *layout = new QStackedLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);

  map.initializeMap();

  game = new Ludo(&map);

  openglwidget = new GameOpenGLWidget;
  pausemenu = std::make_shared<PauseMenuWidget>(new PauseMenuWidget);

  openglwidget->initializeGame(&map);
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

  const quint8 playerIndex = game->getToMove();
  const quint8 playerOffset = game->getFigure(playerIndex, 0);
  Player *player = &game->players[playerIndex];
  LOG("Getting possible moves for roll: " << (int)lastDieRoll);
  const QVector<bool> possibleMoves = player->getPossibleMoves(
      game->state.positions, playerOffset, lastDieRoll, config);

  bool canMove = false;
  for (const bool movePossible : possibleMoves) {
    if (movePossible) {
      canMove = true;
    }
  }

  if (!canMove) {
    LOG("Player cannot move");
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
    LOG("Not a possible move");
    return;
  }

  LOG("Player played " << (int)playerFigure);
  quint8 figure = game->applyMove(playerIndex, playerFigure, lastDieRoll);
  if (figure == 255) {
    updateGameState();
  }
  openglwidget->updatePosition(figure, game->getPosition(figure));
  updateGameState();
}

void GameWidget::startGame() {
  game->start();
  updateGameState();
}

void GameWidget::updateGameState() {
  game->humanMove = false;

  const quint8 playerIndex = game->getToMove();
  const Player *player = &game->players[playerIndex];
  const LudoColor color = player->color;
  LOG("\n" << printLudoColor(color) << "'s turn");
  std::cout << "Game state ";
  for(int i = 0; i < config.numberOfPieces; i++){
      std::cout << (int)game->state.positions[i] << ", ";
  }
  std::cout << std::endl;
  lastDieRoll = game->roll();
  LOG("Rolled " << (int)lastDieRoll);
  if (player->human) {
    game->humanMove = true;
    return;
  }

  const quint8 playerFigure = game->findMove(playerIndex, lastDieRoll);
  const quint8 figure = game->applyMove(playerIndex, playerFigure, lastDieRoll);

  if (figure == 255) {
    updateGameState();
    return;
  }

  LOG("Updating coords of figure " << (int)figure << " of player "
                                   << (int)playerIndex << " with "
                                   << (int)game->getPosition(figure));
  openglwidget->updatePosition(figure, game->getPosition(figure));
  updateGameState();
}
} // namespace QtLudo
