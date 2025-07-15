#include "Game.h"
#include "Players.h"

namespace QtLudo {
Ludo::Ludo(const Map *_map) : map(_map), config(_map->getMapConfig()) {
  players = {HumanPlayer(LudoColor::red),
             AIPlayer(LudoColor::blue, oneManArmyPreset),
             AIPlayer(LudoColor::green, youNeverWalkAlonePreset),
             AIPlayer(LudoColor::yellow, killerPreset)};
  state.positions = new quint8[config.numberOfPieces];
  memset(state.positions, 0, config.numberOfPieces);
}

Ludo::~Ludo() { delete state.positions; }

void Ludo::start() {
  state.toMoveIndex = startingRoll();
  humanMove = players[state.toMoveIndex].human;
}

const quint8 Ludo::findMove(const quint8 playerIndex, const quint8 dieRoll) {
  if (players[playerIndex].human)
    return 255;

  const AIPlayer *bot = (AIPlayer *)&players[playerIndex];
  const quint8 offset = getFigure(playerIndex, 0);
  const quint8 pieceToMove =
      bot->decide(state.positions + offset, dieRoll, config, offset);
  LOG("Decided on piece : " << (int)pieceToMove);
  return pieceToMove;
}

void Ludo::applyMove(const quint8 playerIndex, const quint8 playerFigure,
                     const quint8 dieRoll) {
  const bool noMovesPossible = playerFigure == 255;
  if (noMovesPossible) {
    state.toMoveIndex = (state.toMoveIndex + 1) % config.numberOfPlayers;
    LOG("No possible moves...");
    return;
  }
  const bool home = state.positions[playerFigure] == 0;
  if (home) {
    state.positions[playerFigure] = 4;
  } else {
    state.positions[playerFigure] += dieRoll;
  }
  const quint8 offset = getFigure(playerIndex, 0);
  const quint8 figure = getFigure(playerIndex, playerFigure);
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
}

const quint8 Ludo::getFigure(const quint8 playerIndex,
                             const quint8 playerFigure) {
  return playerIndex * config.numberOfPiecesPerPlayer + playerFigure;
}

const quint8 Ludo::startingRoll() {
  quint32 seed = std::time(0);
  quint8 bestRoll = 0;
  int bestIndex = -1;

  for (int dieIndex = 0; dieIndex < config.numberOfPlayers; dieIndex++) {
    quint8 currentRoll = roll(seed++);
    if (currentRoll > bestRoll) {
      bestIndex = dieIndex;
      bestRoll = currentRoll;
    }
  }

  return bestIndex;
}

const quint8 Ludo::roll(quint32 seed) {
  const int random = rand_r(&seed);
  return 1 + random % 6;
}
} // namespace QtLudo
