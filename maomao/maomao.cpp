//Silvania Alves Oliveira
#include <iostream>
#include "listCDE.h"
#include "pilha.h"
#include "carta.h"
#include "list.h"
using namespace std;


struct jogador{
	int id;	
};
int main(){
	carta aux;
	int numPartidas, numJog;
	
	cin>>numPartidas;
	for(int p=1; p<=numPartidas; p++){ //numero de rodadas
		cin>>numJog; 
		Lista jg[numJog];
		listCDE<jogador> vez[numJog]; //vez do jogador jogar 
		stack<carta> monte, lixo;
		for(int c=0; c<104; c++){ //colocar as cartas na pilha monte
			cin>>aux.valor>>aux.naipe;
			monte.Push(aux);
		}
		for(int j=0; j<numJog; j++){ 
			for(int k=0; k<=5; k++){ //destribuir as cartas para cada jogador
				jg[j].InsertL(monte.Top());
				monte.Pop();
			}
		}
	}
}
