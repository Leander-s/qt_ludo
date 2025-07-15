#pragma once
#include <QVector2D>
#include <QVector>
#include <iostream>
#include "State.h"

namespace QtLudo {
// Default map
const QVector<QVector2D> positionMappings = {
    // Path
    QVector2D(-7.0f, -1.0f),    // 0
    QVector2D(-6.0f, -1.0f),    // 1
    QVector2D(-5.0f, -1.0f),    // 2
    QVector2D(-4.0f, -1.0f),    // 3
    QVector2D(-3.0f, -1.0f),    // 4
    QVector2D(-2.0f, -1.0f),    // 5
    QVector2D(-1.0f, -1.0f),    // 6
    QVector2D(-1.0f, -2.0f),    // 7
    QVector2D(-1.0f, -3.0f),    // 8
    QVector2D(-1.0f, -4.0f),    // 9
    QVector2D(-1.0f, -5.0f),    // 10
    QVector2D(-1.0f, -6.0f),    // 11
    QVector2D(-1.0f, -7.0f),    // 12
    QVector2D(0.0f, -7.0f),     // 13

    QVector2D(1.0f, -7.0f),     // 14
    QVector2D(1.0f, -6.0f),     // 15
    QVector2D(1.0f, -5.0f),     // 16
    QVector2D(1.0f, -4.0f),     // 17
    QVector2D(1.0f, -3.0f),     // 18
    QVector2D(1.0f, -2.0f),     // 19
    QVector2D(1.0f, -1.0f),     // 20
    QVector2D(2.0f, -1.0f),     // 21
    QVector2D(3.0f, -1.0f),     // 22
    QVector2D(4.0f, -1.0f),     // 23
    QVector2D(5.0f, -1.0f),     // 24
    QVector2D(6.0f, -1.0f),     // 25
    QVector2D(7.0f, -1.0f),     // 26
    QVector2D(7.0f, 0.0f),      // 27

    QVector2D(7.0f, 1.0f),      // 28
    QVector2D(6.0f, 1.0f),      // 29
    QVector2D(5.0f, 1.0f),      // 30
    QVector2D(4.0f, 1.0f),      // 31
    QVector2D(3.0f, 1.0f),      // 32
    QVector2D(2.0f, 1.0f),      // 33
    QVector2D(1.0f, 1.0f),      // 34
    QVector2D(1.0f, 2.0f),      // 35
    QVector2D(1.0f, 3.0f),      // 36
    QVector2D(1.0f, 4.0f),      // 37
    QVector2D(1.0f, 5.0f),      // 38
    QVector2D(1.0f, 6.0f),      // 39
    QVector2D(1.0f, 7.0f),      // 40
    QVector2D(0.0f, 7.0f),      // 41

    QVector2D(-1.0f, 7.0f),     // 42
    QVector2D(-1.0f, 6.0f),     // 43
    QVector2D(-1.0f, 5.0f),     // 44
    QVector2D(-1.0f, 4.0f),     // 45
    QVector2D(-1.0f, 3.0f),     // 46
    QVector2D(-1.0f, 2.0f),     // 47
    QVector2D(-1.0f, 1.0f),     // 48
    QVector2D(-2.0f, 1.0f),     // 49
    QVector2D(-3.0f, 1.0f),     // 50
    QVector2D(-4.0f, 1.0f),     // 51
    QVector2D(-5.0f, 1.0f),     // 52
    QVector2D(-6.0f, 1.0f),     // 53
    QVector2D(-7.0f, 1.0f),     // 54
    QVector2D(-7.0f, 0.0f),     // 55
                               
    // Starting positions
    QVector2D(-6.0f, -6.0f),    // 56
    QVector2D(-3.0f, -6.0f),    // 57
    QVector2D(-6.0f, -3.0f),    // 58
    QVector2D(-3.0f, -3.0f),    // 59

    QVector2D(6.0f, -6.0f),     // 60
    QVector2D(3.0f, -6.0f),     // 61
    QVector2D(6.0f, -3.0f),     // 62
    QVector2D(3.0f, -3.0f),     // 63

    QVector2D(6.0f, 6.0f),      // 64
    QVector2D(3.0f, 6.0f),      // 65
    QVector2D(6.0f, 3.0f),      // 66
    QVector2D(3.0f, 3.0f),      // 67

    QVector2D(-6.0f, 6.0f),     // 68
    QVector2D(-3.0f, 6.0f),     // 69
    QVector2D(-6.0f, 3.0f),     // 70
    QVector2D(-3.0f, 3.0f),     // 71

    // Ending positions
    QVector2D(-6.0f, 0.0f),     // 72
    QVector2D(-5.0f, 0.0f),     // 73
    QVector2D(-4.0f, 0.0f),     // 74
    QVector2D(-3.0f, 0.0f),     // 75
    QVector2D(-2.0f, 0.0f),     // 76
    QVector2D(-1.0f, 0.0f),     // 77

    QVector2D(0.0f, -6.0f),     // 78
    QVector2D(0.0f, -5.0f),     // 79
    QVector2D(0.0f, -4.0f),     // 80
    QVector2D(0.0f, -3.0f),     // 81
    QVector2D(0.0f, -2.0f),     // 82
    QVector2D(0.0f, -1.0f),     // 83

    QVector2D(6.0f, 0.0f),      // 84
    QVector2D(5.0f, 0.0f),      // 85
    QVector2D(4.0f, 0.0f),      // 86
    QVector2D(3.0f, 0.0f),      // 87
    QVector2D(2.0f, 0.0f),      // 88
    QVector2D(1.0f, 0.0f),      // 89

    QVector2D(0.0f, 6.0f),      // 90
    QVector2D(0.0f, 5.0f),      // 91
    QVector2D(0.0f, 4.0f),      // 92
    QVector2D(0.0f, 3.0f),      // 93
    QVector2D(0.0f, 2.0f),      // 94
    QVector2D(0.0f, 1.0f),      // 95
};

QVector<QVector<quint8>> genDefaultPaths();
} // namespace QtLudo
