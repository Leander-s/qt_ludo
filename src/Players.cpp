#include "Players.h"

namespace QtLudo {
std::vector<bool> Player::getPossibleMoves(uint8_t *playerPositions,
                                             uint8_t roll, MapConfig config,
                                             uint8_t playerOffset) {
  bool sixRolled = roll == 6;
  std::vector<bool> possibleMoves(config.numberOfPiecesPerPlayer, false);

  for (int i = 0; i < config.numberOfPiecesPerPlayer; i++) {
    // Check if I there is enough space to move my piece
    bool notTooFar = (config.lengthOfPath - playerPositions[i]) >= roll;
    if (!notTooFar) {
      break;
    }

    // Check if I am in home and need to roll a six to move
    bool inHome = playerPositions[i] < 4;
    uint8_t futurePos;
    if (inHome) {
      if (!sixRolled) {
        break;
      }
      futurePos = 4;
    } else {
      futurePos = playerPositions[i] + roll;
    }

    // We are here so this move is possible
    possibleMoves[i] = true;
  }
  return possibleMoves;
}

uint8_t OneManArmy::decide(uint8_t *positions, uint8_t roll, MapConfig config,
                           uint8_t playerOffset) {
  std::vector<bool> possibleMoves =
      getPossibleMoves(positions + playerOffset, roll, config, playerOffset);
  uint8_t *playerPositions = positions + playerOffset;
  int bestScore = 0x80000000; // minimum integer value
  uint8_t bestScoreIndex = 255;
  for (int i = 0; i < config.numberOfPiecesPerPlayer; i++) {
    if (!possibleMoves[i]) {
      continue;
    }
    int score = playerPositions[i];
    if (score > bestScore) {
      bestScore = score;
      bestScoreIndex = i;
    }
  }
  return bestScoreIndex;
}

uint8_t YouNeverWalkAlone::decide(uint8_t *positions, uint8_t roll,
                                  MapConfig config, uint8_t playerOffset) {
  std::vector<bool> possibleMoves =
      getPossibleMoves(positions + playerOffset, roll, config, playerOffset);
  uint8_t *playerPositions = positions + playerOffset;
  int bestScore = 0x80000000; // minimum integer value
  uint8_t bestScoreIndex = 255;
  for (int i = 0; i < config.numberOfPiecesPerPlayer; i++) {
    if (!possibleMoves[i]) {
      continue;
    }
    int score = config.lengthOfPath - playerPositions[i];
    if (score > bestScore) {
      bestScore = score;
      bestScoreIndex = i;
    }
    bool otherPieceOnSquare = false;
    for (int j = 0; j < config.numberOfPieces; j++) {
      if (j >= playerOffset && j < playerOffset + 4) {
        continue;
      }
      int nextPos = playerPositions[i] + roll;
      if (positions[j] == nextPos) {
        if (otherPieceOnSquare) {
          // This means there is a block ahead!!
          score -= config.lengthOfPath;
        } else {
          otherPieceOnSquare = true;
          score += 10;
        }
      }
    }
  }
  return bestScoreIndex;
}
uint8_t Pacifist::decide(uint8_t *positions, uint8_t roll, MapConfig config,
                         uint8_t playerOffset) {
  std::vector<bool> possibleMoves =
      getPossibleMoves(positions + playerOffset, roll, config, playerOffset);
  uint8_t *playerPositions = positions + playerOffset;
  int bestScore = 0x80000000; // minimum integer value
  uint8_t bestScoreIndex = 255;
  for (int i = 0; i < config.numberOfPiecesPerPlayer; i++) {
    if (!possibleMoves[i]) {
      continue;
    }
    int score = playerPositions[i];
    for (int j = 0; j < config.numberOfPieces; j++) {
      if (j >= playerOffset && j < playerOffset + 4) {
        continue;
      }
      int nextPos = playerPositions[i] + roll;
      if (positions[j] == nextPos) {
        score -= config.lengthOfPath;
      }
    }
    if (score > bestScore) {
      bestScore = score;
      bestScoreIndex = i;
    }
  }
  return bestScoreIndex;
}

uint8_t Killer::decide(uint8_t *positions, uint8_t roll, MapConfig config,
                       uint8_t playerOffset) {
  std::vector<bool> possibleMoves =
      getPossibleMoves(positions + playerOffset, roll, config, playerOffset);
  uint8_t *playerPositions = positions + playerOffset;
  int bestScore = 0x80000000; // minimum integer value
  uint8_t bestScoreIndex = 255;
  for (int i = 0; i < config.numberOfPiecesPerPlayer; i++) {
    if (!possibleMoves[i]) {
      continue;
    }
    int score = playerPositions[i];
    bool otherPieceTargeted = false;
    for (int j = 0; j < config.numberOfPieces; j++) {
      if (j >= playerOffset && j < playerOffset + 4) {
        continue;
      }
      int nextPos = playerPositions[i] + roll;
      if (positions[j] == nextPos) {
        if (otherPieceTargeted) {
          // This means there is a block ahead!!
          score -= 2 * config.lengthOfPath;
        } else {
          otherPieceTargeted = true;
          score += config.lengthOfPath;
        }
      }
    }
    if (score > bestScore) {
      bestScore = score;
      bestScoreIndex = i;
    }
  }
  return bestScoreIndex;
}
} // namespace QtLudo
