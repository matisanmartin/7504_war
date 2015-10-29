#ifndef ESTRATEGIA_EVASIVA_H
#define ESTRATEGIA_EVASIVA_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "common.hpp"
#include "lista.hpp"
#include "nodo.hpp"
#include "estrategia_base.hpp"

template <typename TipoLista>
class EstrategiaEvasiva : public Estrategia<TipoLista>
{
	private:
		void Ejecutar(Lista<TipoLista> & lstAliados,Lista<TipoLista> & lstEnemigos, 
						int InfGranadaX, int InfGranadaY, int NumFilas, int NumCol, int TurnoActual, int MaximoTurno, int EnergiaInicial);
		int CalcularPeso(Lista<TipoLista> lstCercanos, int Fila, int Columna, int NumFilas, int NumCol);
	
	public:
		EstrategiaEvasiva(): Estrategia<TipoLista>(){}
};

template <typename TipoLista>
int EstrategiaEvasiva<TipoLista>::CalcularPeso(Lista<TipoLista> lstCercanos, int Fila, int Columna, int NumFilas, int NumCol)
{
	Nodo<TipoLista> *aux =lstCercanos.ObtenerComienzoLista();
	
	int Peso=0;
	
	while(aux)
	{
		TipoLista Cercano=aux->ObtenerDato();
				
		int PosXE= Cercano.ObtenerPosicionX();
		int PosYE=Cercano.ObtenerPosicionY();
		int InfXE=Cercano.ObtenerInfluenciaX();
		int InfYE=Cercano.ObtenerInfluenciaY();
		int LimInf,LimSup,LimDer,LimIzq;
			
		ValidarLimites(NumFilas, NumCol,PosXE,PosYE,InfXE,InfYE,LimIzq,LimDer,LimSup,LimInf);
		for(int i=LimIzq;i<LimDer;i++)
			for(int j=LimSup;j<LimInf;j++)
			{
				int Distancia=(Fila-i)*(Fila-i) + (Columna-j)*(Columna-j);
				Peso+=Distancia;
			}
		
		aux=aux->ObtenerSiguiente();
	}
	
	return Peso;
}

template <typename TipoLista>
void EstrategiaEvasiva<TipoLista>::Ejecutar(Lista<TipoLista> & lstAliados,Lista<TipoLista> & lstEnemigos,int InfGranadaX, int InfGranadaY, int NumFilas, int NumCol, 
				int TurnoActual, int MaximoTurno, int EnergiaInicial)
{
	
	cerr<<60<<endl;
	Nodo<TipoLista> *NodoAuxAliados=lstAliados.ObtenerComienzoLista();
			
	while(NodoAuxAliados)
	{
		if((NodoAuxAliados->ObtenerDato()).ObtenerAccion()==ATAQUE)
			NodoAuxAliados=NodoAuxAliados->ObtenerSiguiente();
		else
		{
			int PosX=(NodoAuxAliados->ObtenerDato()).ObtenerPosicionX();
			int PosY=(NodoAuxAliados->ObtenerDato()).ObtenerPosicionY();
			int InfX=(NodoAuxAliados->ObtenerDato()).ObtenerInfluenciaX();
			int InfY=(NodoAuxAliados->ObtenerDato()).ObtenerInfluenciaY();

			Lista<TipoLista> lstEnemigosCercanos;
				
			BuscarCercanos(InfGranadaX,InfGranadaY,PosX,PosY,InfX,InfY,
							lstEnemigos,lstEnemigosCercanos,PRECISION_DEFENSA,false);
			
			int LimInf,LimSup,LimDer,LimIzq;
	
			ValidarLimites(NumFilas,NumCol,PosX,PosY,InfX,InfY,
						LimIzq,LimDer,LimSup,LimInf);
				
			int PesoMaximo,PesoNuevo;
				
			int PosNuevaX,PosNuevaY;
	
			for(int i=LimIzq;i<=LimDer;i++)
				for(int j=LimSup;j<=LimInf;j++)
				{
					if((j==LimSup)&&(i==LimIzq))
					{
						PesoMaximo=CalcularPeso(lstEnemigosCercanos,i,j,NumFilas,NumCol);
						PosNuevaX=LimIzq;
						PosNuevaY=LimSup;
					}
						
					PesoNuevo=CalcularPeso(lstEnemigosCercanos,i,j,NumFilas,NumCol);
			
					if(PesoNuevo>PesoMaximo)
					{
						PesoMaximo=PesoNuevo;
						PosNuevaX=i;
						PosNuevaY=j;
					}
				}
				
			(NodoAuxAliados->ObtenerDato()).AsignarAccion(DEFENSA);
			(NodoAuxAliados->ObtenerDato()).AsignarPosicionAccionX(PosNuevaX);
			(NodoAuxAliados->ObtenerDato()).AsignarPosicionAccionY(PosNuevaY);
				
			NodoAuxAliados=NodoAuxAliados->ObtenerSiguiente();
		}					
	}
}

#endif
