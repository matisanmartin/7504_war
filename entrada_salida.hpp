#ifndef ENTRADA_SALIDA_H
#define ENTRADA_SALIDA_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "soldado.hpp"
#include "lista.hpp"
#include "nodo.hpp"
#include "common.hpp"

template <typename TipoLista>
StatusT LeerEntrada(long int & EnergiaMaxima, long int & TurnoActual,long int & MaxTurnos, long int & InfluenciaGranadaX,long int & InfluenciaGranadaY, long int & NumFilas,long int & NumCol, istream * FlujoEntrada, Lista<TipoLista> & lstAliados, Lista<TipoLista> & lstEnemigos)
{	

	long int Energia;
	
	(*FlujoEntrada)>>TurnoActual;
	
	(*FlujoEntrada)>>MaxTurnos;
	if((TurnoActual>MaxTurnos)||(TurnoActual<0)||(MaxTurnos<0))
		return ERROR_NUMERO_TURNO;
	
	(*FlujoEntrada)>>NumFilas;
	
	(*FlujoEntrada)>>NumCol;
	
	if(NumFilas<=0 || NumCol<=0)
		return ERROR_TERRITORIO_INVALIDO;
		
	(*FlujoEntrada)>>InfluenciaGranadaX;	

	(*FlujoEntrada)>>InfluenciaGranadaY;
	
	(*FlujoEntrada)>>EnergiaMaxima;
	
	if(!TurnoActual) /*Turno 0*/
	{	
			string line;
			
			int Contador=1;
	
			while(getline((*FlujoEntrada),line))
			{	
				stringstream LineStream(line);
				string Nombre;
	
				while(LineStream>>Nombre)
				{ 		
					
					long int InfluenciaX,InfluenciaY;
			
					LineStream>>Energia;
					if(Energia>EnergiaMaxima)
						return ERROR_ENERGIA;
		
					LineStream>>InfluenciaY;
					LineStream>>InfluenciaX;
					if((InfluenciaX<0)||(InfluenciaY<0))
						return ERROR_INFLUENCIA;
		
					if(Energia>0)
					{
						Soldado SoldadoAuxiliar(Energia,Nombre,InfluenciaX,InfluenciaY);
		
						if(ValidarNombreRepetido(lstAliados,SoldadoAuxiliar.ObtenerNombre())==false)
						{
							lstAliados.Insertar(SoldadoAuxiliar);
							lstAliados.AsignarLongitud(Contador);
							Contador++;
						}
						else					
							return ERROR_NOMBRE_REPETIDO;	
					}
				}
			}
	
		lstEnemigos.AsignarComienzoLista(NULL);
		return OK;
	}
	else
	{
		if(TurnoActual>0)
		{
			
			string line;
			int contador=-1;
			int ContadorAliados=1;
			int ContadorEnemigos=1;
			
			while(getline((*FlujoEntrada),line))
			{	
				if(line=="")
					contador++;
									
				stringstream LineStream(line);
				string Nombre;	
				while(LineStream>>Nombre)
				{ 				
					long int InfluenciaX,InfluenciaY;
					long int PosicionX,PosicionY;
			
					LineStream>>Energia;
					if(Energia>EnergiaMaxima)
						return ERROR_ENERGIA;
					
					LineStream>>InfluenciaY;			
					LineStream>>InfluenciaX;
					if((InfluenciaX<0)||(InfluenciaY<0))
						return ERROR_INFLUENCIA;

					LineStream>>PosicionX;				
					LineStream>>PosicionY;
					if((PosicionX>=NumFilas)||(PosicionX<0)||(PosicionY>=NumCol)||(PosicionY<0))
						return ERROR_POSICION_INVALIDA;

					if(Energia>0)
					{
						Soldado SoldadoAuxiliar(Energia,Nombre,InfluenciaX,
												InfluenciaY,PosicionX,PosicionY);										
					
						
						if(((ValidarNombreRepetido(lstAliados,SoldadoAuxiliar.ObtenerNombre()))==false)&&
							((ValidarNombreRepetido(lstEnemigos,SoldadoAuxiliar.ObtenerNombre()))==false))
						{
							if(contador==2)
							{
								lstEnemigos.Insertar(SoldadoAuxiliar);
								lstEnemigos.AsignarLongitud(ContadorEnemigos);
								ContadorEnemigos++;
							}
							else if(contador==1)
							{
								lstAliados.Insertar(SoldadoAuxiliar);	
								lstAliados.AsignarLongitud(ContadorAliados);
								ContadorAliados++;
							}
						}
						else
							return ERROR_NOMBRE_REPETIDO;
					}
				}
			}
		}
	}
	return OK;
}

