#include "fourier.h"
#include <iostream>
#include <vector>

int main() {
    try {
        // Створюємо об'єкт базового класу
        FourierSynthesis sintez(512, 10);

        // Задаємо бітове число для використання коефіцієнтів
        int S = 0;
        S |= (1 << 1); // Використовуємо 1-й коефіцієнт
        S |= (1 << 3); // Використовуємо 3-й коефіцієнт
        S |= (1 << 5); // Використовуємо 5-й коефіцієнт
        sintez.setS(S);

        // Амплітуди та фази
        std::vector<double> A(32, 0);
        std::vector<double> Fi(32, 0);
        A[1] = 1.0;
        A[3] = 0.5;
        A[5] = 0.2;
        Fi[1] = 0.0;
        Fi[3] = 90.0;
        Fi[5] = 180.0;

        sintez.setAmplitudesAndPhases(A, Fi);

        // Виконуємо синтез
        sintez.synthesize();

        // Виводимо результати
        int max_data = sintez.getMaxData();
        for (int i = 0; i < max_data; ++i) {
            std::cout << "x[" << i << "] = " << sintez.getX(i) << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}