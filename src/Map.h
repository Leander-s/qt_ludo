#pragma once

// Mine
#include <defaultMap.h>

// Qt
#include <QFile>

namespace QtLudo {
constexpr char fType[4] = {'P', 'P', '\r', '\n'};
constexpr quint32 version = 1;

struct MapConfig {
  quint8 numberOfPlayers;
  quint8 numberOfPiecesPerPlayer;
  quint8 numberOfPieces;
  quint8 lengthOfPath;
};

class Map {
public:
  Map();
  void initializeMap(const QString path = "default");
  const QVector2D getCoords(const quint8 figure, const quint8 position) const;
  const quint8 getTotalIndex(const quint8 figure, const quint8 position) const;
  const MapConfig getMapConfig() const;

private:
  QVector<QVector2D> posCoordMap;
  QVector<QVector<quint8>> paths;
  MapConfig config;
  bool initialized;
  bool saveMap(const QString path);
  bool loadMap(const QString path);
};
} // namespace QtLudo
