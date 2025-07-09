#include "Game.h"

namespace QtLudo {
Ludo::Ludo() {
  for (int i; i < NUMBER_OF_PIECES; i++) {
    state->positions[i] = i % NUMBER_OF_PIECES_PER_PLAYER;
  }
}

void Ludo::start() {
}

LudoColor Ludo::startingRoll(){
    uint32_t seed = clock();
    uint8_t redDie = roll(seed++);
    uint8_t blueDie = roll(seed++);
    uint8_t greenDie = roll(seed++);
    uint8_t yellowDie = roll(seed);

    LudoColor startingColor = LudoColor::red;
    uint8_t bestRoll = redDie;
    if(blueDie > redDie){
    }
}

uint8_t Ludo::roll(uint32_t seed) {
    return 1 + rand_r(&seed)%6;
}
} // namespace QtLudo
