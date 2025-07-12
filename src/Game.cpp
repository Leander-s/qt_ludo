#include "Game.h"

namespace QtLudo {
Ludo::Ludo(MapConfig newConfig) : config(newConfig) {
  for (int i; i < config.numberOfPieces; i++) {
    state->positions[i] = i % config.numberOfPiecesPerPlayer;
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

uint8_t Ludo::getPosition(LudoColor color, int position){
    uint8_t offset = getOffset(color);
    return offset + position;
}

void Ludo::start() { 
    state->toMove = startingRoll(); 
    humanMove = players[getPlayer(state->toMove)].human;
}

std::array<uint8_t, 2> Ludo::update() {
  Player *player = &players[getPlayer(state->toMove)];
  uint32_t seed = clock();
  uint8_t dieRoll = roll(seed);
  uint8_t *positions = state->positions;
  if (!player->human) {
    AIPlayer *player = player;
    uint8_t offset = getOffset(state->toMove);
    uint8_t pieceToMove = player->decide(state->positions, dieRoll, config,
                                         offset);
    uint8_t totalPiece = getPosition(state->toMove, pieceToMove);
    state->positions[totalPiece] += dieRoll;
    // Are we beating another piece
    for(int i = 0; i < config.numberOfPieces; i++){
        bool ownPiece = i - offset < config.numberOfPiecesPerPlayer;
        if(ownPiece){
            continue;
        }
        if(positions[i] == positions[totalPiece]){
            positions[i] = i%config.numberOfPiecesPerPlayer;
        }
    }
    state->toMove++;
    humanMove = players[getPlayer(state->toMove)].human;
    return {pieceToMove, dieRoll};
  }
  return {255, dieRoll};
}

LudoColor Ludo::startingRoll() {
  uint32_t seed = clock();
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

uint8_t Ludo::roll(uint32_t seed) { return 1 + rand_r(&seed) % 6; }
} // namespace QtLudo
