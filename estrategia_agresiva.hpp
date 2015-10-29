#ifndef ESTRATEGIA_AGRESIVA_H
#define ESTRATEGIA_AGRESIVA_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "common.hpp"
#include "lista.hpp"
#include "nodo.hpp"
#include "estrategia_base.hpp"

template <typename TipoLista>
class EstrategiaAgresiva : public Estrategia<TipoLista>
{
	private:
		void Ejecutar(Lista<TipoLista> & lstAliados, Lista<TipoLista> & lstEnemigos, 
						int InfGranadaX, int InfGranadaY, int NumFilas, int NumCol, int TurnoActual, int MaximoTurno, int EnergiaInicial);
		int CalcularEnergia(int i, int j, Lista<TipoLista> Total, int CantidadEnemigos, int InfGranadaX, int InfGranadaY);
		double Danio(int i, int j, TipoLista Dato, int InfGranadaX, int InfGranadaY);
		
	public:
		EstrategiaAgresiva(): Estrategia<TipoLista>(){}
};


template <typename TipoLista>
double EstrategiaAgresiva<TipoLista>::Danio(int i, int j, TipoLista Dato, int InfGranadaX, int InfGranadaY)
{	
	int EnergiaActual=Dato.ObtenerEnergia();
	int PosX=Dato.ObtenerPosicionX();
	int PosY=Dato.ObtenerPosicionY();
				
	if(Dato.ObtenerAccion()==DEFENSA)
	{
		PosX=Dato.ObtenerPosicionAccionX();
		PosY=Dato.ObtenerPosicionAccionY();
	}
			
	if((i-PosX>InfGranadaX)||(PosX-i>InfGranadaX)||(j-PosY>InfGranadaY)||(PosY-j>InfGranadaY))
		return 0;
	
	double Distancia=sqrt((PosX-i)*(PosX-i)+(PosY-j)*(PosY-j));
	
	double AuxCuenta=(double)EnergiaActual/pow(2,Distancia);
	
	double Minimo;	
			
	if(AuxCuenta<EnergiaActual)
		Minimo=AuxCuenta;
	else
		Minimo=EnergiaActual;
	
	return ceil(Minimo);
}

template <typename TipoLista>
int EstrategiaAgresiva<TipoLista>::CalcularEnergia(int i, int j, Lista<TipoLista> Total, int CantidadEnemigos, int InfGranadaX, int InfGranadaY)
{
	Nodo<TipoLista> *aux=Total.ObtenerComienzoLista();
	
	int EnergiaAcum=0;
	
	cerr<<63<<endl;
	
	for(int k=0;k<CantidadEnemigos;k++)
	{
		EnergiaAcum+=Danio(i,j,aux->ObtenerDato(),InfGranadaX,InfGranadaY);
		aux=aux->ObtenerSiguiente();
		cerr<<69<<endl;
		cerr<<k<<" "<<CantidadEnemigos<<endl;
	}
	
	//cuando tira sigsegv no llega aca
	cerr<<71<<endl;
	while(aux)
	{
		
		EnergiaAcum-=Danio(i,j,aux->ObtenerDato(),InfGranadaX,InfGranadaY);
		aux=aux->ObtenerSiguiente();
		cerr<<78<<endl;
	}
	cerr<<80<<endl;
	
	return EnergiaAcum;
}
		
template <typename TipoLista>
void EstrategiaAgresiva<TipoLista>::Ejecutar(Lista<TipoLista> & lstAliados, Lista<TipoLista> & lstEnemigos, 
						int InfGranadaX, int InfGranadaY, int NumFilas, int NumCol, int TurnoActual, int MaximoTurno, int EnergiaInicial)
{

	cerr<<83<<endl;
	
	Nodo<TipoLista> *NodoAuxAliados=lstAliados.ObtenerComienzoLista();
	
	cerr<<87<<endl;		
	while(NodoAuxAliados)
	{
		if((NodoAuxAliados->ObtenerDato()).ObtenerAccion()==DEFENSA)
			NodoAuxAliados=NodoAuxAliados->ObtenerSiguiente();
		else
		{	
			int PosX=(NodoAuxAliados->ObtenerDato()).ObtenerPosicionX();
			int PosY=(NodoAuxAliados->ObtenerDato()).ObtenerPosicionY();
			int InfX=(NodoAuxAliados->ObtenerDato()).ObtenerInfluenciaX();
			int InfY=(NodoAuxAliados->ObtenerDato()).ObtenerInfluenciaY();
				
			Lista<TipoLista> lstEnemigosCercanos;
			Lista<TipoLista> lstAliadosCercanos;
			
			cerr<<102<<endl;
			
			BuscarCercanos(InfGranadaX,InfGranadaY,PosX,PosY,InfX,InfY,
							lstEnemigos,lstEnemigosCercanos,PRECISION_ATAQUE,false);
			
			cerr<<107<<endl;	
			BuscarCercanos(InfGranadaX,InfGranadaY,PosX,PosY,InfX,InfY,
							lstAliados,lstAliadosCercanos,PRECISION_ATAQUE,true);
			
			cerr<<111<<endl;
				
			int CantidadEnemigos=lstEnemigosCercanos.ObtenerCantidadElementos();
			cerr<<CantidadEnemigos<<"cant enemigos"<<endl;
			Lista<TipoLista> lstCercanos(lstEnemigosCercanos+lstAliadosCercanos);
	
			cerr<<116<<endl;
			
			int LimIzq,LimDer,LimSup,LimInf;

	
			ValidarLimites(NumFilas, NumCol,PosX,PosY,InfX,InfY,LimIzq,LimDer,LimSup,LimInf);
			
			cerr<<123<<endl;
	
			int EnergiaMaxima,EnergiaNueva;
	
			int PosFinalGranadaX,PosFinalGranadaY;
			
				
			for(int i=LimIzq;i<=LimDer;i++)
				for(int j=LimSup;j<=LimInf;j++)
				{
					cerr<<133<<endl;
					if((i==LimIzq)&&(j==LimSup))
					{
						cerr<<136<<endl;
						EnergiaMaxima=CalcularEnergia(i,j,lstCercanos,CantidadEnemigos,InfGranadaX,InfGranadaX);
						cerr<<138<<endl;
						PosFinalGranadaX=LimIzq;
						PosFinalGranadaY=LimSup;
					}
					cerr<<140<<endl;
					EnergiaNueva=CalcularEnergia(i,j,lstCercanos,CantidadEnemigos,InfGranadaX,InfGranadaX);
					if(EnergiaNueva>EnergiaMaxima)
					{
						EnergiaMaxima=EnergiaNueva;
						PosFinalGranadaX=i;
						PosFinalGranadaY=j;
					}
					cerr<<148<<endl;
				}
			
			cerr<<151<<endl;	
			(NodoAuxAliados->ObtenerDato()).AsignarAccion(ATAQUE);
			(NodoAuxAliados->ObtenerDato()).AsignarPosicionAccionX(PosFinalGranadaX);
			(NodoAuxAliados->ObtenerDato()).AsignarPosicionAccionY(PosFinalGranadaY);
			NodoAuxAliados=NodoAuxAliados->ObtenerSiguiente();				
		}	
	}
}

#endif
