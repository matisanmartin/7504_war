#ifndef ESTRATEGIA_H
#define ESTRATEGIA_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "common.hpp"
#include "lista.hpp"
#include "nodo.hpp"
#include "estrategia_base.hpp"
#include "estrategia_agresiva.hpp"
#include "estrategia_evasiva.hpp"


template <typename TipoLista>
class TestEstrategia
{
  public:
    TestEstrategia(){Estrategia_ = NULL;}

    void AsignarEstrategia(char Modo);
    void RealizarEstrategia(Lista<TipoLista> & lstAliados, Lista<TipoLista> & lstEnemigos, 
							int InfGranadaX, int InfGranadaY, int NumFilas, int NumCol, int TurnoActual, int MaximoTurno, int EnergiaInicial);
  private:
    Estrategia<TipoLista> *Estrategia_;
};

template <typename TipoLista>
void TestEstrategia<TipoLista>::AsignarEstrategia(char Modo)
{
  delete Estrategia_;
  
  if (Modo==EVASIVO)
    Estrategia_ = new EstrategiaEvasiva<TipoLista>();
  else if (Modo==AGRESIVO)
    Estrategia_ = new EstrategiaAgresiva<TipoLista>();
}

template <typename TipoLista>
void TestEstrategia<TipoLista>::RealizarEstrategia(Lista<TipoLista> & lstAliados, Lista<TipoLista> & lstEnemigos, 
										int InfGranadaX, int InfGranadaY, int NumFilas, int NumCol, int TurnoActual, int MaximoTurno, int EnergiaInicial)
{
  Estrategia_->Ejecutar(lstAliados,lstEnemigos,InfGranadaX,InfGranadaY,NumFilas,NumCol,TurnoActual,MaximoTurno,EnergiaInicial);
}

#endif
