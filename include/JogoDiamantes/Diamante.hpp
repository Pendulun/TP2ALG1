#ifndef DIAMANTE_H
#define DIAMANTE_H

namespace JogoDiamantes{
	class Diamante{
	private:
		unsigned int peso;
	public:
		Diamante(unsigned int peso);
		unsigned int getPeso();
		void setPeso(unsigned int novoPeso);
	};
}

#endif