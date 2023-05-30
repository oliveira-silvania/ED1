//Silvania Alves Oliveira
#include <iostream>
using namespace std;

template <class lista> class NodeLCDE{
	public:
	lista D;
	NodeLCDE<lista>* Next;
	NodeLCDE<lista>* Prev;
	static NodeLCDE* MontaNode(lista dat){
		NodeLCDE* P=new NodeLCDE;
		if(P){
			P->D=dat;
			P->Next= P->Prev = 0;
		}
		return P;
	}
	static DesmontaNode(NodeLCDE* P){
		if(P) delete P;
	}
};

//Lista
template<class lista>class listCDE{
	private:
		NodeLCDE<lista> *Head;
		NodeLCDE<lista> *It;
		int N;
	public:
	listCDE(){
		Head=0;
		It=0;
		N=0;
	}
	bool InsertNext(lista T){
		NodeLCDE<lista> *P = NodeLCDE<lista>::MontaNode(T);
		if(!P) return false;
		if(!Head){
			P-> Prev = P->Next = Head = It = P;
		}
		else{
			P-> Prev = It;
			P-> Next = It->Next;
			It-> Next = P-> Next-> Prev = P;
			It = P;
		}
		N++;
		return true;
	}
	
	bool InsertPrev(lista T){
		NodeLCDE<lista> *P = NodeLCDE<lista>::MontaNode(T);
		if(!P) return false;
		if(!Head){
			P-> Prev = P->Next = Head = It = P;
		}
		else{
			P-> Next = It;
			P-> Prev = It->Prev;
			It-> Prev = P-> Prev-> Next = P;
			It = P;
			if(Head==P->Next){
				Head=P;
			}
		}
		N++;
		return true;
	}
	bool Itpp(){
		if(It){
			It=It->Next;
			return true;
		}
		return false;
	}
	bool Itmm(){
		if(It){
			It=It->Prev;
			return true;
		}
		return false;
	}
	void BeginLCDE(){
		It=Head;
	}
	void EndLCDE(){
		if(Head){
			It=Head->Prev;
		}
	}
	void EraseLCDE(){
		if(It){
			NodeLCDE<lista> *P = It;
			if(It->Next==It){
				NodeLCDE<lista>::DesmontaNode(P);
				Head=It=0;
			}
			else{
				(It->Next)->Prev=It->Prev;
				(It->Prev)->Next=It->Next;
				It=It->Next;
				if(Head==P){
					Head=P->Next;
				}
				NodeLCDE<lista>::DesmontaNode(P);
			}
			N--;
		}
	}
	int SizeLCDE(){
		return N;
	}
	bool EmptyLCDE(){
		if(Head==0) return true;
		
		return false;
	}
	void ClearLCDE(){
		NodeLCDE<lista> *P;
		while(N){
			P=Head;
			Head=Head->Next;
			NodeLCDE<lista>::DesmontaNode(P);
			N--;
		}
		Head=It=0;
		N=0;
	}
	lista ItRet(){
		lista T;
		if(!It) return T;
		
		T=It->D;
		return T;
	}
	~listCDE(){
		NodeLCDE<lista> *P;
		while(N){
			P=Head;
			Head=Head->Next;
			NodeLCDE<lista>::DesmontaNodeLCDE(P);
			N--;
		}
	}
	
};

