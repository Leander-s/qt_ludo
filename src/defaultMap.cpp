#include "defaultMap.h"

namespace QtLudo {
QVector<QVector<quint8>> genDefaultPaths() {
  QVector<quint8> Starts = {0, 14, 28, 42};

  QVector<quint8> Yards = {56, 60, 64, 68};

  QVector<quint8> Homes = {72, 78, 84, 90};

  const qint8 defaultNumberOfPlayers = 4;
  const qint8 defaultNumberOfPiecesPerPlayer = 4;
  const qint8 defaultPathLength = 63;

  QVector<QVector<quint8>> paths;
  paths.reserve(defaultNumberOfPlayers * defaultNumberOfPiecesPerPlayer);

  for (int i = 0; i < defaultNumberOfPlayers; i++) {
    for (int j = 0; j < defaultNumberOfPiecesPerPlayer; j++) {
      int pieceIndex = i * defaultNumberOfPiecesPerPlayer + j;
      paths[pieceIndex].push_back(Yards[i] + j);
      // -6 for home spaces and -1 for yard space
      for (int k = 0; k < defaultPathLength - 6 - 1; k++) {
        paths[pieceIndex].push_back((Starts[i] + k) % 56);
      }
      for (int k = 0; k < 6; k++) {
        paths[pieceIndex].push_back(Homes[i] + k);
      }
    }
  }
  return paths;
}
} // namespace QtLudo
