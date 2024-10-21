#include "fourier.h"
#include <cmath>
#include <stdexcept>

// Конструктор класу
FourierSynthesis::FourierSynthesis(int M, int P) : M(M), P(P), A(32, 0), Fi(32, 0), S(0) {
    if (M < 256 || P < 1) {
        throw std::invalid_argument("Invalid M or P value");
    }
    x.resize(M * P, 0); // Ініціалізуємо масив нулями
}

// Метод для встановлення кількості вибірок на період
void FourierSynthesis::setM(int M) {
    if (M >= 256) {
        this->M = M;
        x.resize(M * P, 0); // Оновлюємо розмір масиву
    }
}

// Метод для встановлення кількості періодів
void FourierSynthesis::setP(int P) {
    if (P >= 1) {
        this->P = P;
        x.resize(M * P, 0); // Оновлюємо розмір масиву
    }
}

// Метод для встановлення бітів для використання коефіцієнтів ряду Фур'є
void FourierSynthesis::setS(int S) {
    this->S = S;
}

// Метод для встановлення амплітуд і фаз
void FourierSynthesis::setAmplitudesAndPhases(const std::vector<double>& A, const std::vector<double>& Fi) {
    if (A.size() == 32 && Fi.size() == 32) {
        this->A = A;
        this->Fi = Fi;
    } else {
        throw std::invalid_argument("A and Fi arrays must be of size 32");
    }
}

// Синтез сигналу на основі ряду Фур'є
void FourierSynthesis::synthesize() {
    for (int i = 0; i < M * P; ++i) {
        x[i] = 0;
        for (int k = 0; k < 32; ++k) {
            if (S & (1 << k)) {
                x[i] += A[k] * cos(2 * M_PI * k * i / M + Fi[k] * M_PI / 180);
            }
        }
    }
}

// Метод для отримання результату синтезу
double FourierSynthesis::getX(int i) const {
    if (i >= 0 && i < M * P) {
        return x[i];
    } else {
        throw std::out_of_range("Index out of range");
    }
}

// Метод для отримання кількості синтезованих відліків
int FourierSynthesis::getMaxData() const {
    return M * P;
}

// Очищення масиву
void FourierSynthesis::clear() {
    x.clear();
}

// Конструктор успадкованого класу
LimitedFourierSynthesis::LimitedFourierSynthesis(int M, int P) : FourierSynthesis(M, P) {}

// Перевизначення методу для встановлення амплітуд із обмеженням
void LimitedFourierSynthesis::setAmplitudesAndPhases(const std::vector<double>& A, const std::vector<double>& Fi) {
    FourierSynthesis::setAmplitudesAndPhases(A, Fi);
    // Обмежуємо амплітуди до 1.0
    for (double& a : this->A) {
        if (a > 1.0) {
            a = 1.0;
        }
    }
}