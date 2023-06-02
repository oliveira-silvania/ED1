#pragma once
//Silvania Alves Oliveira
#include "carta.h"
using namespace std;

class NodeL{
	public:
		carta D;
		NodeL *Next;
		static NodeL* MontaNode(carta T){
			NodeL *P = new NodeL;
			if(P){
				P->D=T;
				P->Next=0;
			}
			return P;
		}
		static carta DesmontaNode(NodeL* P){
			carta x;
		if(P){
			x=P->D;
			delete P;
		}
		return x;
	}
};

class Lista{
	public:
		NodeL *Head;
		int N;
	public:
	Lista(){
		Head=0;
		N=0;
	}
	~Lista(){
		NodeL *P = Head;
		while(Head){
			P=Head;
			Head=Head->Next;
			NodeL::DesmontaNode(P);
			
		}
	}
	
	void InsertL(carta T){
	NodeL* p = NodeL::MontaNode(T);
	NodeL** it = &Head;
	if(!Head) Head=p;
	else{
		while((*it) and ((((*it)->D).valor > (p->D).valor) or (((*it)->D).valor == (p->D).valor)) and (((*it)->D).naipe < (p->D).naipe)){
			it = &((*it)->Next);
		}
		p->Next = (*it);
		(*it)= p;
	}
	N++;
}

	
	carta Buscar(carta T){

	NodeL **it= &Head;
	NodeL *P;
	carta aux;
	aux.valor = '0';

		while(*it && ((*it)->D).valor != T.valor){
			it=&((*it)->Next);
		}	
		if(*it){
			P=(*it);
			aux=P->D;
			*it=(P->Next);
			NodeL::DesmontaNode(P);
			N--;
			return aux;
		}
		it = &Head;
		while(*it && ((*it)->D).naipe != T.naipe){
			it=&((*it)->Next);
		}	
		if(*it){
			P=(*it);
			aux=P->D;
			*it=(P->Next);
			NodeL::DesmontaNode(P);
			N--;
			return aux;
		}
	return aux; //se nao tiver nada vai retornar lixo
}
	carta primeiraCarta(){
		carta aux;
		aux=Head->D;
		NodeL *P;
		P=Head;
		Head=Head->Next;
		NodeL::DesmontaNode(P);
		
		return aux;
	}
	
	carta imp(){
		carta aux;
		if(Head){
			aux=Head->D;
			NodeL *x = Head;
			Head = Head->Next;
			delete x;
		}
		return aux;
	}
		
	int SizeL(){
		return N;
	}
		
	void ClearL(){
		NodeL *P = Head;
		while(Head){
			P=Head;
			Head=Head->Next;
			NodeL::DesmontaNode(P);
		}
		N=0;
	}
	
	bool EmptyL(){
		if(Head==0) return true;
		
		return false;
	}

	carta PopL(){
		NodeL *P;
		carta aux;
		if(!Head) return aux;
		
		P=Head;
		Head=Head->Next;
		return NodeL::DesmontaNode(P);
	}
};
