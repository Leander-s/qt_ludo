#include "Game.h"

namespace QtLudo {
Ludo::Ludo(const Map *_map) : map(_map), config(_map->getMapConfig()) {
  players = {HumanPlayer(LudoColor::red), OneManArmy(LudoColor::blue),
             YouNeverWalkAlone(LudoColor::green), Killer(LudoColor::yellow)};
  state.positions = new quint8[config.numberOfPieces];
  memset(state.positions, 0, config.numberOfPieces);
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
    state->positions[totalPiece] = 4;
  } else {
    state->positions[totalPiece] += dieRoll;
  }
  quint8 offset = getOffset(currentColor);
  quint8 *positions = state->positions;
  // Are we beating another piece
  for (int i = 0; i < config.numberOfPieces; i++) {
    bool ownPiece = i - offset < config.numberOfPiecesPerPlayer;
    if (ownPiece) {
      continue;
    }
    if (positions[i] == positions[totalPiece]) {
      positions[i] = i % config.numberOfPiecesPerPlayer;
    }
  }
}

LudoColor Ludo::startingRoll() {
  uint32_t seed = std::time(0);
  quint8 bestRoll = 0;
  int bestIndex = -1;
  const int redIndex = 0;
  const int blueIndex = 1;
  const int greenIndex = 2;
  const int yellowIndex = 3;

  for (int dieIndex = 0; dieIndex < config.numberOfPlayers; dieIndex++) {
    quint8 currentRoll = roll(seed++);
    if (currentRoll > bestRoll) {
      bestIndex = dieIndex;
    }
  }

  switch (bestIndex) {
  case redIndex:
    return LudoColor::red;
  case blueIndex:
    return LudoColor::blue;
  case greenIndex:
    return LudoColor::green;
  case yellowIndex:
    return LudoColor::yellow;
  default:
    std::cout << "Something went wrong in startingRoll\n";
    return LudoColor::red;
  }
}

quint8 Ludo::roll(uint32_t seed) {
  int random = rand_r(&seed);
  return 1 + random % 6;
}
} // namespace QtLudo
