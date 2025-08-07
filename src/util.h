#include <QCoreApplication>
#include <QTime>

namespace QtLudo {
void delay(int timeInSecs);

template <typename T> T mathMod(T A, T B) {
        // This returns the standard modulo class of A mod B
        T mod = A % B;
        if (mod < 0) {
                mod += B;
        }
        return mod;
}
} // namespace QtLudo
