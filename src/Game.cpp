#include "Game.h"
#include "Players.h"
#include <chrono>

namespace QtLudo {
Ludo::Ludo(const Map *_map) : map(_map), config(_map->getMapConfig()) {
  players = {
      HumanPlayer(LudoColor::red),
      AIPlayer(LudoColor::blue, oneManArmyPreset),
      AIPlayer(LudoColor::yellow, killerPreset),
      AIPlayer(LudoColor::green, youNeverWalkAlonePreset),
  };
  state.positions = new quint8[config.numberOfPieces];
  memset((void *)state.positions, 0, config.numberOfPieces);
}

Ludo::~Ludo() { delete state.positions; }

void Ludo::start() {
  state.toMoveIndex = startingRoll();
  humanMove = players[state.toMoveIndex].human;
}

const QVector<bool> Ludo::getPossibleMoves(const quint8 playerIndex,
                                           const quint8 roll) const {
  bool sixRolled = roll == 6;
  QVector<bool> possibleMoves(config.numberOfPiecesPerPlayer, false);

  LOG("Rolled " << (int)roll);
  LOG("Possible moves are : ");
  const quint8 *playerPositions = state.positions + getFigure(playerIndex, 0);
  for (int i = 0; i < config.numberOfPiecesPerPlayer; i++) {
    // Check if there is enough space to move my piece
    bool notTooFar = (config.lengthOfPath - playerPositions[i]) >= roll;
    if (!notTooFar) {
      continue;
    }

    // Check if I am in home and need to roll a six to move
    bool inHome = playerPositions[i] == 0;
    LOG((int)playerPositions[i]);
    LOG(i << " is home: " << inHome);
    quint8 futurePos;
    if (inHome) {
      if (!sixRolled) {
        continue;
      }
      futurePos = 1;
    } else {
      futurePos = playerPositions[i] + roll;
    }

    // We are here so this move is possible
    possibleMoves[i] = true;
    LOG(i);
  }
  return possibleMoves;
}

const quint8 Ludo::findMove(const quint8 playerIndex, const quint8 dieRoll) {
  if (players[playerIndex].human)
    return 255;

  const AIPlayer *bot = (AIPlayer *)&players[playerIndex];
  const quint8 offset = getFigure(playerIndex, 0);
  const quint8 pieceToMove =
      bot->decide(state.positions, dieRoll, config, offset);
  return pieceToMove;
}

const quint8 Ludo::applyMove(const quint8 playerIndex,
                             const quint8 playerFigure, const quint8 dieRoll) {
  const bool noMovesPossible = playerFigure == 255;
  if (noMovesPossible) {
    state.toMoveIndex = (state.toMoveIndex + 1) % config.numberOfPlayers;
    LOG("No possible moves...");
    return 255;
  }
  const quint8 offset = getFigure(playerIndex, 0);
  const quint8 figure = getFigure(playerIndex, playerFigure);
  const bool home = state.positions[figure] == 0;
  if (home) {
    state.positions[figure] = 1;
  } else {
    state.positions[figure] += dieRoll;
  }
  // Are we beating another piece
  for (int otherFigure = 0; otherFigure < config.numberOfPieces;
       otherFigure++) {
    const bool ownPiece = otherFigure - offset < config.numberOfPiecesPerPlayer;
    if (ownPiece) {
      continue;
    }
    if (state.positions[otherFigure] == state.positions[figure]) {
      state.positions[otherFigure] = 0;
    }
  }
  state.toMoveIndex = (state.toMoveIndex + 1) % config.numberOfPlayers;
  return figure;
}

const quint8 Ludo::getPosition(const quint8 figure) const {
  return state.positions[figure];
}

const quint8 Ludo::getToMove() const { return state.toMoveIndex; }

const quint8 Ludo::getFigure(const quint8 playerIndex,
                             const quint8 playerFigure) const {
  return playerIndex * config.numberOfPiecesPerPlayer + playerFigure;
}

const quint8 Ludo::startingRoll() {
  quint8 bestRoll = 0;
  int bestIndex = -1;

  for (int dieIndex = 0; dieIndex < config.numberOfPlayers; dieIndex++) {
    quint8 currentRoll = roll();
    if (currentRoll > bestRoll) {
      bestIndex = dieIndex;
      bestRoll = currentRoll;
    }
  }

  return bestIndex;
}

const quint8 Ludo::roll() {
  using namespace std::chrono;
  quint32 seed =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch())
          .count();
  const int random = rand_r(&seed);
  return 1 + random % 6;
}
} // namespace QtLudo
