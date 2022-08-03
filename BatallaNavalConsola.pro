TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        barco.cpp \
        juego.cpp \
        jugador.cpp \
        main.cpp \
        randomrange.cpp \
        tablero.cpp \
        tableroataques.cpp \
        tablerobarcos.cpp

HEADERS += \
  barco.h \
  crucero.h \
  destructor.h \
  info.h \
  juego.h \
  jugador.h \
  lancha.h \
  portaaviones.h \
  randomrange.h \
  submarino.h \
  tablero.h \
  tableroataques.h \
  tablerobarcos.h
