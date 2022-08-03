#include "juego.h"

Juego::Juego(bool debugMode) {
  std::cout << "=======BATALLA NAVAL=======\n\n";
  this->inicializarConfiguracion();
  this->debugMode = debugMode;
  this->randomRange = new RandomRange();
}

void Juego::iniciar() {
  this->colocacionAleatoria ? this->colocarBarcosAleatorio(Turno::Jugador)
                            : this->colocarBarcosManual();

  this->colocarBarcosAleatorio(Turno::IA);

  int continuar = 0;
  while (continuar != 1) {
    this->limpiarPantalla();
    this->dibujar();
    std::cout << "\nAsi quedara su tablero"
                 "\nIngrese 1 para continuar: ";
    std::cin >> continuar;
  }

  this->limpiarPantalla();
  this->actualizar();
}

void Juego::inicializarConfiguracion() {
  std::cout << "Parametros iniciales\n";
  std::cout << "Alto y ancho del tablero: ";
  std::cin >> this->dimensiones;
  std::cout << "Cantidad de barcos con los que vas a jugar: ";
  std::cin >> this->maxBarcos;
  std::cout << "Colorcar barcos de forma manual o aleatoria (0: Manual, 1: "
               "Aleatoria): ";
  std::cin >> this->colocacionAleatoria;

  if (colocacionAleatoria == 1) {
    int tamMaximoBarco = 5;
    /*
    para un ratio dimensiones/maxBarcos < [0.7,..., 0.9] con dicha dimension
    menor al doble del tamaño maximo de un barco (portaaviones = 5) se
    recomienda aumentar el tamaño de la misma
    */
    while (dimensiones / maxBarcos < 0.8f || dimensiones < tamMaximoBarco * 2) {
      int opcion;

      std::cout << "\nATENCION!!\n"
                   "Es probable que dicha configuracion cause que el programa "
                   "no pueda continuar\n"
                   "Se recominenda aumentar las dimensiones del mapa "
                   "(0: Reconfigurar - 1:Continuar): ";
      std::cin >> opcion;

      if (opcion == 0) {
        std::cout << "Alto y ancho del tablero: ";
        std::cin >> this->dimensiones;
      } else
        break;
    }
  }

  this->turno = Turno::Jugador;
  this->jugador = new class Jugador(dimensiones, maxBarcos, "Jugador");
  this->IA = new class Jugador(dimensiones, maxBarcos, "IA");
}

void Juego::actualizar() {
  this->dibujar();
  bool isContinuar = true, ataqueJugadorExitoso, ataqueIAExitoso;
  int x, y;
  std::cout << "\nIngrese coordenada X: ";
  std::cin >> x;
  std::cout << "Ingrese coordenada Y: ";
  std::cin >> y;

  while (isContinuar) {
    bool coordenadasVerificadas = this->verificarCoordenadas(x, y);

    if (coordenadasVerificadas) {
      ataqueJugadorExitoso = this->atacarIA(x, y);
      ataqueIAExitoso = this->atacarJugador();

      this->moverLanchas();
      this->limpiarPantalla();
      isContinuar = !jugador->isGameOver() && !IA->isGameOver();
    }

    if (isContinuar) {
      this->dibujar();

      if (coordenadasVerificadas) {
        this->infoAtaques(ataqueJugadorExitoso, ataqueIAExitoso);
      } else {
        std::cout << this->errorCargaDatos;
      }

      std::cout << "\nIngrese coordenada X: ";
      std::cin >> x;
      std::cout << "Ingrese coordenada Y: ";
      std::cin >> y;
    }
    this->limpiarPantalla();
  }

  this->limpiarPantalla();

  if (jugador->isGameOver())
    std::cout << "Perdiste :(\n";
  else if (IA->isGameOver())
    std::cout << "Ganaste!!!\n";
  this->dibujar();
}

