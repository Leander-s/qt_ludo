#include "Game.h"

namespace QtLudo {
Ludo::Ludo(const Map *_map) : map(_map), config(_map->getMapConfig()) {
  players = {HumanPlayer(LudoColor::red), OneManArmy(LudoColor::blue),
             YouNeverWalkAlone(LudoColor::green), Killer(LudoColor::yellow)};
  state.positions = new quint8[config.numberOfPieces];
  memset(state.positions, 0, config.numberOfPieces);
}

Ludo::~Ludo(){
    delete state.positions;
}

void Ludo::start() {
  state.toMoveIndex = startingRoll();
  humanMove = players[state.toMoveIndex].human;
}

const quint8 Ludo::findMove(const quint8 playerIndex, const quint8 dieRoll) {
  if (players[playerIndex].human)
    return 255;

  AIPlayer* bot = (AIPlayer*)&players[playerIndex];
  quint8 offset = playerIndex * config.numberOfPiecesPerPlayer;
  quint8 pieceToMove = bot->decide(state.positions, dieRoll, config, offset);
  quint8 figure = pieceToMove + offset;
  return figure;
}

void Ludo::applyMove(const quint8 playerIndex, const quint8 figure, const quint8 dieRoll) {
  bool noMovesPossible = figure == 255;
  if (noMovesPossible) {
    return;
  }
  bool home = state.positions[figure] == 0;
  if (home) {
    state.positions[figure] = 4;
  } else {
    state.positions[figure] += dieRoll;
  }
  quint8 offset = playerIndex * config.numberOfPiecesPerPlayer;
  // Are we beating another piece
  for (int i = 0; i < config.numberOfPieces; i++) {
    bool ownPiece = i - offset < config.numberOfPiecesPerPlayer;
    if (ownPiece) {
      continue;
    }
    if (state.positions[i] == state.positions[figure]) {
      state.positions[i] = 0;
    }
  }
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
