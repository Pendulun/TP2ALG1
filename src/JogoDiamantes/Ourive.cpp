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
	  				std::cout<<"Novo Peso: "<<peso<<std::endl;
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
		while((*this->colecaoDiamantes).size()>1){
			std::cout<<"Entrou While"<<std::endl;
			auto primeiro = (*this->colecaoDiamantes).begin();
			unsigned int count=0;
			//Para cada elemento
			for(auto elemento=(*this->colecaoDiamantes).begin();
			elemento!=(*this->colecaoDiamantes).end();
			elemento++){
				std::cout<<"Entrou For"<<std::endl;
				unsigned int minDiferenca=NULL;
				unsigned int minIndex=0;
				auto elementosAcima = std::next((*this->colecaoDiamantes).begin(),count); //A partir do próximo elemento
				std::list<Diamante*>::iterator elementoPar;
				std::cout<<"Elemento Num:"<<count<<" com peso: "<< (*elemento)->getPeso()<<std::endl;
				unsigned int index=0;
				while(elementosAcima!=(*this->colecaoDiamantes).end()){
					std::cout<<"Entrou While 2"<<std::endl;
					int diferenca=0;
					diferenca=(*elemento)->getPeso()-(*elementosAcima)->getPeso();
					if(diferenca<0){
						diferenca = diferenca*(-1);
					}
					if(minDiferenca==NULL || diferenca<minDiferenca){
						minDiferenca=diferenca;
						minIndex=count+index;
						elementoPar=elementosAcima;
					}
					index++;
					elementosAcima = std::next(elementosAcima);
				}
				imprimeColecao();
				std::cout<<"Menor diferenca:"<<minDiferenca<<" Index: "<<minIndex<<" de peso:";
				std::cout<<getPesoAt(minIndex)<<std::endl;
				if(minDiferenca==0){
					Diamante* elementoDel = (*elemento);
					Diamante* elementoParDel = (*elementoPar);
					(*this->colecaoDiamantes).erase(elemento);
					(*this->colecaoDiamantes).erase(elementoPar);
					delete elementoDel;
					delete elementoParDel;
				}else if(((*elemento)->getPeso()-(*elementoPar)->getPeso())>0){
					Diamante* elementoParDel = (*elementoPar);
					(*elemento)->setPeso(minDiferenca);
					(*this->colecaoDiamantes).erase(elementoPar);
					delete elementoParDel;
				}else if(((*elemento)->getPeso()-(*elementoPar)->getPeso())<0){
					Diamante* elementoDel = (*elemento);
					(*elementoPar)->setPeso(minDiferenca);
					(*this->colecaoDiamantes).erase(elemento);
					delete elementoDel;
				}
				imprimeColecao();
				count++;
			}
		}
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