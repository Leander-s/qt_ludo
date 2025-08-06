#include <Game.h>
#include <LudoTesting.h>
#include <QString>

using namespace QtLudo;
using namespace std;
int main() {
        Map testMap;
        testMap.initializeMap();
        Ludo testGame(&testMap);
        const quint8 pathLength = testGame.config.lengthOfPath;
        const quint8 lastPos = pathLength - 1;
        const quint8 almostEnd = pathLength - 2;
        int offset = 0;
        for (int i = 0; i < 4; i++) {
                offset = i * 4;
                testGame.state.positions[0 + offset] = almostEnd;
                testGame.state.positions[1 + offset] = 0;
                testGame.state.positions[2 + offset] = 12;
                testGame.state.positions[3 + offset] = 1;
        }

        quint8 movedFig;

        quint8 playerFig1, playerFig2, playerFig3, playerFig4, nextPlayer;
        for (int i = 0; i < 4; i++) {
                std::cout << "Testing for player " << i << std::endl;
                playerFig1 = testGame.getFigure(i, 0);
                playerFig2 = testGame.getFigure(i, 1);
                playerFig3 = testGame.getFigure(i, 2);
                playerFig4 = testGame.getFigure(i, 3);

                testGame.state.positions[playerFig4] = 1;

                nextPlayer = (i + 1) % 4;

                movedFig = testGame.applyMove(i, 0, 2);
                testResults("Too far", QtLudo::equal, movedFig, quint8{255});
                testResults("Too far actual position", QtLudo::equal,
                            testGame.state.positions[playerFig1], almostEnd);
                movedFig = testGame.applyMove(i, 0, 1);
                testResults("Not too far", QtLudo::equal, movedFig,
                            quint8{playerFig1});
                testResults("Not too far actual position", QtLudo::equal,
                            testGame.state.positions[playerFig1], lastPos);
                movedFig = testGame.applyMove(i, 1, 4);
                testResults("No six rolled at start", QtLudo::equal, movedFig,
                            quint8{255});
                testResults("No six rolled actual position", QtLudo::equal,
                            testGame.state.positions[playerFig2], quint8{0});
                movedFig = testGame.applyMove(i, 1, 6);
                testResults("Six rolled at start", QtLudo::equal, movedFig,
                            playerFig2);
                testResults("Six rolled actual position", QtLudo::equal,
                            testGame.state.positions[playerFig2], quint8{1});
                quint8 otherFigure = testGame.getFigure(nextPlayer, 3);
                testGame.state.positions[otherFigure] = 1;
                movedFig = testGame.applyMove(i, 2, 3);
                testResults("3 rolled at 3", QtLudo::equal, movedFig,
                            playerFig3);
                testResults("3 rolled at 3 actual position", QtLudo::equal,
                            testGame.state.positions[playerFig3], quint8{15});
                testResults("Beat piece", QtLudo::equal,
                            testGame.state.positions[otherFigure], quint8{0});

                movedFig = testGame.applyMove(i, 3, 7);
                testResults("7 rolled", QtLudo::equal, movedFig, quint8{255});
                testResults("7 rolled actual position", QtLudo::equal,
                            testGame.state.positions[playerFig4], quint8{1});
        }
        return 0;
}
