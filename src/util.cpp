#include <util.h>

namespace QtLudo {
void delay(int timeInSecs) {
        QTime returnTime = QTime::currentTime().addSecs(timeInSecs);
        while (QTime::currentTime() < returnTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
} // namespace QtLudo
