#include <LudoTesting.h>

namespace QtLudo {
template <typename Comp, typename T>
void testEquals(const QString testName, const Comp Op, const T &result,
                const T &expectedResult) {
        const bool success = Op(result, expectedResult);

        if (success) {
                std::cout << greenText.data() << testName.data()
                          << " succeeded!" << textColorReset.data()
                          << std::endl;
                return;
        }

        QString op;

        switch (Op) {
        case less:
                op = "less than ";
                break;
        case greater:
                op = "greater than ";
                break;
        case equal:
                op = "";
                break;
        }

        std::cout << redText.data() << testName.data() << " did not succeed!"
                  << textColorReset.data() << std::endl;
        std::cout << "Expected " << op.data() << expectedResult << ", got "
                  << result << std::endl;
}

void printResult(const QString testName, const bool result,
                 const QString message) {
        if (result) {
                std::cout << greenText.data() << testName.data()
                          << " succeeded!" << textColorReset.data()
                          << std::endl;
                return;
        }

        std::cout << redText.data() << testName.data() << " did not succeed!"
                  << textColorReset.data() << std::endl;

        if (message.data()) {
                std::cout << message.data() << std::endl;
        }
}
} // namespace QtLudo
