#ifndef ESTRATEGIA_BASE_H
#define ESTRATEGIA_BASE_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "common.hpp"
#include "lista.hpp"
#include "nodo.hpp"

using namespace std;

#define EVASIVO 'E'
#define DEFAULT 'D'
#define AGRESIVO 'A'

void ValidarLimites(int NumFilas, int NumCol, int PosX, int PosY, int InfX, int InfY, int & LimIzq, 
					int & LimDer, int & LimSup, int & LimInf);
					

template <typename TipoLista>
class Estrategia
{
	public:
		virtual void Ejecutar(Lista<TipoLista> & lstAliados, Lista<TipoLista> & lstEnemigos, 
							  int InfGranadaX, int InfGranadaY, int NumFilas, int NumCol, int TurnoActual, 
							  int MaximoTurno, int EnergiaInicial)=0;
							 
		bool EstaCerca(int InfGranadaX, int InfGranadaY, int PosX, int PosY,int InfX, int InfY, TipoLista 	
				Dato,bool Aliado, int Precision=1);
		
		void BuscarCercanos(int InfGranadaX, int InfGranadaY, int PosX, int PosY, int InfX, int InfY, 	
						Lista<TipoLista> lst, Lista<TipoLista> & lstCercanos, 
						int Precision,bool Aliado);	
};


template <typename TipoLista>
void Estrategia<TipoLista>::BuscarCercanos(int InfGranadaX, int InfGranadaY, int PosX, int PosY, int InfX, int InfY, 	
						Lista<TipoLista> lst, Lista<TipoLista> & lstCercanos, 
						int Precision,bool Aliado)	
						
						/*BuscarCercanos(InfGranadaX,InfGranadaY,PosX,PosY,InfX,InfY,
								lstEnemigos,lstEnemigosCercanos,PRECISION_DEFENSA,false);	*/	
{
		/*[PosX,PosY] es la posicion de nuestro soldado, y se recibe la lista de soldados 
		  enemigos para devolver una lista donde quedan seleccionados nada mas los soldados
		  enemigos que pueden afectar a este soldado. */
		 
		 Nodo<TipoLista> *aux=lst.ObtenerComienzoLista();
		 	 
		 while(aux)
		 {
		 	TipoLista Dato= aux->ObtenerDato();
		 	if(EstaCerca(InfGranadaX,InfGranadaY,PosX,PosY,InfX,InfY,Dato,Aliado,Precision))
		 		lstCercanos.Insertar(Dato);
		 	
		 	aux=aux->ObtenerSiguiente();
		 }
}

template <typename TipoLista>
bool Estrategia<TipoLista>::EstaCerca(int InfGranadaX, int InfGranadaY, int PosX, int PosY,int InfX, int InfY, 
										TipoLista Dato,bool Aliado, int Precision)
{
		/*Recibe datos del soldado y el soldado enemigo y busca si hay overlap entre las zonas de
		influencia de ambos, bajo ese criterio, se considera que el soldado "esta cerca" y puede 
		afectar al soldado */
		
		int InfXE;
		int InfYE; 
		int PosXE=Dato.ObtenerPosicionX(); 
		int PosYE=Dato.ObtenerPosicionY();
		
		if(Aliado==true)
		{
			if(Dato.ObtenerAccion()==DEFENSA)
			{
				PosXE=Dato.ObtenerPosicionAccionX();
				PosYE=Dato.ObtenerPosicionAccionY();
			}
		}
		
		if(Precision==0)
		{
			InfXE=0;
			InfYE=0;
		}
		else
		{
			InfXE=Dato.ObtenerInfluenciaX();
			InfYE=Dato.ObtenerInfluenciaY();
		}	
	

		if((PosX+InfX+Precision)>=(PosXE-InfXE-InfGranadaX))
		{
			if(((PosY+InfY+Precision)>=(PosYE-InfYE-InfGranadaY))||((PosY-InfY-Precision)<=(PosYE+InfYE+InfGranadaY)))
				return true;
		}
		else 
		{
			if((PosX-InfX-Precision)<=(PosXE+InfXE+InfGranadaX))
				if(((PosY+InfY+Precision)>=(PosYE-InfYE-InfGranadaY))||
					((PosY-InfY-Precision)<=(PosYE+InfYE+InfGranadaY)))
					return true;
		}
		return false;
}

template<typename TipoLista>
int SumaEnergia(Lista<TipoLista> lst)
{
	int Suma=0;
	Nodo<TipoLista> *aux=lst.ObtenerComienzoLista();
			
	while(aux)
	{
		Suma+=(aux->ObtenerDato()).ObtenerEnergia();
		aux=aux->ObtenerSiguiente();
	}
			
	return Suma;
}	

template<typename TipoLista>		
void AsignarAccionesDefault(Lista<TipoLista> & lstAliados,Lista<TipoLista> & lstEnemigos, int TurnoActual, int MaximoTurno, int EnergiaInicial)	
{				
		int SumaEnergiaAliados=SumaEnergia(lstAliados);
		int SumaEnergiaEnemigos=SumaEnergia(lstEnemigos);
				
		double FactorEnergia=(double)SumaEnergiaAliados/SumaEnergiaEnemigos;
				
		Nodo<TipoLista> *NodoAux=lstAliados.ObtenerComienzoLista();
							
		while(NodoAux)
		{
			int Energia=(NodoAux->ObtenerDato()).ObtenerEnergia();
			if(Energia>FACTOR_VIDA_MAX*(EnergiaInicial))
				(NodoAux->ObtenerDato()).AsignarAccion(DEFENSA);
			else if(Energia<FACTOR_VIDA_MIN*(EnergiaInicial))
				(NodoAux->ObtenerDato()).AsignarAccion(ATAQUE);
			else
			{
				double FactorTurno=(double)(TurnoActual)/MaximoTurno;
						
				if((FactorTurno>=FACTOR_TURNO_DEFECTO)&&(FactorEnergia<1))
					(NodoAux->ObtenerDato()).AsignarAccion(ATAQUE);
				else if((FactorTurno>=FACTOR_TURNO_DEFECTO)&&(FactorEnergia>1))
					(NodoAux->ObtenerDato()).AsignarAccion(DEFENSA);
				else
				{
					if(FactorEnergia>FACTOR_ENERGIA_DEFECTO)
						(NodoAux->ObtenerDato()).AsignarAccion(DEFENSA);
					else if(FactorEnergia<(double)1/FACTOR_ENERGIA_DEFECTO)
						(NodoAux->ObtenerDato()).AsignarAccion(ATAQUE);
					else
					{
						srand(time(NULL));
						int AuxRandom=rand()%LIMITE_RANDOM;
							
						if(!AuxRandom)
							(NodoAux->ObtenerDato()).AsignarAccion(DEFENSA);
						else
							(NodoAux->ObtenerDato()).AsignarAccion(ATAQUE);
					}
				}	
			}
			NodoAux=NodoAux->ObtenerSiguiente();			
		}
		NodoAux=lstAliados.ObtenerComienzoLista();
				
}

#endif
