#ifndef OURIVE_H
#define OURIVE_H
#include <fstream>
#include <string>
#include <iostream>
#include <iterator>
#include <list>
#include <stdlib.h>
#include "Diamante.hpp"
namespace JogoDiamantes{

	class Ourive{
	private:
		std::list<Diamante*>* colecaoDiamantes=nullptr;
		unsigned int tamColecao=0;
		void imprimeColecao();
		unsigned int getPesoAt(unsigned int index);
		Diamante* getDiamanteAt(unsigned int index);
		bool areEqual();
	public:
		void criaColecao(std::string arqEntrada);
		unsigned int forcaBruta();
		~Ourive();
	};
}
#endif