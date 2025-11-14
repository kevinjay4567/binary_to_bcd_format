#ifndef BCD_H
#define BCD_H

#include <bitset>

bool fullAdder(bool b1, bool b2, bool &carry);

std::bitset<4> bitsetAdd(std::bitset<4> x, std::bitset<4> y);

class Bcd {
public:
  std::bitset<4> unidad;
  std::bitset<4> decena;
  std::bitset<4> centena;
  std::bitset<4> u_mil;
  std::bitset<4> d_mil;

  Bcd();
  Bcd(std::bitset<4> u, std::bitset<4> d, std::bitset<4> c, std::bitset<4> u_m, std::bitset<4> d_m);

  std::string to_string();
  void update(bool bit);

private:
  void shift(std::bitset<4> &b1, bool bit);
};

#endif // !BCD_H
