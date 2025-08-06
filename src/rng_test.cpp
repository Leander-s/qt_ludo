#include <Game.h>
#include <QtMath>
#include <LudoTesting.h>

using namespace QtLudo;
using namespace std;
int main() {
  QRandomGenerator rng = QRandomGenerator::securelySeeded();
  quint32 counts[6] = {0, 0, 0, 0, 0, 0};
  const int dieRolls = 100000;
  for (int i = 0; i < dieRolls; i++) {
    const quint32 random = rng.generate();
    quint32 number = 1 + random % 6;
    counts[number - 1]++;
  }

  int greatestDifference = 0;
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      if (i == j) {
        continue;
      }
      int difference = qAbs(counts[i] - counts[j]);
      if (difference > greatestDifference) {
        greatestDifference = difference;
      }
    }
  }

  float percentageDifference = (float)greatestDifference * 100 / dieRolls;
  testResults("RNG", QtLudo::less, percentageDifference, 1.0f);
}
