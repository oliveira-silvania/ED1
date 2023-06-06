//Silvania Alves Oliveira
#include <bits/stdc++.h>
#include "listaCDE.h"
#include "pilha.h"
#include "carta.h"
#include "lista.h"
using namespace std;

struct jogador{
	int id;
};

int main(){
	carta aux;
	int numPartidas, numJog;
	cin>>numPartidas;
	while(numPartidas--){ //primeira entrada-numero de rodadas
		int numPartidasAux;
		numPartidasAux=numPartidas;
		cin>>numJog; 
		listCDE<jogador> jogo;
		Stack<carta> monte, lixo;
		Lista jog[numJog];
		int continua=numJog-1;
		while(continua--){
			for(int c=0; c<104; c++){ //colocar as cartas na pilha monte
				cin>>aux.valor>>aux.naipe;
				monte.Push(aux);
			}
			for(int j=0; j<numJog; j++){ //destribuir as cartas para cada jogador
				for(int k=0; k<5; k++){ 
					jog[j].InsertL(monte.Top());
					monte.Pop();
				}
			}
			for(int i=0; i<numJog; i++){ //preenchedo a lista circular
				jogador posicao;
				posicao.id = i;
				jogo.InsertNext(posicao);
			}
			jogo.Begin(); //comecando com o primeiro jogador
			int Pont;
			Pont=jogo.ItRet().id; //vez do jogador
			if(lixo.Empty()){ //vai jogar a primeira carta da partida
				lixo.Push(jog[Pont].primeiraCarta());
				jogo.Itpp();
			}
			
			bool zero=true;
			while(zero){ //ninguem chegou a zero
				Pont=jogo.ItRet().id; //vez do jogador
				bool ok=false;
				int sentido=1; //1 horario ; -1 anti horario
				carta aux;
				carta inverte;
				aux=jog[Pont].Buscar(lixo.Top());
				if(aux.valor=='0'){//Jog nao tem a carta igual do lixo; vai ter que comprar carta no monte
					if(monte.Top().valor==lixo.Top().valor or monte.Top().naipe==lixo.Top().naipe){//a carta do monte e igual do lixo
						ok=true;
					}
					else{ //a carta do monte nao eh igual do lixo
						ok=false;
					}
				}
				else{//carta comprada eh diferente do topo do lixo; proximo jog joga
					if(sentido==1) jogo.Itpp();
					else jogo.Itmm();
				}  
				if(ok){ //tem carta para jogar
					if(aux.valor=='Q'){//trocar de sentido; 1-horario; -1 anti-horario
						sentido=sentido*(-1);
						if(sentido==1) jogo.Itpp();
						else jogo.Itmm();
					}
					if(sentido==1){ //jogo ta no sentido horario
						if(aux.valor=='A'){//proximo jog não joga
							jogo.Itpp();
							jogo.Itpp();
						}
						else{
							
							if(aux.valor=='7'){//proximo jog compra 2 cartas
								jogo.Itpp();
								jog[Pont].InsertL(monte.Top()); //compra 1
								monte.Pop();
								jog[Pont].InsertL(monte.Top()); //compra 2
								monte.Pop();
							}
							else{
								if(aux.valor=='9'){//o jog anterior compra 3 cartas
									jogo.Itmm();
									jog[Pont].InsertL(monte.Top());//compra 1
									monte.Pop();
									jog[Pont].InsertL(monte.Top());//compra 2
									monte.Pop();
									jog[Pont].InsertL(monte.Top());//compra 3
									monte.Pop();
								}
							}
						}
					}
					if(sentido==-1){//jogo ta no sentido anti horario
						if(aux.valor=='A'){//proximo jog não jogar
							jogo.Itmm();
							jogo.Itmm();
						}
						else{
							if(aux.valor=='7'){//proximo jog compra 2 cartas
								jogo.Itmm();
								jog[Pont].InsertL(monte.Top()); //compra 1
								monte.Pop();
								jog[Pont].InsertL(monte.Top()); //compra 2
								monte.Pop();
							}
							else{
								if(aux.valor=='9'){//o jog anterior compra 3 cartas
									jogo.Itpp();
									jog[Pont].InsertL(monte.Top());//compra 1
									monte.Pop();
									jog[Pont].InsertL(monte.Top());//compra 2
									monte.Pop();
									jog[Pont].InsertL(monte.Top());//compra 3
									monte.Pop();
								}
							}
						}
					}
					lixo.Push(aux);
				}//fim do if ok		
						 
				if(jog[Pont].SizeL()==0) zero=false;//verificar se algum jogador tem size==0	
				cout<<"ninguem chegou a zero"<<endl;
				
				if(monte.Size()==0){//monte ta vazio, levar todas as carta do lixo menos o topo para o monte
					inverte=lixo.Top();
					lixo.Pop();
					while(!lixo.Empty()){
						monte.Push(lixo.Top());
						lixo.Pop();
					}
					lixo.Push(inverte);
				}
			}//fim do zero; fim da partida
			
			//verificar quem perdeu
			int pontuacao=0, pontos=0;
			jogador perdedor;
			jogo.Begin();
			for(int p=0; p<jogo.Size(); p++){
				int aux;
				aux=jogo.ItRet().id;
				pontos=jog[aux].SomaPontos();
				if(pontos>pontuacao){
					perdedor.id=aux;
					pontuacao=pontos;
				}
				jogo.Itpp();
			}
			jogo.Erase(perdedor);
			while(!lixo.Empty()) lixo.Pop();
			while(!monte.Empty()) monte.Pop();
		}
		//quem ganhou a rodada???
		cout<<"partida: "<<numPartidasAux<<" vencedor"<<jogo.ItRet().id<<endl;
	}
}
/*
1
2
A0 B0 C0 D0 E0 F0 G0 H0 I0 J0 K0 L0 M0 A1 B1 C1 D1 E1 F1 G1 H1 I1 J1 K1 L1 M1 
A2 B2 C2 D2 E2 F2 G2 H2 I2 J2 K2 L2 M2 A3 B3 C3 D3 E3 F3 G3 H3 I3 J3 K3 L3 M3 
A0 B0 C0 D0 E0 F0 G0 H0 I0 J0 K0 L0 M0 A1 B1 C1 D1 E1 F1 G1 H1 I1 J1 K1 L1 M1 
A2 B2 C2 D2 E2 F2 G2 H2 I2 J2 K2 L2 M2 A3 B3 C3 D3 E3 F3 G3 H3 I3 J3 K3 L3 M3 
*/
