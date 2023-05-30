//Silvania Alves Oliveira
#include "classCarta.h"
using namespace std;

template <class list> class Node{
	public:
		carta D;
		Node<list> *Next;
		static Node* MontaNode(carta dat){
			Node *P = new Node;
			if(P){
				P->D=dat;
				P->Next=0;
			}
			return P;
		}
		static DesmontaNode(Node *P){
			if(P) delete P;	
		}
};

template<class lista>class Lista{
	public:
		Node<lista> *Head;
		int N;
	public:
	Lista(){
		Head=0;
		N=0;
	}
	~Lista(){
		Node<lista> *P = Head;
		while(Head){
			P=Head;
			Head=Head->Next;
			Node<lista>::DesmontaNode(P);
			
		}
	}
	
	bool InsertL (carta T){
		Node<lista> *P = Node<lista>::MontaNode(T);
		if(!P) return false;
		
		Node<lista> **aux = &Head;
		while((*aux) && ((((*aux)->D).valor > T.valor) || (((*aux)->D).valor == T.valor) && (((*aux)->D).naipe < T.naipe))){
			aux = &((*aux)->Next);
		}
		P->Next = (*aux);
		(*aux)= P;
		N++;
		return true;
	}	
	/*carta EraseL(carta T)
	{
		carta X;
		Node<list>* auxx;
		Node<list>** P = &Head;
		while((*P) && (((*P)->D).valor != T.valor || ((*P)->D).naipe != T.naipe))
		{
			P = &((*P)->Next);
		}
		if(*P)
		{
			auxx = *P;
			*P = (auxx->Next);
			X = Node::DesmontaNode(auxx);
			N--;
		}
		return X;
	}*/
	
	/*bool ProcurarL(carta T, carta*){
		
	}*/
	
	int SizeL(){
		return N;
	}
	
	void ClearL(){
		Node<lista> *P = Head;
		while(Head){
			P=Head;
			Head=Head->Next;
			Node<lista>::DesmontaNode(P);
		}
		N=0;
	}
	
	bool EmptyL(){
		if(Head==0) return true;
		
		return false;
	}
	lista Ret(){
		if(!Head) return false;
		
		return Head->D.valor;
	}
	void PopL()
	{
		if(!Head) return;
		
		Node<lista> *P;
		P=Head;
		Head=Head->Next;
		Node<lista>::DesmontaNode(P);
	}
};
