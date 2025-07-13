#pragma once
#include <QFile>
#include <iostream>
#include "defaultMap.h"

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
  Map(QString path = "default");
  ~Map();
  QVector2D getCoords(quint8 figure, quint8 index);
  quint8 getTotalIndex(quint8 figure, quint8 index);

private:
  QVector<QVector2D> posCoordMap;
  QVector<QVector<quint8>> paths;
  MapConfig config;
  bool saveMap(QString path);
  bool loadMap(QString path);
};
} // namespace QtLudo
