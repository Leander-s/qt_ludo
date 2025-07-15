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
  std::cout << "Showing opengl widget\n";
  openglwidget->show();
  std::cout << "Showed opengl widget\n";
  pausemenu->hide();
  paused = false;
  pausemenu->setContentsMargins(0, 0, 0, 0);

  std::cout << "Adding opengl widget\n";
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
  const quint8 offset = playerIndex * config.numberOfPiecesPerPlayer;
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
  quint8 chosenFigure = 255;
  switch (event->key()) {
  case Qt::Key_1:
    if (!possibleMoves[0]) {
      break;
    }
    chosenFigure = 0;
    break;
  case Qt::Key_2:
    if (!possibleMoves[1]) {
      break;
    }
    chosenFigure = 1;
    break;
  case Qt::Key_3:
    if (!possibleMoves[2]) {
      break;
    }
    chosenFigure = 2;
    break;
  case Qt::Key_4:
    if (!possibleMoves[3]) {
      break;
    }
    chosenFigure = 3;
    break;
  }

  if(chosenFigure == 255){
      return;
  }

  game->applyMove(playerIndex, chosenFigure, lastDieRoll);
  quint8 totalChosenFigure = map.getTotalIndex(chosenFigure, playerIndex);
  openglwidget->updatePosition(totalChosenFigure);
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
  std::cout << printLudoColor(color) << "'s turn\n";
  const quint32 seed = std::time(0);
  lastDieRoll = game->roll(seed);
  if (player->human) {
    game->humanMove = true;
    return;
  }

  const quint8 *positions = game->state.positions;
  const quint8 figureIndex = game->findMove(playerIndex, lastDieRoll);
  game->applyMove(playerIndex, figureIndex, lastDieRoll);
  const quint8 offset = playerIndex * config.numberOfPiecesPerPlayer;
  const quint8 totalFigureIndex = offset + figureIndex;

  openglwidget->updatePosition(totalFigureIndex);
  updateGameState();
}

} // namespace QtLudo
