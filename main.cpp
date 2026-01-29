#include <iostream>
#include <vector>
#include <random>
#include <omp.h>

int main() {
    const int N = 1000;
    std::vector<int> A(N), B(N), C(N);

    // Generar números aleatorios (0 a 100)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 100);

    for (int i = 0; i < N; i++) {
        A[i] = dist(gen);
        B[i] = dist(gen);
    }

    // For paralelo con OpenMP
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }

    // Imprimir una muestra (primeros 10) para comprobar
    std::cout << "Primeros 10 elementos:\n";
    for (int i = 0; i < 10; i++) {
        std::cout << "A[" << i << "]=" << A[i]
                  << "  B[" << i << "]=" << B[i]
                  << "  C[" << i << "]=" << C[i] << "\n";
    }

    // Validación básica
    int errores = 0;
    for (int i = 0; i < N; i++) {
        if (C[i] != A[i] + B[i]) errores++;
    }

    if (errores == 0) {
        std::cout << "\n Suma en paralelo correcta.\n";
    } else {
        std::cout << "\n Fallo: errores = " << errores << "\n";
    }

    return 0;
}