#ifndef JUEGO_H
#define JUEGO_H
#include "crucero.h"
#include "destructor.h"
#include "info.h"
#include "jugador.h"
#include "lancha.h"
#include "portaaviones.h"
#include "randomrange.h"
#include "submarino.h"

class Juego {
private:
  class Jugador *jugador;
  class Jugador *IA;
  RandomRange *randomRange;
  int dimensiones, maxBarcos;
  bool colocacionAleatoria;
  bool turno;
  bool debugMode;
  char *nombreJugador;
  char *infoBarco = "\n1: Lancha (Tamanio = 1)\n"
                    "2: Crucero (Tamanio = 3\n"
                    "3: Submarino (Tamanio = 3)\n"
                    "4: Destructor (Tamanio = 4)\n"
                    "5: Portaaviones(Tamanio = 5)\n";
  char *errorCargaDatos =
      "\nError en algún parametro, favor de volver a cargar bien "
      "los datos\n";

public:
  Juego(bool = false);
  ~Juego(){};

  void iniciar();
  void inicializarConfiguracion();
  void actualizar();

  // Colocacion de barcos
  bool colocarBarcosManual();
  bool colocarBarcosAleatorio(int);
  bool colocarBarcos(class Jugador *, int, int, int, char &);

  // Ataques
  bool verificarCoordenadas(int, int);
  bool atacarIA(int, int);
  bool atacarJugador();

  // mover la lancha en cada turno
  void moverLanchas();

  // dibujado
  void limpiarPantalla();
  void dibujar(bool = true);
  void infoAtaques(bool, bool);
};

#endif // JUEGO_H
