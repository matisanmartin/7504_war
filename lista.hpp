#ifndef LISTA_H
#define LISTA_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "soldado.hpp"
#include "nodo.hpp"
#include "common.hpp"

#define SEP_ESPACIO " "

using namespace std;

#define SEPARADOR "-->"
#define FIN_DE_LISTA "NULL"


template <typename TipoLista>
class Lista
{
	private:
		Nodo<TipoLista> *ComienzoLista;
		Nodo<TipoLista> *NodoActual;
		bool Vacia();
		int Longitud;
			
	public:
		Lista();
		Lista(const Lista & l);
		void Insertar(const TipoLista &dato);
		void Mostrar();
		Nodo<TipoLista> * ObtenerComienzoLista() const;
		int ObtenerCantidadElementos() const;
		void AsignarComienzoLista(Nodo<TipoLista> * nodo);
		void AsignarLongitud(int Valor);
		~Lista();	
	
};

template <typename TipoLista>
bool Lista<TipoLista>::Vacia()
{
	return (this->ComienzoLista == NULL);
}

template <typename TipoLista>
Lista<TipoLista>::Lista()
{
	this->ComienzoLista=NULL;
	this->NodoActual=NULL;
}

template <typename TipoLista>
Lista<TipoLista>::Lista(const Lista & l)
{
	/*Constructor por copia
	Pre: debe existir la lista que recibe
	Pos: crea una lista idéntica a la pasada por argumento
	*/

	Nodo<TipoLista> * Aux=l.ComienzoLista, *prev = NULL;
	this->ComienzoLista=NULL;
	while(Aux != NULL)
	{
		// Ni la lista ni los nodos deben conocer absolutamente nada de los soldados!
		this->NodoActual=new Nodo<TipoLista>(Aux->ObtenerDato());
		if(this->ComienzoLista == NULL)
		this->ComienzoLista = this->NodoActual;
		if(prev != NULL)
		prev->Sig = this->NodoActual;
		Aux=Aux->Sig;
		prev = this->NodoActual;
	}
	this->NodoActual = this->ComienzoLista;
}


template <typename TipoLista>
void Lista<TipoLista>::Insertar(const TipoLista &dato)						
{
	//debe cargarse un dato previamente para esta prueba
	Nodo<TipoLista> *nuevo=new Nodo<TipoLista>(dato);
	
	if(Vacia())
	{			
		this->ComienzoLista=nuevo;
	}
	else
	{
		this->NodoActual->Sig=nuevo;
	}
	this->NodoActual=nuevo;
}
	
template <typename TipoLista>
void Lista<TipoLista>::Mostrar()
{				
	Nodo<TipoLista> *aux= this->ComienzoLista;
	
	while(aux)
	{
		(aux->ObtenerDato()).Mostrar();
		aux=aux->Sig;
	}
}

template <typename TipoLista>
Nodo<TipoLista> * Lista<TipoLista>::ObtenerComienzoLista() const
{
	return this->ComienzoLista;
}

template <typename TipoLista>
void Lista<TipoLista>::AsignarComienzoLista(Nodo<TipoLista> * nodo)
{
	this->ComienzoLista=nodo;
}

template <typename TipoLista>
ostream& operator<<(ostream &os, Nodo<TipoLista> &nodo)
{
	os<<(nodo.ObtenerDato()).ObtenerNombre()<<SEP_ESPACIO<<(nodo.ObtenerDato()).ObtenerEnergia()<<SEP_ESPACIO
	<<(nodo.ObtenerDato()).ObtenerPosicionX()<<SEP_ESPACIO<<(nodo.ObtenerDato()).ObtenerPosicionY()<<endl;
	return os;
}

template <typename TipoLista>
Lista<TipoLista>& operator+(Lista<TipoLista> & lstInicial, Lista<TipoLista> & lstFinal) 
{
	Nodo<TipoLista> *aux=lstFinal.ObtenerComienzoLista();

	while(aux)
	{
		lstInicial.Insertar(aux->ObtenerDato());
		aux=aux->ObtenerSiguiente();
	}		
	return lstInicial;
}


template <typename TipoLista>
void Lista<TipoLista>::AsignarLongitud(int Valor)
{
	this->Longitud=Valor;	
}
template <typename TipoLista>
int Lista<TipoLista>::ObtenerCantidadElementos() const
{
	Nodo<TipoLista> *aux=this->ComienzoLista;
	int Contador=0;
	
	while(aux)
	{
		Contador++;
		aux=aux->Sig;
	}
	return Contador;
	
	//return this->Longitud;
}


template <typename TipoLista>
Lista<TipoLista>::~Lista()
{
	if(this->ComienzoLista)
	{
		Nodo<TipoLista> *Aux=this->ComienzoLista;
		while (Aux)
		{
			this->ComienzoLista=Aux->ObtenerSiguiente();
			delete Aux;
			Aux=this->ComienzoLista;
		}
	}	
}

#endif

