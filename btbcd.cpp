#include "bcd.h"
#include <bitset>
#include <iostream>
#include <sys/types.h>

Bcd *convert_bits_to_bcd(std::bitset<16> bits) {
  Bcd *bcd = new Bcd();
  int i{15};

  while (i >= 0) {
    bcd->update(bits[i]);
    i--;
  }

  return bcd;
}

// TODO: Falta implementar
std::bitset<16> convert_bcd_to_bits(Bcd *bcd) { return 0; }

int main() {
  std::bitset<16> bits{0b11110011};
  Bcd *bcd = convert_bits_to_bcd(bits);

  std::cout << "DECIMAL: " << bits.to_ulong() << '\n';
  std::cout << "BINARY:  " << bits << '\n';
  std::cout << "BCD:     " << bcd->to_string() << '\n';
  return 0;
}
