#include "ListCDE.h"
#include "listord.h"
#include <bits/stdc++.h>//dps tem que trocar para <iostream>

struct jogador{
	int numJog;
};

using namespace std;
int main(){
	
	int J,Jaux,n,partida,vez,vezaux,sentido;
	bool continua,ok;
	carta c,caux;
	stack<carta> monte,lixo; //dps tem que trocar para a minha classe
	cin>>n; //quantidade de partidas
	
	while(n--){
		
		cin>>J;//quantidade de jogadores
		listord jgd[J];
		listCDE<jogador> jogo;
		partida=J-1;
		Jaux=J;
		
		while(partida--){
			cout<<"partida "<<partida<<endl;
			for(int i=0;i<20;i++){ //leitura das cartas em toda partida(FUNCIONANDO)
				cin>>c.valor>>c.nipe;
				monte.push(c);
			}
		
			for(int i=0;i<Jaux;i++){//entrega das quartas a cada partida (FUNCIONANDO)
				jogador posi;
				posi.numJog=i;
				jogo.insertnext(posi);
				for(int j=0;j<5;j++){
					jgd[i].insert(monte.top());
					monte.pop();
				}
			}
			jogo.begin();//sempre começa com o primeiro jogador da lista
			vez = jogo.itret().numJog; //pegando a vez do cara
			lixo.push(jgd[vez].primeiracarta()); //inicio do jogo,primeira carta a ser jogada
			sentido = 1; //sempre começando em sentido hórario
			continua = true;
			jogo.itpp(); //pois o primeiro jogadorja jogou, logo passa para o proximo
			//cout<<"quem joga primeiro" << vez<<endl;
			while(continua){
				ok = true;
				vez = jogo.itret().numJog; //proximo jogador
				//cout<<"quem jogou " << vez<<endl;
				caux = jgd[vez].buscar(lixo.top()); //irá buscar na mão do jogador para ver se tem a carta compativel com o lixo = '0'
				
				if(caux.valor == '0'){//não tem a carta que possa ser jogada
					caux = jgd[vez].buscar(monte.top());//dando maisuma chance de ele ter uma carta jogavel
					if(caux.valor == '0')ok=false; //ele não conseguiu uma carta jogavel
					else ok = true; //teve sorte poderá jogar	
				}
				
				if(ok){ //ele tem uma carta jogavel que esta guardada no 'caux'
					
					if(caux.valor =='L'){ //mudando o sentido do jogo
						sentido *= -1;
						lixo.push(caux); //colocando a carta no lixo
						if(sentido == 1)jogo.itpp();
						else jogo.itmm();
					}
					else{
						if(sentido == 1){//estamos no sentido horario
							if(caux.valor == '7'){
								jogo.itpp(); //jogando o it para o proximo jogador
								vezaux = jogo.itret().numJog;
								jogo.itmm(); //voltando o jogo para o jogador original
								
								for(int compra = 0;compra<2;compra++){ //for da penalidade da carta '7'
									jgd[vezaux].insert(monte.top());
									monte.pop();
								}
							}
							else{
								if(caux.valor == '9'){
									jogo.itmm(); //jogando para o jogador anterior
									vezaux = jogo.itret().numJog;
									jogo.itpp(); //voltando o jogo para o jogador original
									
									for(int compra = 0;compra<3;compra++){ //for da penalidade da carta '9'
										jgd[vezaux].insert(monte.top());
										monte.pop();
									}
								}
								else{
									if(caux.valor == 'A'){
										jogo.itpp(); //fazendo o proximo não jogar
									}
									else{ //apenas descarta(cartas normais)
										lixo.push(caux); //descartando no lixo
										
									}
								}
							}
							jogo.itpp();
						}
						else{ //sentido anti-horario
							
							if(caux.valor == '7'){
								jogo.itmm(); //jogando o it para o proximo jogador
								vezaux = jogo.itret().numJog;
								jogo.itpp(); //voltando o jogo para o jogador original
								
								for(int compra=0;compra<2;compra++){ //for da penalidade da carta '7'
									jgd[vezaux].insert(monte.top());
									monte.pop();
								}
							}
							else{
								if(caux.valor == '9'){
									jogo.itpp(); //jogando para o jogador anterior
									vezaux = jogo.itret().numJog;
									jogo.itmm(); //voltando o jogo para o jogador original
									
									for(int compra=0;compra<3;compra++){ //for da penalidade da carta '9'
										jgd[vezaux].insert(monte.top());
										monte.pop();
									}
								}
								else{
									if(caux.valor == 'A'){
										jogo.itmm(); //fazendo o proximo não jogar
									}
									else{ //apenas descarta(cartas normais)
										lixo.push(caux); //descartando no lixo
									}
								}
							}
							jogo.itmm();
						}
					}
				}
				if(jgd[vez].size()==0){
					//~ cout<<"ganhou a rodada: "<<vez<<endl;
					continua = false;
				} 
				
				if(monte.size() == 0){
					carta c2 = lixo.top(); //guardando a carta guia do jogo
					lixo.pop();
					while(lixo.empty()){
						monte.push(lixo.top());
						lixo.pop();
					}
					lixo.push(c2);
				}
			}
			//fim da partida

			jogador perdedor;
			int pontuacao = 0,pontos;
			for(int p=0;p<jogo.size();p++){
				int ps = jogo.itret().numJog;
				pontos = jgd[ps].calcularpontuacao();
				cout << "jogador "<< ps << " " << pontos << endl;
				if(pontos > pontuacao){
					cout<<"entrei"<<endl;
					perdedor.numJog = ps;
					pontuacao = pontos;
				}
				jogo.itpp();
			}
			cout<<"perdedor "<<perdedor.numJog<<endl;
			jogo.erase(perdedor);
			for(int i=0;i<jogo.size();i++){
				cout<<jogo.itret().numJog<<" ";
				jogo.itpp();
			}
			cout << "\n";
			Jaux--; //tirando um jogador a cada rodada
			while(!lixo.empty()) lixo.pop();
			while(!monte.empty()) monte.pop();
		} 
		cout<<"vencedor "<<jogo.itret().numJog<<endl<<endl;
		for(int i=0;i<jogo.size();i++){
			cout<<jogo.itret().numJog<<" ";
			jogo.itpp();
		}
	}
}
