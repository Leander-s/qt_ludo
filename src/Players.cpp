#include "Players.h"

namespace QtLudo {
const std::vector<bool>
Player::getPossibleMoves(const quint8 *playerPositions, const quint8 roll,
                         const MapConfig &config) const {
  bool sixRolled = roll == 6;
  std::vector<bool> possibleMoves(config.numberOfPiecesPerPlayer, false);

  for (int i = 0; i < config.numberOfPiecesPerPlayer; i++) {
    // Check if there is enough space to move my piece
    bool notTooFar = (config.lengthOfPath - playerPositions[i]) >= roll;
    if (!notTooFar) {
      break;
    }

    // Check if I am in home and need to roll a six to move
    bool inHome = playerPositions[i] < 4;
    quint8 futurePos;
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

Player::Player(const LudoColor _color) : color(_color) {};

HumanPlayer::HumanPlayer(const LudoColor _color) : Player(_color) {
  human = true;
};

AIPlayer::AIPlayer(const LudoColor _color) : Player(_color) { human = false; };

const quint8 OneManArmy::decide(const quint8 *positions, const quint8 roll,
                                const MapConfig &config,
                                const quint8 playerOffset) const {
  const std::vector<bool> possibleMoves =
      getPossibleMoves(positions + playerOffset, roll, config);
  const quint8 *playerPositions = positions + playerOffset;
  int bestScore = 0x80000000; // minimum integer value
  quint8 bestScoreIndex = 255;
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

const quint8 YouNeverWalkAlone::decide(const quint8 *positions,
                                       const quint8 roll,
                                       const MapConfig &config,
                                       const quint8 playerOffset) const {
  const std::vector<bool> possibleMoves =
      getPossibleMoves(positions + playerOffset, roll, config);
  const quint8 *playerPositions = positions + playerOffset;
  int bestScore = 0x80000000; // minimum integer value
  quint8 bestScoreIndex = 255;
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
const quint8 Pacifist::decide(const quint8 *positions, const quint8 roll,
                              const MapConfig &config,
                              const quint8 playerOffset) const {
  const std::vector<bool> possibleMoves =
      getPossibleMoves(positions + playerOffset, roll, config);
  const quint8 *playerPositions = positions + playerOffset;
  int bestScore = 0x80000000; // minimum integer value
  quint8 bestScoreIndex = 255;
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

const quint8 Killer::decide(const quint8 *positions, const quint8 roll,
                            const MapConfig &config,
                            const quint8 playerOffset) const {
  std::vector<bool> possibleMoves =
      getPossibleMoves(positions + playerOffset, roll, config);
  const quint8 *playerPositions = positions + playerOffset;
  int bestScore = 0x80000000; // minimum integer value
  quint8 bestScoreIndex = 255;
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
