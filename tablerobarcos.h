#ifndef TABLEROBARCOS_H
#define TABLEROBARCOS_H
#include "barco.h"
#include "randomrange.h"
#include "tablero.h"
#include <cstdlib>

class TableroBarcos : public Tablero {
private:
  int cantBarcos, maxBarcos;
  Barco **barcos;
  RandomRange *randomRange;

public:
  TableroBarcos();
  TableroBarcos(int, int);
  ~TableroBarcos(){};

  Barco **inicializaBarcos();
  bool sePuedeAgregar(Barco);
  bool agregarBarco(Barco);
  bool recibirAtaque(int, int);
  bool gameOver();
  void info();
  void moverLanchas();
  bool compararChar(char *, char *, int);
};

#endif // TABLEROBARCOS_H
