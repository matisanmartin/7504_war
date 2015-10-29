#ifndef SOLDADO_H
#define SOLDADO_H

#include <cstdlib>
#include <iostream>
#include <string>

typedef enum{FLAG_X,FLAG_Y}FlagT;

using namespace std;

class Soldado
{
	private:
		string Nombre;
		int Energia;
		int InfluenciaX;
		int InfluenciaY;
		int PosicionX;
		int PosicionY;
		char Accion;
		int PosicionAccionX;
		int PosicionAccionY;
	public:
		
		Soldado();
		Soldado(int Energia, const string & Nombre, int InfX, int InfY, int PosicionX=0, int PosicionY=0);
		Soldado(const Soldado &);
		void Posicionar(int DimensionX, int DimensionY);
		int ObtenerEnergia() const;
		int ObtenerPosicionX() const;
		int ObtenerPosicionY() const;
		int ObtenerInfluenciaX() const;
		int ObtenerInfluenciaY() const;
		string ObtenerNombre() const;
		char ObtenerAccion() const; 
		int ObtenerPosicionAccionX() const;
		int ObtenerPosicionAccionY() const;
		void AsignarAccion(char Accion);
		void AsignarPosicionAccionX(int PosX);
		void AsignarPosicionAccionY(int PosY);
		void Mostrar();
		~Soldado();
};


#endif

