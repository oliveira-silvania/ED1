//Silvania Alves Oliveira
#include <iostream>

using namespace std;

template <class pilha> class Node{
	public:
	pilha D;
	Node<pilha> *Next;
	static Node<pilha>* MontaNode(pilha T){
		Node<pilha>* P=new Node;
		if(P){
			P->D=T;
			P->Next=0;
		}
		return P;
	}
	static void DesmontaNode(Node* P){
		if(P) delete P;
	}
};

template <class pilha> class stack{
	Node<pilha> *Topo;
	int N;
	public:
	stack(){
		Topo=0;
		N=0;
	}
	bool Push(pilha T){
		Node<pilha> *P=Node<pilha>::MontaNode(T);
		if(!P) return false;
		//tem nó feito no MontaNode
		P->Next=Topo;
		Topo=P;
		N++;
		return true;
	}
	void Pop(){
		if(!Topo) return;
		Node<pilha> *p;
		p=Topo;
		Topo=Topo->Next;
		Node<pilha>::DesmontaNode(p);
		N--;
	}
	pilha Top(){
		pilha T;
		if(Topo){//Topo!=0
			T=Topo->D;
		}
		return T;
	}
	bool Empty(){
		if(Topo==0){
			return true;
		}
		return false;
	}
	int Size(){
		return N;
	}
	void clear(){
		Node<pilha> *P;
		while(Topo){ //Topo!=0
			P=Topo;
			Topo=Topo->Next;
			Node<pilha>::DesmontaNode(P);
			N--;
		}
	}
	~stack(){
		stack:: clear();
	}
};
