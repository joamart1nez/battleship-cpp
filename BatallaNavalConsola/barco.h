#ifndef BARCO_H
#define BARCO_H
#include "info.h"

class Barco {
protected:
  int x, y, k, golpes;
  int *cuerpo;
  char *nombre;
  char orientacion;
  bool isMuerto;
  int codigo;

public:
  Barco(){};
  Barco(int, int, int, char, char *);
  ~Barco();

  int *inicializaCuerpo();
  virtual bool golpe(int);
  int getX() const;
  int getY() const;
  int getK() const;
  char getOrientacion() const;
  char *getNombre() const;
  int getCodigo() const;
  int getGolpes() const;
  bool getIsMuerto() const;
  void setX(int newX);
  void setY(int newY);

  bool compararChar(char *char1, char *char2, int tamaño) {
    for (int i = 0; i < tamaño; ++i)
      if (char1[i] != char2[i])
        return false;
    return true;
  }
};

#endif // BARCO_H
