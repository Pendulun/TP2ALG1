#include "Ourive.hpp"


namespace JogoDiamantes{

	Ourive::~Ourive(){
		for(auto iteradorColecao=(*this->colecaoDiamantes).begin();
			iteradorColecao!=(*this->colecaoDiamantes).end();
			iteradorColecao++){
			delete *iteradorColecao;
		}
		delete[] this->colecaoDiamantes;
	}

	void Ourive::criaColecao(std::string arqEntrada){
		std::fstream fs;
		fs.open(arqEntrada, std::fstream::in);
		if(fs.is_open()){
	  		unsigned int K=0;
	  		fs>>K;
	  		this->tamColecao = K;
	  		this->colecaoDiamantes = new std::list<Diamante*>[this->tamColecao];
	  		unsigned int peso=0;
	  		for(unsigned int linha=0;linha<this->tamColecao;linha++){
	  				fs>>peso;
	  				(*this->colecaoDiamantes).push_back(new Diamante(peso));
	  		}
	  		fs.close();
 		 }else{
    		std::cout<< "Erro ao abrir o arquivo - confira o local e nome do arquivo"<<std::endl;
    		fs.close();
    		system("PAUSE");
  		}
	}

	unsigned int Ourive::forcaBruta(){
		while((*this->colecaoDiamantes).size()>1){
			//Acha os dois maiores
			unsigned int maiorPeso=0,segundoPeso=0,indexMaior=0,indexSegundo=0,count=0,diferenca=0;
			bool isEqual=areEqual();
			for(auto elemento=(*this->colecaoDiamantes).begin();
				elemento!=(*this->colecaoDiamantes).end();
				elemento++){

				if((*elemento)->getPeso()>maiorPeso){
					segundoPeso=maiorPeso;
					indexSegundo=indexMaior;
					maiorPeso=(*elemento)->getPeso();
					indexMaior=count;
					count++;
					continue;
				}
				if(isEqual){
					segundoPeso=(*elemento)->getPeso();
					indexSegundo=count;
					break;
				}else{
					if((*elemento)->getPeso()>segundoPeso && (*elemento)->getPeso()!=maiorPeso){
						segundoPeso=(*elemento)->getPeso();
						indexSegundo=count;
					}
				}
				count++;

			}
			//Faz a diferença
			auto maior = (*this->colecaoDiamantes).begin();
			auto segundo = (*this->colecaoDiamantes).begin();
			std::advance(maior,indexMaior);
			std::advance(segundo,indexSegundo);
			if(isEqual){
				Diamante* maiorErase = (*maior);
				Diamante* segundoErase = (*segundo);
				(*this->colecaoDiamantes).erase(maior);
				(*this->colecaoDiamantes).erase(segundo);
				delete maiorErase;
				delete segundoErase;
			}else{
				Diamante* segundoErase = (*segundo);
				diferenca = (*maior)->getPeso()-(*segundo)->getPeso();
				(*maior)->setPeso(diferenca);
				(*this->colecaoDiamantes).erase(segundo);
				delete segundoErase;
			}
		}

		//Retorna o resultado
		if((*this->colecaoDiamantes).size()==1){
			auto diamanteFinal = (*this->colecaoDiamantes).begin();
			return (*diamanteFinal)->getPeso();
		}else{
			return 0;
		}
	}

	//Se todos os pesos na coleção são iguais
	bool Ourive::areEqual(){
		auto primeiroElemento = (*this->colecaoDiamantes).begin();
		auto outrosElementos=(*this->colecaoDiamantes).begin();
		outrosElementos++;
		for(outrosElementos;
			outrosElementos!=(*this->colecaoDiamantes).end();
			outrosElementos++){
			if((*primeiroElemento)->getPeso()!=(*outrosElementos)->getPeso()){
				return false;
			}
		}
		return true;
	}

	void Ourive::imprimeColecao(){
		unsigned int count=0;
		for(auto iterador=(*this->colecaoDiamantes).begin();
			iterador!=(*this->colecaoDiamantes).end();
			iterador++){
			std::cout<<"Elemento: "<<count<<" Peso: "<<(*iterador)->getPeso()<<std::endl;
			count++;
		}
	}

	unsigned int Ourive::getPesoAt(unsigned int index){
		auto iterador=(*this->colecaoDiamantes).begin();
		std::advance(iterador,index);
		return (*iterador)->getPeso();
	}

	Diamante* Ourive::getDiamanteAt(unsigned int index){
		auto iterador=(*this->colecaoDiamantes).begin();
		std::advance(iterador,index);
		return (*iterador);
	}
}