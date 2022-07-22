#include <iostream>
#include <vector>

enum Codigo { Agua, Navio, Ataque };

class Barco {
public:
  int x, y, k, golpes;
  char *nombre;
  char orientacion;
  int *cuerpo;
  int sinDaño = 0, daño = 1;
  bool isMuerto = false;
  Barco(int x, int y, int k, char orientacion, char *nombre) {
    this->x = x;
    this->y = y;
    this->k = k; // largo del barco
    this->orientacion = orientacion;
    this->nombre = nombre;
    this->golpes = 0;

    this->cuerpo = this->inicializarCuerpo();
  }
  ~Barco() {}

  int *inicializarCuerpo() {
    int *cuerpo = new int[k];
    for (int x = 0; x < k; ++x) {
      cuerpo[x] = sinDaño;
    }
    return cuerpo;
  }

  bool golpe(int x) { // AQUI AGREGAR LA LOGICA DEPENDIENDO DEL BARCO, SI ES
                      // SUBMARINO SOLO EN EL MEDIO
    // si el golpe se hizo dentro del rango de su longitud
    if (x <= k && this->cuerpo[x] != daño) {
      this->cuerpo[x] = daño;
      this->golpes++;
      return true;
    }
    if (this->golpes == this->k) {
      this->isMuerto = true;
      return true;
    }
    return false;
  }
};

class Tablero {
public:
  int cantBarcos, maxBarcos, dimension; // dimension
  int **tablero;
  std::vector<Barco> barcos;

  Tablero(int maxBarcos, int dimension) {
    this->cantBarcos = 0; // para contar que no se exceda el tamaño
    this->maxBarcos = maxBarcos;
    this->dimension = dimension;
    this->tablero = this->inicializaMatriz(Codigo::Agua);
  }

  int **inicializaMatriz(int casilla) {
    int **aux = new int *[dimension];
    for (int i = 0; i < dimension; i++) {
      aux[i] = new int[dimension];
    }

    for (int i = 0; i < dimension; i++) {
      for (int j = 0; j < dimension; j++)
        aux[i][j] = casilla;
    }
    return aux;
  }

  bool sePuedeAgregar(Barco barco) {
    if ((barco.x < 0 || barco.y < 0) ||
        (barco.x > dimension || barco.y > dimension))
      return false;

    if ((barco.orientacion == 'H' && barco.x + barco.k > dimension) ||
        (barco.orientacion == 'V' && barco.y + barco.k > dimension))
      return false;

    if (tablero[barco.x][barco.y] == Codigo::Navio)
      return false;

    /*
      este ciclo verifica a los alrededores del barco
      como el ancho de cada barco es de 1 y si hay que ver a sus dos lados eso
      da un total de 3 espacios en un eje a verificar por eso empieza desde -1
      (una posicion antes) y termina en 1 (una posicion despues) el resto se
      calcula segun la orientacion y sumando y restando 1 para verificar los
      espacios del otro eje
    */
    for (int i = -1; i <= 1; ++i) {
      if (barco.orientacion == 'H') {
        for (int j = barco.x - 1; j < (barco.x + barco.k) + 1; j++)
          if (tablero[j][barco.y + i] == Codigo::Navio)
            return false;
      }

      if (barco.orientacion == 'V') {
        for (int j = barco.y - 1; j < (barco.y + barco.k) + 1; j++)
          if (tablero[barco.x + i][j] == Codigo::Navio)
            return false;
      }
    }

    return true;
  }

  bool agregarBarco(Barco barco) {
    if (this->cantBarcos <= this->maxBarcos && this->sePuedeAgregar(barco)) {
      std::cout << barco.orientacion << "\n";
      this->barcos.push_back(barco);

      if (barco.orientacion == 'H') {
        for (int i = barco.x; i < barco.x + barco.k; i++) {
          tablero[i][barco.y] = Codigo::Navio;
        }
      }
      if (barco.orientacion == 'V') {
        for (int i = barco.y; i < barco.y + barco.k; i++) {
          tablero[barco.x][i] = Codigo::Navio;
        }
      }

      cantBarcos++;
      return true;
    }
    return false;
  }

  void recibirAtaque(int x, int y) {
    int posEnCuerpo = 0;

    this->tablero[x][y] = Codigo::Ataque;

    // agregar daño dentro del cuerpo del barco
    for (auto barco : barcos) {
      if (barco.orientacion == 'H' && (y == barco.y) &&
          (x >= barco.x && x <= barco.x + barco.k)) {
        posEnCuerpo = (x - barco.x);
      }
      if (barco.orientacion == 'V' && (x == barco.x) &&
          (y >= barco.y && y <= barco.y + barco.k)) {
        posEnCuerpo = (y - barco.y);
      }
      barco.golpe(posEnCuerpo);
    }
  }

  void print() {
    for (int y = 0; y < dimension; ++y) {
      for (int x = 0; x < dimension; ++x) {
        std::cout << this->tablero[x][y] << " ";
      }
      std::cout << "\n";
    }
  }
};

int main() {
  Tablero tablero1(5, 10);

  Barco lancha(1, 2, 1, 'V', "Lancha");
  Barco sub(3, 2, 4, 'V', "Submarino");
  tablero1.agregarBarco(lancha);
  tablero1.agregarBarco(sub);

  tablero1.recibirAtaque(5, 4);

  tablero1.print();

  /*
    CLASES
    -Juego: que controle la logica cruzada(el jugador ataca el tablero
    de la Ia y vicebersa) de ambos tableros, la colocacion manual o automatica
    de los barcos, informar que barcos han sido hundidos,
  */

  return 0;
}
