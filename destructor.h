#ifndef DESTRUCTOR_H
#define DESTRUCTOR_H
#include "barco.h"

class Destructor : public Barco {
public:
  Destructor(){};
  Destructor(int x, int y, char orientacion)
      : Barco(x, y, 4, orientacion, "Destructor") {
    this->codigo = Codigo::Destructor;
  };
  ~Destructor(){};
};

#endif // DESTRUCTOR_H
