//Silvania Alves Oliveira
#include <bits/stdc++.h>
#include "listCDE.h"
#include "pilha.h"
#include "carta.h"
#include "list.h"
using namespace std;


int main(){
	carta aux;
	int numPartidas, numJog;
	
	cin>>numPartidas;
	for(int p=1; p<=numPartidas; p++){ //numero de rodadas
		cin>>numJog; 
		listCDE<int> Jog;
		vector<Lista> posJog(numJog+1);
		Stack<carta> monte, lixo;
		for(int c=0; c<104; c++){ //colocar as cartas na pilha monte
			cin>>aux.valor>>aux.naipe;
			monte.Push(aux);
		}
		for(int j=1; j<=numJog; j++){ //destribuir as cartas para cada jogador
			for(int k=0; k<=5; k++){ 
				posJog[j].InsertL(monte.Top());
				monte.Pop();
			}
		}
		for(int i=1; i<=numJog; i++){
			Jog.InsertNext(i);
		}
		int Pont = Jog.ItRet();
		bool sentido=true;
		while(numJog>1){
			bool acabouRodada=false;
			if(lixo.Empty()){
				lixo.Push(posJog[Pont].primeiraCarta());
			}
		}
	}
}
