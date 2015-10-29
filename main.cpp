#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <sstream>
#include "soldado.hpp"
#include "lista.hpp"
#include "nodo.hpp"
#include "entrada_salida.hpp"
#include "common.hpp"
#include "cmdline.hpp"
#include "estrategia_base.hpp"
#include "estrategia_evasiva.hpp"
#include "estrategia_agresiva.hpp"
#include "estrategia_test.hpp"

using namespace std;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_mode(string const &);
static void opt_name(string const &);

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "m", "mode", "-", opt_mode, OPT_DEFAULT},
	{0,"n","name",NULL,opt_name,OPT_DEFAULT},
	{0, },
};

					 
static istream *iss = 0;
static ostream *oss = 0;
static fstream ifs;
static fstream ofs;
static char modo;

static void
opt_input(string const &arg)
{
	if (arg == "-") {
		iss = &cin;
	} else {
		ifs.open(arg.c_str(), ios::in);
		iss = &ifs;
	}

	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_output(string const &arg)
{
	if (arg == "-") {
		oss = &cout;
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_mode(string const &arg)
{
		if(arg=="-")
			modo=DEFAULT;
		else if(arg==MODO_EVASIVO)
			modo=EVASIVO;
		else if(arg==MODO_DEFAULT)
			modo=DEFAULT;
		else if(arg==MODO_AGRESIVO)
			modo=AGRESIVO;
		else
		{
			cerr<<MSJ_MODO_INCOMPATIBLE<<endl;
			exit(1);
		}
}

static void
opt_name(string const &arg)
{
		if(!oss)
		{
			oss=&cout;		
			(*oss)<<NOMBRE_EQUIPO<<endl;
		}
		else
			(*oss)<<NOMBRE_EQUIPO<<endl;
				
		exit(1);		
}


	

		

int main(int argc, char *argv[])
{
	long int NumColumnas,NumFilas;
	Lista<Soldado> lstAliados,lstEnemigos;
	
	cmdline cmdl(options);
	cmdl.parse(argc, argv);
	
	long int MaxTurnos;
	long int TurnoActual;
	long int InfluenciaGranadaX;
	long int InfluenciaGranadaY;
	long int EnergiaMaxima;
		
	if(LeerEntrada(EnergiaMaxima,TurnoActual,MaxTurnos,InfluenciaGranadaX,InfluenciaGranadaY,
						NumFilas,NumColumnas,iss,lstAliados,lstEnemigos)!=OK)
	{
			cout<<MSJ_ERROR_ABRIR_ARCHIVO<<endl;
			return EXIT_FAILURE;
	}

	cerr<<137<<endl;
	
	if (!TurnoActual)
	{
		PosicionarSoldados(lstAliados,NumFilas,NumColumnas);
		cerr<<143<<endl;
	}	
	else
	{
		cerr<<146<<endl;
		TestEstrategia<Soldado> Test;
		if(modo==DEFAULT)
		{
			cerr<<150<<endl;
			AsignarAccionesDefault(lstAliados,lstEnemigos,TurnoActual,MaxTurnos,EnergiaMaxima);
			cerr<<152<<endl;
			Test.AsignarEstrategia(EVASIVO);
			cerr<<154<<endl;
			Test.RealizarEstrategia(lstAliados,lstEnemigos,InfluenciaGranadaY,InfluenciaGranadaX,NumFilas,
			 						NumColumnas,TurnoActual,MaxTurnos,EnergiaMaxima);
			cerr<<157<<endl;					
			Test.AsignarEstrategia(AGRESIVO);
			cerr<<159<<endl;
			Test.RealizarEstrategia (lstAliados,lstEnemigos,InfluenciaGranadaY,InfluenciaGranadaX,NumFilas,
									NumColumnas,TurnoActual,MaxTurnos,EnergiaMaxima);	
			cerr<<162<<endl;		
		}
		else
		{
			Test.AsignarEstrategia(modo);
			Test.RealizarEstrategia (lstAliados,lstEnemigos,InfluenciaGranadaX,InfluenciaGranadaY,NumFilas,
								NumColumnas,TurnoActual,MaxTurnos,EnergiaMaxima);
		}	
	}
	
	
	if(GuardarSalida(oss,lstAliados,TurnoActual)!=OK)
	{
		cout<<MSJ_ERROR_ABRIR_ARCHIVO<<endl;
		return EXIT_FAILURE;
	}
		
	return EXIT_SUCCESS;
}
