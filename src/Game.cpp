#include "Game.h"

namespace QtLudo {
Ludo::Ludo(MapConfig newConfig) : config(newConfig) {
  state = new GameState;
  players = {new HumanPlayer(LudoColor::red), new OneManArmy(LudoColor::blue),
             new YouNeverWalkAlone(LudoColor::green),
             new Killer(LudoColor::yellow)};
  state->positions = new uint8_t[config.numberOfPieces];
  for (int i; i < config.numberOfPieces; i++) {
    state->positions[i] = i % config.numberOfPiecesPerPlayer;
  }
}

Ludo::~Ludo() {
  delete state->positions;
  delete state;
  for (Player *player : players) {
    delete player;
  }
}

int Ludo::getPlayer(LudoColor color) {
  switch (color) {
  case LudoColor::red:
    return 0;
  case LudoColor::blue:
    return 1;
  case LudoColor::yellow:
    return 3;
  case LudoColor::green:
    return 2;
  }
  std::cout << "Something went really wrong in QtLudo::Ludo::getPlayer\n";
  return -1;
}

uint8_t Ludo::getPosition(LudoColor color, int position) {
  uint8_t offset = getOffset(color);
  return offset + position;
}

void Ludo::start() {
  state->toMove = startingRoll();
  humanMove = players[getPlayer(state->toMove)]->human;
}

uint8_t Ludo::findMove(Player *player, uint8_t dieRoll) {
  if (player->human)
    return 255;
  AIPlayer *bot = (AIPlayer *)player;
  uint8_t offset = getOffset(state->toMove);
  uint8_t pieceToMove = bot->decide(state->positions, dieRoll, config, offset);
  uint8_t totalPiece = getPosition(state->toMove, pieceToMove);
  return totalPiece;
}

void Ludo::applyMove(uint8_t totalPiece, uint8_t dieRoll) {
  bool noMovesPossible = totalPiece == 255;
  LudoColor currentColor = state->toMove++;
  if (noMovesPossible) {
    return;
  }
  bool home = state->positions[totalPiece] < 4;
  if (home) {
    state->positions[totalPiece] = 4;
  } else {
    state->positions[totalPiece] += dieRoll;
  }
  uint8_t offset = getOffset(currentColor);
  uint8_t *positions = state->positions;
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
  uint8_t bestRoll = 0;
  int bestIndex = -1;
  const int redIndex = 0;
  const int blueIndex = 1;
  const int greenIndex = 2;
  const int yellowIndex = 3;

  for (int dieIndex = 0; dieIndex < config.numberOfPlayers; dieIndex++) {
    uint8_t currentRoll = roll(seed++);
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

uint8_t Ludo::roll(uint32_t seed) {
  int random = rand_r(&seed);
  return 1 + random % 6;
}
} // namespace QtLudo
