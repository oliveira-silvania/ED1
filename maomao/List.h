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
	
	bool InsertL (carta T){
		NodeL *P = NodeL::MontaNode(T);
		if(!P) return false;
		
		NodeL **aux = &Head;
		while(((*aux) && ((((*aux)->D).valor > T.valor))) || ((((*aux)->D).valor == T.valor) && (((*aux)->D).naipe < T.naipe))){
			aux = &((*aux)->Next);
		}
		P->Next = (*aux);
		(*aux)= P;
		N++;
		return true;
	}	
	
	carta ProcurarL(carta T){ 
		NodeL **it= &Head;
		NodeL *p;
		carta aux;
		aux.valor = '0';
		
		while((*it) and ((*it)->D).valor != T.valor){//it!=null and it ta apontando for diferente do que eu quero
			it = &((*it)->Next);
		}
		if(*it){
			p=(*it);
			aux=(*it)->D;
			NodeL::DesmontaNode(p);
			return aux;
		}
		it = &Head;
		while(*it and ((*it)->D).naipe != T.naipe){//it!=null and it ta apontando para o diferente do que eu quero
			it = &((*it)->Next);
		}
		if(*it){
			p=*it;
			aux=(*it)->D;
			NodeL::DesmontaNode(p);
			return aux;
		}
		return aux; //se nao tiver nada vai retornar lixo
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