bool Juego::colocarBarcosManual() {
  int i = 0;
  bool colocacionExitosa = true;
  int opcionBarco, x, y;
  char orientacion;

  while (i < this->maxBarcos) {
    this->limpiarPantalla();
    this->dibujar(false);
    std::cout << infoBarco;
    std::cout << "\nBarcos agregados: " << i << "/" << maxBarcos << "\n";

    if (!colocacionExitosa)
      std::cout << this->errorCargaDatos;

    std::cout << "\nBarco a agregar (1,2,3,4,5): ";
    std::cin >> opcionBarco;
    std::cout << "Posicion en x: ";
    std::cin >> x;
    std::cout << "Posicion en y: ";
    std::cin >> y;
    std::cout << "Orientacion (H: horizontal, V: vertical): ";
    std::cin >> orientacion;

    colocacionExitosa =
        this->colocarBarcos(this->jugador, opcionBarco, x, y, orientacion);
    if (colocacionExitosa)
      i++;
  }
  return true;
}

bool Juego::colocarBarcosAleatorio(int turno) {
  int i = 0;
  bool colocacionExitosa;

  while (i < maxBarcos) {
    int opcionBarco = randomRange->get(1, 6);
    int x = randomRange->get(0, this->dimensiones - 1);
    int y = randomRange->get(0, this->dimensiones - 1);
    char orientacion = randomRange->get(0, 2) == 1 ? 'H' : 'V';

    class Jugador *jugadorConTurno =
        (turno == Turno::Jugador) ? this->jugador : this->IA;

    colocacionExitosa =
        this->colocarBarcos(jugadorConTurno, opcionBarco, x, y, orientacion);

    if (colocacionExitosa)
      i++;
  }
  return true;
}

bool Juego::colocarBarcos(class Jugador *jugadorConTurno, int opcion, int x,
                          int y, char &orientacion) {
  orientacion = toupper(orientacion);
  if (int(orientacion) != 72 && int(orientacion) != 86)
    return false;

  switch (opcion) {
  case 1: {
    class Lancha lancha(x, y, orientacion);
    return jugadorConTurno->agregarBarco(lancha);
  } break;
  case 2: {
    class Crucero cru(x, y, orientacion);
    return jugadorConTurno->agregarBarco(cru);
  } break;
  case 3: {
    class Submarino sub(x, y, orientacion);
    return jugadorConTurno->agregarBarco(sub);
  } break;
  case 4: {
    class Destructor des(x, y, orientacion);
    return jugadorConTurno->agregarBarco(des);
  } break;
  case 5: {
    class Portaaviones porta(x, y, orientacion);
    return jugadorConTurno->agregarBarco(porta);
  } break;
  default:
    return false;
  }
}

bool Juego::verificarCoordenadas(int x, int y) {
  bool verificacion =
      ((x >= 0 && y >= 0) && (x < dimensiones && y < dimensiones));
  return verificacion;
}

bool Juego::atacarIA(int x, int y) {
  jugador->marcarAtaque(x, y);
  return IA->recibirAtaque(x, y);
}

bool Juego::atacarJugador() {
  int x = randomRange->get(0, this->dimensiones - 1);
  int y = randomRange->get(0, this->dimensiones - 1);
  IA->marcarAtaque(x, y);
  return jugador->recibirAtaque(x, y);
}

void Juego::moverLanchas() {
  this->jugador->moverLanchas();
  this->IA->moverLanchas();
}

void Juego::dibujar(bool informacion) {
  this->jugador->dibujar(informacion);
  if (debugMode) {
    std::cout << "Tablero de la IA\n";
    this->IA->dibujar();
  }
}

void Juego::infoAtaques(bool ataqueJugadorExitoso, bool ataqueIAExitoso) {
  std::cout << "\n";
  ataqueJugadorExitoso ? std::cout << "Ataque HACIA enemigo EXITOSO!!\n"
                       : std::cout << "Ataque HACIA enemigo FALLIDO!!\n";
  ataqueIAExitoso ? std::cout << "Ataque DEL enemigo EXITOSO!\n"
                  : std::cout << "Ataque DEL enemigo FALLIDO!!\n";
}

void Juego::limpiarPantalla() {
#ifdef _WIN32
  std::system("cls");
#elif __unix__
  std::system("clear");
#endif
}
