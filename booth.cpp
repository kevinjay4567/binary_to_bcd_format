#include <iostream>
#include <bitset>
#include <string>
#include <cmath>
using namespace std;

const int BITS = 16;

// Convierte binario string → entero con signo (2's complement)
int binToDec(const string &bin) {
    bitset<BITS> b(bin);
    // Si MSB = 1 → número negativo
    if (b[BITS - 1] == 1)
        return -((int)((~b).to_ulong() + 1));
    return (int)b.to_ulong();
}

// Convierte entero → binario string de 16 bits (2's complement)
string decToBin(int num) {
    bitset<BITS> b;
    if (num < 0) {
        int pos = (abs(num) ^ ((1 << BITS) - 1)) + 1;
        b = bitset<BITS>(pos);
    } else {
        b = bitset<BITS>(num);
    }
    return b.to_string();
}

// Algoritmo de Booth
string boothMultiply(int multiplicand, int multiplier) {
    bitset<BITS> A(multiplicand);   // A
    bitset<BITS> S(-multiplicand); // -A
    bitset<BITS + BITS> P;         // [A | Q | Q-1]

    // Inicializar P
    for (int i = 0; i < BITS; i++)
        P[i + BITS] = (multiplier >> (BITS - 1 - i)) & 1;

    int Qm1 = 0;

    for (int i = 0; i < BITS; i++) {
        int Q0 = P[0];

        if (Q0 == 0 && Qm1 == 1) {
            // Suma A
            bitset<BITS + BITS> temp(A.to_ullong());
            temp <<= BITS;
            P = bitset<BITS + BITS>(P.to_ullong() + temp.to_ullong());
        }
        else if (Q0 == 1 && Qm1 == 0) {
            // Resta A → suma S
            bitset<BITS + BITS> temp(S.to_ullong());
            temp <<= BITS;
            P = bitset<BITS + BITS>(P.to_ullong() + temp.to_ullong());
        }

        // Guardar Q-1
        Qm1 = Q0;

        // Desplazamiento aritmético a la derecha
        bool msb = P[BITS + BITS - 1];
        P >>= 1;
        P[BITS + BITS - 1] = msb;
    }

    return P.to_string();
}

int main() {
    string inputA, inputB;
    int a, b;

    cout << "=== Multiplicación con Algoritmo de Booth (max 16 bits) ===" << endl;
    cout << "Ingrese el primer número (decimal o binario prefijado con b: ej: b1011): ";
    cin >> inputA;

    cout << "Ingrese el segundo número (decimal o binario prefijado con b: ej: b1100): ";
    cin >> inputB;

    // Procesar entradas
    if (inputA[0] == 'b')
        a = binToDec(inputA.substr(1));
    else
        a = stoi(inputA);

    if (inputB[0] == 'b')
        b = binToDec(inputB.substr(1));
    else
        b = stoi(inputB);

    // Mostrar en ambas representaciones
    cout << "\n--- Valores ingresados ---\n";
    cout << "A (dec) = " << a << " | A (bin) = " << decToBin(a) << endl;
    cout << "B (dec) = " << b << " | B (bin) = " << decToBin(b) << endl;

    // Ejecutar Booth
    string resultBin = boothMultiply(a, b);

    // Convertir resultado final a decimal (32 bits posibles)
    long resultDec = stoll(resultBin, nullptr, 2);
    if (resultBin[0] == '1') {
        // Es negativo (2's complement)
        resultDec = resultDec - (1LL << 32);
    }

    cout << "\n=== Resultado ===" << endl;
    cout << "Binario (32 bits): " << resultBin << endl;
    cout << "Decimal: " << resultDec << endl;

    return 0;
}

