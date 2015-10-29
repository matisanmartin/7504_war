#include <iostream>
#include <cstdlib>
#include <string>
#include "soldado.hpp"

Soldado::Soldado(){}

Soldado::Soldado(int NuevaEnergia, const string & NuevoNombre, int InfX, int InfY, int PosicionX, int PosicionY)
{
	/*	
		Constructor Parametrizado
		PRE: Ninguna
	 	POS: Crea un soldado con los parametros pasados
	*/
	  
	this->Nombre=NuevoNombre;
	this->Energia=NuevaEnergia;
	this->InfluenciaX=InfX;
	this->InfluenciaY=InfY;
	this->PosicionX=PosicionX;
	this->PosicionY=PosicionY;
	
}

Soldado::Soldado(const Soldado & s)
{
	/*Constructor Copia
		PRE: Ninguna
	  	POS: Crea un soldado identico al pasado por argumento*/
	  
	this->Nombre=s.Nombre;
	this->Energia=s.Energia;
	this->InfluenciaX=s.InfluenciaX;
	this->InfluenciaY=s.InfluenciaY;
	this->PosicionX=s.PosicionX;
	this->PosicionY=s.PosicionY;
}

void Soldado::Posicionar(int NumFilas, int NumColumnas)
{
	/*PRE: El soldado debe existir
	  POS: Modifica la posicion */
	  
	PosicionX=rand()%NumColumnas;
	PosicionY=rand()%NumFilas;

}


int Soldado::ObtenerEnergia() const
{
	/*Getter
		PRE: El soldado debe existir
	  	POS: Devuelve la energía*/
	  
	return this->Energia;
}

int  Soldado::ObtenerPosicionX() const
{
	/*Getter
		PRE: El soldado debe existir
	  	POS: Devuelve la fila en la que se encuentra*/
	  
	return this->PosicionX;
}

int Soldado::ObtenerPosicionY() const
{
	/*Getter
		PRE: El soldado debe existir
	  	POS: Devuelve la columna en la que se encuentra*/
	  
	return this->PosicionY;
}

int Soldado::ObtenerInfluenciaX() const
{
	/*Getter
		PRE: El soldado debe existir
	  	POS: Devuelve la influencia a nivel fila*/
	  
	return this->InfluenciaX;
}

int Soldado::ObtenerInfluenciaY() const
{
	/*Getter
		PRE: El soldado debe existir
	  	POS: Devuelve la fila en la que se encuentra*/
	  
	return this->InfluenciaY;
}

string Soldado::ObtenerNombre() const
{
	/*Getter
		PRE: El soldado debe existir
	  	POS: Devuelve el nombre del soldado*/
	  
	return this->Nombre;
}

char Soldado::ObtenerAccion() const
{
	return this->Accion;
}

int Soldado::ObtenerPosicionAccionX() const
{
	return this->PosicionAccionX;
}


int Soldado::ObtenerPosicionAccionY() const
{
	return this->PosicionAccionY;
}


void Soldado::AsignarAccion(char Accion)
{
	this->Accion=Accion;
}

void Soldado::AsignarPosicionAccionX(int PosX)
{
	this->PosicionAccionX=PosX;
}
void Soldado::AsignarPosicionAccionY(int PosY)
{
	this->PosicionAccionY=PosY;
}

void Soldado::Mostrar()
{
		cout<<this->ObtenerEnergia()<<" ";
		cout<<this->ObtenerNombre()<<" ";
		cout<<this->ObtenerInfluenciaX()<<" ";
		cout<<this->ObtenerInfluenciaY()<<" ";
		cout<<this->ObtenerPosicionX()<<" ";
		cout<<this->ObtenerPosicionY()<<endl;
}

Soldado::~Soldado()
{
	/*PRE: El soldado debe existir
	  POS: Ninguna */
}

