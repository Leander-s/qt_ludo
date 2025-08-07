#include <Game.h>

namespace QtLudo {
Ludo::Ludo() {
        players = {
            HumanPlayer(LudoColor::red),
            AIPlayer(LudoColor::blue, oneManArmyPreset),
            AIPlayer(LudoColor::yellow, killerPreset),
            AIPlayer(LudoColor::green, youNeverWalkAlonePreset),
        };
        rng = QRandomGenerator::securelySeeded();
        map = std::make_shared<Map>();
        map->initializeMap();
        config = map->getMapConfig();
        state.positions = new quint8[config.numberOfPieces];
        memset((void *)state.positions, 0, config.numberOfPieces);
}

Ludo::~Ludo() { delete state.positions; }

void Ludo::start() {
        state.toMoveIndex = startingRoll();
        humanMove = players[state.toMoveIndex].human;
        LOG("Game started");
}

const quint8 Ludo::findMove(const quint8 playerIndex, const quint8 dieRoll) {
        if (players[playerIndex].human)
                return noMovesPossibleCode;

        const AIPlayer *bot = (AIPlayer *)&players[playerIndex];
        const quint8 pieceToMove =
            bot->decide(state.positions, dieRoll, config, playerIndex);
        return pieceToMove;
}

const quint8 Ludo::applyMove(const quint8 playerIndex,
                             const quint8 playerFigure, const quint8 dieRoll) {
        state.toMoveIndex = (state.toMoveIndex + 1) % config.numberOfPlayers;
        const bool noMovesPossible = playerFigure == noMovesPossibleCode;
        if (noMovesPossible) {
                return noMovesPossibleCode;
        }
        const bool invalidRoll = dieRoll > 6 || dieRoll == 0;
        if (invalidRoll) {
                return noMovesPossibleCode;
        }
        const quint8 offset = getFigure(playerIndex, 0);
        const quint8 figure = getFigure(playerIndex, playerFigure);
        const bool sixRolled = dieRoll == 6;
        const bool home = state.positions[figure] == 0;
        if (home) {
                if (!sixRolled) {
                        return noMovesPossibleCode;
                }
                state.positions[figure] = 1;
        } else {
                const bool tooFar =
                    state.positions[figure] + dieRoll >= config.lengthOfPath;
                if (tooFar) {
                        return noMovesPossibleCode;
                }
                state.positions[figure] += dieRoll;
        }
        // Are we beating another piece
        for (int otherFigure = 0; otherFigure < config.numberOfPieces;
             otherFigure++) {
                const bool ownPiece = mathMod<quint8>((otherFigure - offset),
                                                      config.numberOfPieces) <
                                      config.numberOfPiecesPerPlayer;
                if (ownPiece) {
                        continue;
                }
                const quint8 ownPosition = state.positions[figure];
                const quint8 otherPosition = state.positions[otherFigure];

                const quint8 ownTotalPosition =
                    map->getTotalIndex(figure, ownPosition);
                const quint8 otherTotalPosition =
                    map->getTotalIndex(otherFigure, otherPosition);

                if (ownTotalPosition == otherTotalPosition) {
                        state.positions[otherFigure] = 0;
                }
        }
        state.toMoveIndex = (state.toMoveIndex + 1) % config.numberOfPlayers;
        return figure;
}

const quint8 Ludo::getPosition(const quint8 figure) const {
        return state.positions[figure];
}

const quint8 Ludo::getToMove() const { return state.toMoveIndex; }

const quint8 Ludo::getFigure(const quint8 playerIndex,
                             const quint8 playerFigure) const {
        return playerIndex * config.numberOfPiecesPerPlayer + playerFigure;
}

const quint8 Ludo::startingRoll() {
        quint8 bestRoll = 0;
        int bestIndex = -1;

        for (int dieIndex = 0; dieIndex < config.numberOfPlayers; dieIndex++) {
                quint8 currentRoll = roll();
                if (currentRoll > bestRoll) {
                        bestIndex = dieIndex;
                        bestRoll = currentRoll;
                }
        }

        return bestIndex;
}

const quint8 Ludo::roll() {
        const quint32 random = rng.generate();
        return 1 + random % 6;
}
} // namespace QtLudo
