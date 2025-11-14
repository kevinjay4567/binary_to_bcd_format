#include "bcd.h"
#include <bitset>
#include <iostream>
#include <sys/types.h>

Bcd *convert_bits_to_bcd(std::bitset<16> bits) {
  Bcd *bcd = new Bcd();

  if (bits.to_ulong() < 10) {
    bcd->unidad = bits.to_ulong();

    return bcd;
  }

  int i{15};

  while (i >= 0) {
    bcd->update(bits[i]);
    i--;
  }

  return bcd;
}

std::bitset<16> convert_bcd_to_bits(Bcd bcd) {
  ulong decimal;

  decimal += bcd.unidad.to_ulong();
  decimal += bcd.decena.to_ulong() * 10;
  decimal += bcd.centena.to_ulong() * 100;
  decimal += bcd.u_mil.to_ulong() * 1000;
  decimal += bcd.d_mil.to_ulong() * 10000;

  return std::bitset<16>(decimal);
}

int main() {
  int decision{};

  std::cout << "=== [1] Convertir de decimal/binario a BCD (max 16 bits) ===\n";
  std::cout << "=== [2] Convertir de BCD en formato BCD (max 16 bits) ===\n";

  std::cout << "[opcion 1 por defecto]: ";
  std::cin >> decision;

  if (decision != 2) {
    std::string input;
    std::cout << "=== Conversor de decimal/binario a formato BCD (max 16 "
                 "bits) ===\n";
    std::cout
        << "Ingrese el numero a convertir (decimal o binario [ej: 1011]): ";

    std::cin >> input;

    std::bitset<16> bits(input);

    Bcd *bcd = convert_bits_to_bcd(bits);

    std::cout << "DECIMAL: " << bits.to_ulong() << '\n';
    std::cout << "BINARY:  " << bits << '\n';
    std::cout << "BCD:     " << bcd->to_string() << '\n';

  } else {
    std::cout << "=== Conversor de formato BCD a decimal/binario (max 16 "
                 "bits) ===\n";

    std::cout << "Ingrese cada dígito BCD (4 bits)\n";

    std::string unidad_input, decena_input, centena_input, unidad_m_input, decena_m_input;

    std::cout << "Unidad: ";
    std::cin >> unidad_input;
    std::bitset<4> u(unidad_input);

    std::cout << "Decena: ";
    std::cin >> decena_input;
    std::bitset<4> d(decena_input);

    std::cout << "Centena: ";
    std::cin >> centena_input;
    std::bitset<4> c(centena_input);

    std::cout << "Unidad de mil: ";
    std::cin >> unidad_m_input;
    std::bitset<4> u_m(unidad_m_input);

    std::cout << "Decena de mil: ";
    std::cin >> decena_m_input;
    std::bitset<4> d_m(decena_m_input);

    Bcd bcd(u, d, c, u_m, d_m);

    std::cout << "\nBCD: " << bcd.to_string() << '\n';
    std::cout << "DECIMAL: " << convert_bcd_to_bits(bcd).to_ulong() << '\n';
    std::cout << "BINARY:  " << convert_bcd_to_bits(bcd) << '\n';
  }

  return 0;
}
