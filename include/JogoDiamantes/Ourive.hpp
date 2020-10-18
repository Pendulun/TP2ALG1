#ifndef OURIVE_H
#define OURIVE_H
#include <fstream>
#include <string>
#include <iostream>
#include "Diamante.hpp"
namespace JogoDiamantes{

	class Ourive{
	private:
		Diamante** colecaoDiamantes=nullptr;
		unsigned int tamColecao=0;
	public:
		void criaColecao(std::string arqEntrada);
		void brutaForca();
		~Ourive();
	};
}
#endif