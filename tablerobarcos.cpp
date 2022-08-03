#include "tablerobarcos.h"

TableroBarcos::TableroBarcos(int dimension, int maxBarcos)
    : Tablero(dimension) {
  this->cantBarcos = 0;
  this->maxBarcos = maxBarcos;
  this->barcos = this->inicializaBarcos();
  this->randomRange = new RandomRange();
}

Barco **TableroBarcos::inicializaBarcos() {
  Barco **arregloBarcos = new Barco *[this->maxBarcos];
  return arregloBarcos;
}

bool TableroBarcos::compararChar(char *char1, char *char2, int tamaño) {
  for (int i = 0; i < tamaño; i++)
    if (char1[i] != char2[i])
      return false;
  return true;
}

bool TableroBarcos::sePuedeAgregar(Barco barco) {
  if ((barco.getX() < 0 || barco.getY() < 0) ||
      (barco.getX() > dimension || barco.getY() > dimension))
    return false;

  if ((barco.getOrientacion() == 'H' &&
       barco.getX() + barco.getK() > dimension) ||
      (barco.getOrientacion() == 'V' &&
       barco.getY() + barco.getK() > dimension))
    return false;

  int inicioI, finalI;
  int inicioJ, finalJ;
  if (barco.getOrientacion() == 'H') {
    inicioI = (barco.getY() - 1) < 0 ? 0 : -1;
    finalI = (barco.getY() + barco.getK()) > dimension - 1 ? 0 : 1;
    inicioJ = barco.getX() - 1 < 0 ? barco.getX() : barco.getX() - 1;
    finalJ = (barco.getX() + barco.getK()) + 1 > dimension - 1
                 ? barco.getX() + barco.getK()
                 : barco.getX() + barco.getK() + 1;

    for (int i = inicioI; i <= finalI; ++i) {
      for (int j = inicioJ; j < finalJ; j++) {
        if (matriz[j][barco.getY() + i] != Codigo::Agua)
          return false;
      }
    }
  }
  if (barco.getOrientacion() == 'V') {
    inicioI = (barco.getX() - 1) < 0 ? 0 : -1;
    finalI = (barco.getX() + barco.getK()) > dimension - 1 ? 0 : 1;
    inicioJ = barco.getY() - 1 < 0 ? barco.getY() : barco.getY() - 1;
    finalJ = (barco.getY() + barco.getK()) + 1 > dimension - 1
                 ? barco.getY() + barco.getK()
                 : barco.getY() + barco.getK() + 1;

    for (int i = inicioI; i <= finalI; ++i) {
      for (int j = inicioJ; j < finalJ; j++) {
        if (matriz[barco.getX() + i][j] != Codigo::Agua)
          return false;
      }
    }
  }
  return true;
}

bool TableroBarcos::agregarBarco(Barco barco) {
  if (!this->sePuedeAgregar(barco) || (this->cantBarcos > this->maxBarcos))
    return false;

  Barco *upcastingBarco = new Barco(barco);
  this->barcos[cantBarcos] = upcastingBarco;

  if (barco.getOrientacion() == 'H') {
    for (int i = barco.getX(); i < barco.getX() + barco.getK(); i++) {
      matriz[i][barco.getY()] = barco.getCodigo();
    }
  }
  if (barco.getOrientacion() == 'V') {
    for (int i = barco.getY(); i < barco.getY() + barco.getK(); i++) {
      matriz[barco.getX()][i] = barco.getCodigo();
    }
  }
  cantBarcos++;
  return true;
}

bool TableroBarcos::recibirAtaque(int x, int y) {
  if (!this->verificarCoordenadas(x, y))
    return false;

  int posEnCuerpo = 0;
  this->matriz[x][y] = Codigo::Ataque;

  for (int i = 0; i < cantBarcos; i++) {
    if (barcos[i]->getOrientacion() == 'H' && (y == barcos[i]->getY()) &&
        (x >= barcos[i]->getX() &&
         x <= barcos[i]->getX() + barcos[i]->getK())) {
      posEnCuerpo = (x - barcos[i]->getX());
      barcos[i]->golpe(posEnCuerpo);
      this->matriz[x][y] = Codigo::Dañado;
      return true;
    }
    if (barcos[i]->getOrientacion() == 'V' && (x == barcos[i]->getX()) &&
        (y >= barcos[i]->getY() &&
         y <= barcos[i]->getY() + barcos[i]->getK())) {
      posEnCuerpo = (y - barcos[i]->getY());
      barcos[i]->golpe(posEnCuerpo);
      this->matriz[x][y] = Codigo::Dañado;
      return true;
    }
  }
  return false;
}

bool TableroBarcos::gameOver() {
  int barcosMuertos = 0;
  for (int i = 0; i < cantBarcos; ++i) {
    if (this->barcos[i]->getGolpes() == this->barcos[i]->getK())
      barcosMuertos++;
  }
  return (barcosMuertos == maxBarcos);
}

void TableroBarcos::info() {
  for (int i = 0; i < cantBarcos; ++i) {
    Barco *barco = barcos[i];
    std::cout << std::left << std::setw(11) << std::setfill(' ')
              << barco->getNombre();
    std::cout << "(" << barco->getX() << "," << barco->getY() << ") - "
              << std::left << std::setw(3) << std::setfill(' ');
    if (!barco->getIsMuerto())
      std::cout << "Vida: " << (barco->getK() - barco->getGolpes()) << "/"
                << barco->getK() << " ";
    else
      std::cout << "Esta muerto";
    std::cout << "\n";
  }
}

void TableroBarcos::moverLanchas() {
  char lanchaChar[] = "Lancha";

  for (int i = 0; i < maxBarcos; ++i) {
    Barco *lancha = this->barcos[i];
    if (compararChar(lancha->getNombre(), lanchaChar, 6) &&
        !lancha->getIsMuerto()) {

      int anteriorX = lancha->getX();
      int anteriorY = lancha->getY();
      int newX = randomRange->get(0, this->dimension - 1);
      int newY = randomRange->get(0, this->dimension - 1);

      lancha->setX(newX);
      lancha->setY(newY);

      while (!this->verificarCoordenadas(newX, newY) ||
             !this->sePuedeAgregar(*lancha)) {
        newX = randomRange->get(0, this->dimension - 1);
        newY = randomRange->get(0, this->dimension - 1);
        lancha->setX(newX);
        lancha->setY(newY);
      }

      this->cambiarCasilla(anteriorX, anteriorY, Codigo::Agua);
      this->cambiarCasilla(newX, newY, Codigo::Lancha);
    }
  }
}
