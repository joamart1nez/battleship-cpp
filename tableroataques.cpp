#include "tableroataques.h"

TableroAtaques::TableroAtaques(int dimension) : Tablero(dimension) {}

bool TableroAtaques::recibirAtaque(int x, int y) {
  if (!this->verificarCoordenadas(x, y))
    return false;

  this->matriz[x][y] = Codigo::Ataque;
  return true;
}
