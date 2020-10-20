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
	  		fs>>this->tamColecao;
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

	unsigned int Ourive::naoDinamico(){
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

	unsigned int Ourive::dinamico(){
		return subsetSum();
	}

	unsigned int Ourive::subsetSum(){
		unsigned int somaMaisProxima;
		unsigned int soma = somaPesos();
		unsigned int nColunas = (soma/2)+1;
		unsigned int** M = new unsigned int*[this->tamColecao+1];
		for(unsigned int i =0;i<this->tamColecao+1;i++){
			M[i] = new unsigned int[nColunas];
		}

		for(unsigned int i=0;i<nColunas;i++){
			M[0][i]=0;
		}

		for(unsigned int i=1;i<this->tamColecao+1;i++){
			for(unsigned int w=0;w<nColunas;w++){
				unsigned int i_1 = i-1;
				unsigned int pesoDiamante = getPesoAt(i_1);
				if(w<pesoDiamante){
					M[i][w]=M[i_1][w];
				}else{
					M[i][w]=max(M[i_1][w], pesoDiamante+M[i_1][w-pesoDiamante]);
				}
			}
		}

		somaMaisProxima = M[this->tamColecao][soma/2];
		for(unsigned int i = 0;i<this->tamColecao+1;i++){
			delete[] M[i];
		}
		delete[] M;
		return (soma-somaMaisProxima)-somaMaisProxima;
	}

	unsigned int Ourive::max(unsigned int peso1, unsigned int peso2){
		if(peso1>peso2){
			return peso1;
		}else{
			return peso2;
		}
	}

	unsigned int Ourive::somaPesos(){
		unsigned int soma=0;
		for(auto iterador=(*this->colecaoDiamantes).begin();
			iterador!=(*this->colecaoDiamantes).end();
			iterador++){
			soma+=(*iterador)->getPeso();
		}
		return soma;
	}

	unsigned int Ourive::getPesoAt(unsigned int index){
		auto iterador=(*this->colecaoDiamantes).begin();
		std::advance(iterador,index);
		return (*iterador)->getPeso();
	}
}