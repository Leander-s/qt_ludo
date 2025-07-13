#include "Map.h"

namespace QtLudo {
Map::Map(QString path) {
  if (path == "default") {
      config.lengthOfPath = 63;
      config.numberOfPlayers = 4;
      config.numberOfPiecesPerPlayer = 4;
      config.numberOfPieces = 16;

      posCoordMap = positionMappings;
      paths = genDefaultPaths();
      if(!saveMap(QString("defaultMap.map"))){
          std::cout << "Saving map failed\n";
      }
  }
}

QVector2D Map::getCoords(quint8 figure, quint8 index){
    return posCoordMap[getTotalIndex(figure, index)];
}

quint8 Map::getTotalIndex(quint8 figure, quint8 index){
    return paths[figure][index];
}

bool Map::saveMap(QString path) {
  QFile file(path);
  if (!file.open(QIODevice::WriteOnly)) {
    return false;
  }

  QDataStream out(&file);
  out.setVersion(QDataStream::Qt_6_5);

  out.writeRawData(fType, 4);
  out << version;

  out << config.lengthOfPath;
  out << config.numberOfPlayers;
  out << config.numberOfPiecesPerPlayer;
  out << posCoordMap;
  out << paths;

  file.commitTransaction();
  return true;
}

bool Map::loadMap(QString path) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    return false;
  }

  QDataStream in(&file);
  in.setVersion(QDataStream::Qt_6_5);

  char header[4];
  if (in.readRawData(header, 4) != 4 || memcmp(header, fType, 4) != 0) {
    return false;
  }

  quint32 ver;
  in >> ver;
  if (ver != version)
    return false;

  in >> config.lengthOfPath;
  in >> config.numberOfPlayers;
  in >> config.numberOfPiecesPerPlayer;
  in >> posCoordMap;
  in >> paths;

  config.numberOfPieces =
      config.numberOfPlayers * config.numberOfPiecesPerPlayer;

  return in.status() == QDataStream::Ok;
}
} // namespace QtLudo
