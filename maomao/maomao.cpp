//Silvania Alves Oliveira
#include <bits/stdc++.h>
#include "listaCDE.h"
#include "pilha.h"
#include "carta.h"
#include "lista.h"
using namespace std;



int main(){
	carta aux;
	int numPartidas, numJog;
	
	cin>>numPartidas;
	while(numPartidas--){ //primeira entrada-numero de rodadas
		cin>>numJog; 
		vector<Lista> posJog(numJog+1);
		listCDE<int> Jog;
		Stack<carta> monte, lixo;
		int continua=numJog-1;
		
		while(continua--){
			for(int c=0; c<104; c++){ //colocar as cartas na pilha monte
				cin>>aux.valor>>aux.naipe;
				monte.Push(aux);
				
			}
			for(int j=1; j<=numJog; j++){ //destribuir as cartas para cada jogador
				
				for(int k=1; k<=5; k++){ 
					posJog[j].InsertL(monte.Top());
					monte.Pop();
				}
			}
			
			for(int i=1; i<=numJog; i++){
				Jog.InsertNext(i); //preenchendo a lista circular com a quant de jog
			}
			if(lixo.Empty()){ //vai jogar a primeira carta da partida
				lixo.Push(posJog[Jog.ItRet()].primeiraCarta());
				Jog.Itpp();
			}
			
			bool zero=true;
			bool ok=false;
			while(zero){ //ninguem chegou a zero
				int sentido=1; //1 horario ; -1 anti horario
				int Pont = Jog.ItRet(); //retorna a carta que está no vector e que o lista tá apontando *****
				carta aux;
				carta inverte;
				aux=posJog[Pont].Buscar(lixo.Top());
				if(ok){ //tem carta para jogar
					if(aux.valor=='Q'){//trocar de sentido; 1-horario; -1 anti-horario
						sentido=sentido*(-1);
						if(sentido==1) Jog.Itpp();
						else Jog.Itmm();
					}
					if(sentido==1){ //jogo ta no sentido horario
						if(aux.valor=='A'){//proximo jog não joga
							Jog.Itpp();
							Jog.Itpp();
						}
						else{
							if(aux.valor=='7'){//proximo jog compra 2 cartas
								Jog.Itpp();
								posJog[Pont].InsertL(monte.Top()); //compra 1
								monte.Pop();
								posJog[Pont].InsertL(monte.Top()); //compra 2
								monte.Pop();
							}
							else{
								if(aux.valor=='9'){//o jog anterior compra 3 cartas
									Jog.Itmm();
									posJog[Pont].InsertL(monte.Top());//compra 1
									monte.Pop();
									posJog[Pont].InsertL(monte.Top());//compra 2
									monte.Pop();
									posJog[Pont].InsertL(monte.Top());//compra 3
									monte.Pop();
								}
							}
						}
					}
					if(sentido==-1){//jogo ta no sentido anti horario
						if(aux.valor=='A'){//proximo jog não jogar
							Jog.Itmm();
							Jog.Itmm();
						}
						else{
							if(aux.valor=='7'){//proximo jog compra 2 cartas
								Jog.Itmm();
								posJog[Pont].InsertL(monte.Top()); //compra 1
								monte.Pop();
								posJog[Pont].InsertL(monte.Top()); //compra 2
								monte.Pop();
							}
							else{
								if(aux.valor=='9'){//o jog anterior compra 3 cartas
									Jog.Itpp();
									posJog[Pont].InsertL(monte.Top());//compra 1
									monte.Pop();
									posJog[Pont].InsertL(monte.Top());//compra 2
									monte.Pop();
									posJog[Pont].InsertL(monte.Top());//compra 3
									monte.Pop();
								}
							}
						}
					}
					lixo.Push(aux);
				}
				if(aux.valor=='0'){//Jog nao tem a carta igual do lixo; vai ter que comprar carta no monte
					if(monte.Top().valor==lixo.Top().valor or monte.Top().naipe==lixo.Top().naipe){//a carta do monte e igual do lixo
						ok=true;
					}
					else{ //a carta do monte nao eh igual do lixo
						ok=false;
					}
				}				 
				else{//carta comprada eh diferente do topo do lixo; proximo jog joga
					if(sentido==1) Jog.Itpp();
					else Jog.Itmm();
				}                                                      
				if(monte.Size()==0){//monte ta vazio, levar todas as carta do lixo menos o topo para o monte
					inverte=lixo.Top();
					lixo.Pop();
					while(!lixo.Empty()){
						monte.Top()=lixo.Top();
						lixo.Pop();
					}
					lixo.Top()=inverte;
				}
				if(posJog[Pont].SizeL()==0) zero=false;//verificar se algum jogador tem size==0	
				cout<<"ninguem chegou a zero"<<endl;
			}
			//verificar quem perdeu
			int pontuacao=0, pontos=0, perdedor;
			Jog.BeginLCDE();
			Lista test;
			for(int p=1; p<=Jog.SizeLCDE(); p++){
				pontos=test.SomaPontos();
				if(pontos>pontuacao){
					pontuacao=pontos;
					perdedor=Jog.ItRet();
				}
				Jog.Itpp();
				cout<<pontos<<endl;
			}
			//cout<<perdedor<<endl;
			/*Jog.EraseLCDE(perdedor);
			numPartidas--;
			while(!lixo.Empty()) lixo.Pop();
			while(!monte.Empty()) monte.Pop();*/
		}
		//quem ganhou a rodada?
		//cout<<"Partida"<< <<]
		//cout<<"vencedor"<<Jog.ItRet()<<endl;
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
