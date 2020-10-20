#ifndef OURIVE_H
#define OURIVE_H
#include <fstream>
#include <string>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
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
		unsigned int somaPesos();
		unsigned int max(unsigned int peso1, unsigned int peso2);
		unsigned int subsetSum();
	public:
		void criaColecao(std::string arqEntrada);
		unsigned int naoDinamico();
		unsigned int dinamico();
		~Ourive();
	};
}
#endif