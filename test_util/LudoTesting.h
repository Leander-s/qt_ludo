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

template <typename Comp, typename T>
void testResults(const QString testName, const Comp Op, const T &result,
                 const T &expectedResult);

void printResult(const QString testName, const bool result,
                 const QString message);
} // namespace QtLudo
