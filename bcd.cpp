#include "bcd.h"
#include <bitset>
#include <string>

bool fullAdder(bool b1, bool b2, bool &carry) {
  bool sum = (b1 ^ b2) ^ carry;
  carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
  return sum;
}

std::bitset<4> bitsetAdd(std::bitset<4> x, std::bitset<4> y) {
  bool carry{};
  std::bitset<4> ans;

  for (int i{}; i < 4; i++) {
    ans[i] = fullAdder(x[i], y[i], carry);
  }

  return ans;
}

Bcd::Bcd() {
  this->unidad = {0b0000};
  this->decena = {0b0000};
  this->centena = {0b0000};
  this->u_mil = {0b0000};
  this->d_mil = {0b0000};
}

Bcd::Bcd(std::bitset<4> u, std::bitset<4> d, std::bitset<4> c, std::bitset<4> u_m, std::bitset<4> d_m) {
    this->unidad = u;
    this->decena = d;
    this->centena = c;
    this->u_mil = u_m;
    this->d_mil = d_m;
}

// private methods
void Bcd::shift(std::bitset<4> &b1, bool bit) {
  b1 <<= 1;
  if (bit) {
    b1.flip(0);
  }

  if (b1.to_ulong() >= 5) {
    b1 = bitsetAdd(b1, {0b0011});
  }
}

// public methods
std::string Bcd::to_string() {
  return d_mil.to_string() + ' ' + u_mil.to_string() + ' ' +
         centena.to_string() + ' ' + decena.to_string() + ' ' +
         unidad.to_string();
}

void Bcd::update(bool bit) {
  bool unidad_carry = this->unidad[3];
  bool decena_carry = this->decena[3];
  bool centena_carry = this->centena[3];
  bool u_mil_carry = this->u_mil[3];

  this->shift(this->unidad, bit);
  this->shift(this->decena, unidad_carry);
  this->shift(this->centena, decena_carry);
  this->shift(this->u_mil, centena_carry);
  this->shift(this->d_mil, u_mil_carry);
}
