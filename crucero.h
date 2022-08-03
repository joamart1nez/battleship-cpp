#ifndef CRUCERO_H
#define CRUCERO_H
#include "barco.h"

class Crucero : public Barco {
public:
  Crucero(){};
  Crucero(int x, int y, char orientacion)
      : Barco(x, y, 3, orientacion, "Crucero") {
    this->codigo = Codigo::Crucero;
  };
  ~Crucero(){};
};

#endif // CRUCERO_H
