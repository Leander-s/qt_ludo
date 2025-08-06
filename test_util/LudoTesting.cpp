#include <LudoTesting.h>

namespace QtLudo {
void printResult(const QString testName, const bool result,
                 const QString message) {
        if (result) {
                std::cout << qPrintable(greenText) << qPrintable(testName)
                          << " succeeded!" << qPrintable(textColorReset)
                          << std::endl;
                return;
        }

        std::cout << qPrintable(redText) << qPrintable(testName) << " did not succeed!"
                  << qPrintable(textColorReset) << std::endl;

        if (message.data()) {
                std::cout << qPrintable(message) << std::endl;
        }
}
} // namespace QtLudo
