#include <bitset>
#include <iostream>
#include <string>
#include <sys/types.h>

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

class Bcd {
public:
  std::bitset<4> unidad;
  std::bitset<4> decena;
  std::bitset<4> centena;
  std::bitset<4> u_mil;
  std::bitset<4> d_mil;

  Bcd() {
    this->unidad = {0b0000};
    this->decena = {0b0000};
    this->centena = {0b0000};
    this->u_mil = {0b0000};
    this->d_mil = {0b0000};
  }

  std::string to_string() {
    return d_mil.to_string() + ' ' + u_mil.to_string() + ' ' +
           centena.to_string() + ' ' + decena.to_string() + ' ' +
           unidad.to_string();
  }

  void update(bool bit) {
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

private:
  void shift(std::bitset<4> &b1, bool bit) {
    b1 <<= 1;
    if (bit) {
      b1.flip(0);
    }

    if (b1.to_ulong() >= 5) {
      b1 = bitsetAdd(b1, {0b0011});
    }
  }
};

int main() {
  int i{15};
  Bcd *bcd = new Bcd();
  std::bitset<16> bits{0b11110011};


  while (i >= 0) {
    bcd->update(bits[i]);
    i--;
  }

  std::cout << "DECIMAL: " << bits.to_ulong() << '\n';
  std::cout << "BINARY:  " << bits << '\n';
  std::cout << "BCD:     " << bcd->to_string() << '\n';
  return 0;
}
