#pragma once
#include <QString>
#include <iostream>

namespace QtLudo {
constexpr auto less = std::less<>{};
constexpr auto greater = std::greater<>{};
constexpr auto equal = std::equal_to<>{};

const QString greenText = "\033[1;32m";
const QString redText = "\033[1;31m";
const QString textColorReset = "\033[0m";

template<typename Comp>
constexpr const char* op_string(){
    if constexpr(std::is_same_v<Comp, std::less<>>) return "less than ";
    else if constexpr(std::is_same_v<Comp, std::greater<>>) return "greater than ";
    else if constexpr(std::is_same_v<Comp, std::equal_to<>>) return "equal to ";
    else return "";
}

template <typename Comp, typename T>
void testResults(const QString testName, Comp Op, T &result,
                 const T &expectedResult) {
        const bool success = Op(result, expectedResult);

        if (success) {
                std::cout << qPrintable(greenText) << qPrintable(testName)
                          << " succeeded!" << qPrintable(textColorReset)
                          << std::endl;
                return;
        }

        QString op(op_string<Comp>());

        std::cout << qPrintable(redText) << qPrintable(testName) << " did not succeed!"
                  << qPrintable(textColorReset) << std::endl;
        std::cout << "Expected " << qPrintable(op) << (int)expectedResult << ", got "
                  << (int)result << std::endl;
}

void printResult(const QString testName, const bool result,
                 const QString message);
} // namespace QtLudo