template <typename TipoLista>
bool ValidarNombreRepetido(const Lista<TipoLista> & lst, string Nombre)
{
	Nodo<TipoLista> *aux=lst.ObtenerComienzoLista();
	
	if(!aux)
		return false;
	else
	{
		while(aux)
		{
			if((aux->ObtenerDato()).ObtenerNombre()==Nombre)
				return true;
			
			aux=aux->ObtenerSiguiente();
		}
	}
	return false;
}

template <typename TipoLista>			 
void PosicionarSoldados(Lista<TipoLista> & lst, int DimX, int DimY)
{
	srand(time(NULL)); 
	Nodo<TipoLista> *aux=lst.ObtenerComienzoLista();
	
	while(aux)
	{
		(aux->ObtenerDato()).Posicionar(DimX,DimY);
		aux=aux->ObtenerSiguiente();
	}
}


template <typename TipoLista>
StatusT GuardarSalida(ostream * FlujoSalida, Lista<TipoLista> & lst,int Turno)
{
	Nodo<TipoLista> *aux= lst.ObtenerComienzoLista();

	if(!Turno)
	{
	
		while(aux)
		{
			cerr<<"196"<<endl;
			(*FlujoSalida)<<(aux->ObtenerDato()).ObtenerNombre()<<" ";
			(*FlujoSalida)<<(aux->ObtenerDato()).ObtenerEnergia()<<" ";
			(*FlujoSalida)<<(aux->ObtenerDato()).ObtenerInfluenciaY()<<" ";		
			(*FlujoSalida)<<(aux->ObtenerDato()).ObtenerInfluenciaX()<<" ";
			(*FlujoSalida)<<(aux->ObtenerDato()).ObtenerPosicionX()<<" ";	
			(*FlujoSalida)<<(aux->ObtenerDato()).ObtenerPosicionY()<<endl;	

			aux=aux->ObtenerSiguiente();
		}
	}
	else
	{	while(aux)
		{
			cerr<<"210"<<endl;
			(*FlujoSalida)<<(aux->ObtenerDato()).ObtenerNombre()<<" ";		
			(*FlujoSalida)<<(aux->ObtenerDato()).ObtenerEnergia()<<" ";
			(*FlujoSalida)<<(aux->ObtenerDato()).ObtenerInfluenciaY()<<" ";
			(*FlujoSalida)<<(aux->ObtenerDato()).ObtenerInfluenciaX()<<" ";	
			(*FlujoSalida)<<(aux->ObtenerDato()).ObtenerPosicionX()<<" ";	
			(*FlujoSalida)<<(aux->ObtenerDato()).ObtenerPosicionY()<<" ";	
			(*FlujoSalida)<<(aux->ObtenerDato()).ObtenerAccion()<<" ";
			(*FlujoSalida)<<(aux->ObtenerDato()).ObtenerPosicionAccionX()<<" ";
			(*FlujoSalida)<<(aux->ObtenerDato()).ObtenerPosicionAccionY()<<endl;
			

			aux=aux->ObtenerSiguiente();
		}
		
	
	}
	

	
	return OK;
}

#endif
