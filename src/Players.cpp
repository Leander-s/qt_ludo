#include "Players.h"

namespace QtLudo {
const QVector<bool> Player::getPossibleMoves(const quint8 *positions,
                                             const quint8 playerOffset,
                                             const quint8 roll,
                                             const MapConfig &config) const {
  bool sixRolled = roll == 6;
  QVector<bool> possibleMoves(config.numberOfPiecesPerPlayer, false);

  LOG("Rolled " << (int)roll);
  LOG("Possible moves are : ");
  for (int i = 0; i < config.numberOfPiecesPerPlayer; i++) {
    // Check if there is enough space to move my piece
    int playerPosition = i + playerOffset;
    bool notTooFar = (config.lengthOfPath - positions[playerPosition]) >= roll;
    std::cout << "Game state : ";
    for (int i = 0; i < config.numberOfPieces; i++) {
      std::cout << (int)positions[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "Player position: " << positions[playerPosition] << std::endl;
    if (!notTooFar) {
      continue;
    }

    // Check if I am in home and need to roll a six to move
    bool inHome = positions[playerPosition] == 0;
    LOG((int)positions[playerPosition]);
    LOG(i << " is home: " << inHome);
    quint8 futurePos;
    if (inHome) {
      if (!sixRolled) {
        continue;
      }
      futurePos = 1;
    } else {
      futurePos = positions[playerPosition] + roll;
    }

    // We are here so this move is possible
    possibleMoves[i] = true;
    LOG(i);
  }
  return possibleMoves;
}

void Player::sortPositions(const quint8 *playerPositions,
                           quint8 *sortedPositions,
                           const MapConfig &config) const {
  // create temp buffer for positions
  quint8 tempPositions[config.numberOfPiecesPerPlayer];
  memcpy((void *)tempPositions, (void *)playerPositions,
         config.numberOfPiecesPerPlayer);

  // assign indices for sortedPositions
  for (int i = 0; i < config.numberOfPiecesPerPlayer; i++) {
    sortedPositions[i] = i;
  }

  // sort sortedPositions
  for (int i = 0; i < config.numberOfPiecesPerPlayer; i++) {
    for (int j = i + 1; j < config.numberOfPiecesPerPlayer; j++) {
      if (tempPositions[i] < tempPositions[j]) {
        // Swap using xor, saw it in a yt short :)
        sortedPositions[i] = sortedPositions[i] ^ sortedPositions[j];
        sortedPositions[j] = sortedPositions[i] ^ sortedPositions[j];
        sortedPositions[i] = sortedPositions[i] ^ sortedPositions[j];

        tempPositions[i] = tempPositions[i] ^ tempPositions[j];
        tempPositions[j] = tempPositions[i] ^ tempPositions[j];
        tempPositions[i] = tempPositions[i] ^ tempPositions[j];
      }
    }
  }
}

Player::Player(const LudoColor _color) : color(_color) {};

HumanPlayer::HumanPlayer(const LudoColor _color) : Player(_color) {
  human = true;
};

AIPlayer::AIPlayer(const LudoColor _color, const aiParameters &_params)
    : Player(_color), params(_params) {
  human = false;
};

const int AIPlayer::calculateScore(const quint8 *positions,
                                   const quint8 playerPosition,
                                   const quint8 sortedPosition,
                                   const quint8 roll, const MapConfig &config,
                                   const quint8 playerOffset) const {
  int score = (int)(params.preferredFigurePosition == sortedPosition) *
              params.figurePositionBias;

  bool otherPieceOnSquare = false;
  for (int j = 0; j < config.numberOfPieces; j++) {
    bool ownPiece = false;
    if (j >= playerOffset && j < playerOffset + 4) {
      ownPiece = true;
    }
    quint8 nextPos = playerPosition + roll;
    if (positions[j] == nextPos) {
      if (ownPiece) {
        score += params.defenseBias;
        continue;
      }
      if (!otherPieceOnSquare) {
        otherPieceOnSquare = true;
        score += params.aggressionBias;
        continue;
      }
      // This means there is a block ahead!!
      // subtract aggressionBias again and then subtract willToLive param
      score -= params.aggressionBias;
      score -= params.willToLive;
    }
  }
  return score;
}

const quint8 AIPlayer::decide(const quint8 *positions, const quint8 roll,
                              const MapConfig &config,
                              const quint8 playerIndex) const {
  LOG("Rolled a " << (int)roll);
  const quint8 playerOffset = playerIndex * config.numberOfPiecesPerPlayer;
  const QVector<bool> possibleMoves =
      getPossibleMoves(positions, playerOffset, roll, config);
  int bestScore = 0x80000000; // minimum integer value
  quint8 bestScoreIndex = 255;

  const quint8 *playerPositions = positions + playerOffset;

  // get sorted positions for params.preferredFigurePosition
  quint8 sortedPositions[config.numberOfPiecesPerPlayer];
  sortPositions(playerPositions, sortedPositions, config);

  for (int i = 0; i < config.numberOfPiecesPerPlayer; i++) {
    if (!possibleMoves[i]) {
      continue;
    }
    int score = calculateScore(positions, playerPositions[i],
                               sortedPositions[i], roll, config, playerOffset);
    if (score > bestScore) {
      bestScore = score;
      bestScoreIndex = i;
    }
  }
  return bestScoreIndex;
}
} // namespace QtLudo
