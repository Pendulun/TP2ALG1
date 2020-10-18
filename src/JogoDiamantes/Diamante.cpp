#include "Diamante.hpp"

namespace JogoDiamantes{
	Diamante::Diamante(unsigned int peso){
		this->peso = peso;
	}

	unsigned int Diamante::getPeso(){
		return this->peso;
	}

	void Diamante::setPeso(unsigned int novoPeso){
		this->peso = novoPeso;
	}
}