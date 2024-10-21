#ifndef RGR_FOURIER_H
#define RGR_FOURIER_H

#endif //RGR_FOURIER_H

#ifndef FOURIER_H
#define FOURIER_H

#include <vector>

// Базовий клас для синтезу сигналу на основі ряду Фур'є
class FourierSynthesis {
protected:
    int M; // Кількість вибірок на період
    int P; // Кількість періодів
    std::vector<double> A; // Амплітуди коефіцієнтів ряду Фур'є
    std::vector<double> Fi; // Початкові фази коефіцієнтів ряду Фур'є
    std::vector<double> x; // Результуючий масив для синтезованого сигналу
    int S; // Бітове число для вибору коефіцієнтів ряду Фур'є

public:
    // Конструктор класу
    FourierSynthesis(int M = 256, int P = 1);

    // Метод для встановлення кількості вибірок на період
    void setM(int M);

    // Метод для встановлення кількості періодів
    void setP(int P);

    // Метод для встановлення бітів для використання коефіцієнтів ряду Фур'є
    void setS(int S);

    // Метод для встановлення амплітуд і фаз
    void setAmplitudesAndPhases(const std::vector<double>& A, const std::vector<double>& Fi);

    // Синтез сигналу на основі ряду Фур'є
    void synthesize();

    // Метод для отримання результату синтезу
    double getX(int i) const;

    // Метод для отримання кількості синтезованих відліків
    int getMaxData() const;

    // Очищення масиву
    void clear();
};

// Спадковий клас для обмеження амплітуд
class LimitedFourierSynthesis : public FourierSynthesis {
public:
    // Конструктор успадкованого класу
    LimitedFourierSynthesis(int M = 256, int P = 1);

    // Перевизначення методу для встановлення амплітуд із обмеженням
    void setAmplitudesAndPhases(const std::vector<double>& A, const std::vector<double>& Fi) ;
};

#endif // FOURIER_H