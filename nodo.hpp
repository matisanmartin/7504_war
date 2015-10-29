#ifndef NODO_H
#define NODO_H

#include <cstdlib>
#include <iostream>
#include "soldado.hpp"
#include "common.hpp"
#include "lista.hpp"

template <typename TipoNodo>
class Nodo
{
	private:
		TipoNodo Dato;
		Nodo<TipoNodo> *Sig;
	public:
		Nodo();
		Nodo(const TipoNodo & dato);
		Nodo<TipoNodo> * ObtenerSiguiente() const;
		TipoNodo & ObtenerDato();
		~Nodo();
		template <typename TipoLista>
		friend class Lista;
};

template <typename TipoNodo>
Nodo<TipoNodo>::Nodo()
{
	this->Dato=TipoNodo();
	this->Sig=NULL;
}

template <typename TipoNodo>
Nodo<TipoNodo>::Nodo(const TipoNodo & dato)
{
	this->Dato=TipoNodo(dato);
	this->Sig=NULL;
}

template <typename TipoNodo>
Nodo<TipoNodo> * Nodo<TipoNodo>::ObtenerSiguiente() const
{
	return this->Sig;
}

template <typename TipoNodo>
TipoNodo & Nodo<TipoNodo>::ObtenerDato()
{
	return this->Dato;
}

template <typename TipoNodo>
Nodo<TipoNodo>::~Nodo(){}


#endif //NODO_H
