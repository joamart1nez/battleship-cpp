#include "jugador.h"

Jugador::Jugador(int dimensiones, int maxBarcos, char *nombre) {
  this->tableroBarcos = new TableroBarcos(dimensiones, maxBarcos);
  this->tableroAtaques = new TableroAtaques(dimensiones);
  this->nombre = nombre;
  this->dimensiones = dimensiones;
}

void Jugador::dibujar(bool informacion) {
  if (informacion) {
    std::cout << "TABLERO DE ATAQUES\n";
    tableroAtaques->dibujar();
  }

  std::cout << "\n";
  std::cout << "TABLERO DE BARCOS\n";
  tableroBarcos->dibujar();

  if (informacion) {
    std::cout << "\n";
    tableroBarcos->info();
  }
}

bool Jugador::agregarBarco(Barco barco) {
  return tableroBarcos->agregarBarco(barco);
}

char *Jugador::getNombre() const { return nombre; }

bool Jugador::isGameOver() { return this->tableroBarcos->gameOver(); }

bool Jugador::recibirAtaque(int x, int y) {
  return this->tableroBarcos->recibirAtaque(x, y);
}

bool Jugador::marcarAtaque(int x, int y) {
  return this->tableroAtaques->recibirAtaque(x, y);
}

void Jugador::moverLanchas() { this->tableroBarcos->moverLanchas(); }
