#include "tablero.h"

Tablero::Tablero(int dimension) {
  this->dimension = dimension;
  this->matriz = this->inicializarMatriz(Codigo::Agua);
}

int **Tablero::inicializarMatriz(int codCasilla) {
  int **aux = new int *[dimension];

  for (int i = 0; i < dimension; i++) {
    aux[i] = new int[dimension];
  }

  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++)
      aux[i][j] = codCasilla;
  }
  return aux;
}

bool Tablero::cambiarCasilla(int x, int y, int codCasilla) {
  if ((x >= dimension || y >= dimension) || (x < 0 || y < 0))
    return false;
  this->matriz[x][y] = codCasilla;
  return true;
}

void Tablero::dibujar() {
  std::cout << " ";
  for (int i = 0; i < dimension; ++i)
    std::cout << std::right << std::setw(3) << std::setfill(' ') << i;
  std::cout << "\n";

  for (int y = 0; y < dimension; ++y) {
    std::cout << std::left << std::setw(3) << std::setfill(' ') << y;
    for (int x = 0; x < dimension; ++x) {
      if (this->matriz[x][y] == Codigo::Agua)
        std::cout << std::left << std::setw(3) << std::setfill(' ') << '-';
      else if (this->matriz[x][y] == Codigo::Ataque)
        std::cout << std::left << std::setw(3) << std::setfill(' ') << '*';
      else if (this->matriz[x][y] == Codigo::Dañado)
        std::cout << std::left << std::setw(3) << std::setfill(' ') << '~';
      else
        std::cout << std::left << std::setw(3) << std::setfill(' ')
                  << this->matriz[x][y];
    }
    std::cout << "\n";
  }
}

bool Tablero::verificarCoordenadas(int x, int y) {
  return ((x >= 0 && y >= 0) && (x < dimension && y < dimension));
}
