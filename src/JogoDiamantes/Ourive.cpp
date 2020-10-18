#include "Ourive.hpp"


namespace JogoDiamantes{

	Ourive::~Ourive(){
		for(unsigned int i=0;i<this->tamColecao;i++){
			delete this->colecaoDiamantes[i];
		}
		delete this->colecaoDiamantes;
	}

	void Ourive::criaColecao(std::string arqEntrada){
		std::fstream fs;
		fs.open(arqEntrada, std::fstream::in);
		if(fs.is_open()){
	  		unsigned int K=0;
	  		fs>>K;
	  		this->tamColecao = K;
	  		this->colecaoDiamantes = new Diamante*[this->tamColecao];
	  		unsigned int peso=0;
	  		for(unsigned int linha=0;linha<this->tamColecao;linha++){
	  				fs>>peso;
	  				std::cout<<"Novo Peso: "<<peso<<std::endl;
	  				this->colecaoDiamantes[linha]=new Diamante(peso);
	  		}
	  		fs.close();
 		 }else{
    		std::cout<< "Erro ao abrir o arquivo - confira o local e nome do arquivo"<<std::endl;
    		fs.close();
    		system("PAUSE");
  		}
	}

	void Ourive::brutaForca(){
		std::cout<<"Entrou Forca Bruta"<<std::endl;
	}
}