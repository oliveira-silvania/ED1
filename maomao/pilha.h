#include <iostream>
#include <vector>
using namespace std;

template<class T>
class Node {
	public:
		T D;
		Node* next;
		Node* prev;
	
		static Node* montaNode(T trem) {
			Node* p = new Node;
			if(p) {
				p->D = trem;
				p->next = p->prev = 0;
			}
			return p;
		}
		
		static void desmontaNode(Node* p) {
			delete p;
		}
};

template<class T>
class stack {
	Node<T>* Top;
	int n;
	
	public:
		stack() {
			Top = 0;
			n = 0;
		}
		
		bool push(T trem) {
			Node<T>* p = Node<T>::montaNode(trem);
			if(!p) return false;
			p->next = Top;
			Top = p;
			n++;
			return true;
		}
		
		void pop() {
			if(Top) {
				Node<T>* p = Top;
				Top = Top->next;
				Node<T>::desmontaNode(p);
				n--;
			}
		}
		
		void clear() {
			Node<T>* p;
			while(Top) {
				p = Top;
				Top = Top->next;
				Node<T>::desmontaNode(p);
			}
			n = 0;
		}
		
		T top() {
			T trem;
			if(Top) trem = Top->D;
			return trem;
		}
		
		int size() {
			return n;
		}
		
		bool empty() {
			return !n;
		}
};

template<class T>
class ListCDE {
	Node<T>* Head;
	Node<T>* It;
	int n;
	
	public:
		ListCDE() {
			Head = It = 0;
			n = 0;
		}
		
		~ListCDE(){
			Node<T> *P;
			while(n){
				P = Head;
				Head = Head->next;
				Node<T>::desmontaNode(P);
				n--;
			}
		}
		
		bool insertNext(T trem){
			Node<T> *P = Node<T>::montaNode(trem);
			if(!P) return false;
			if(!Head){
				P->prev = P->next = Head = It = P;
			}
			else{
				Node<T> *antes = It;
				It = Head;
				while(size() && ((It->next)->D[0] < trem[0] || ((It->next)->D[0] == trem[0] && It->D[1] > trem[1]))) {
					It = It->next;
				}
				P->prev = It;
				P->next = It->next;
				It->next = (P->next)->prev = P;
				It = antes;
			}
			n++;
			return true;
		}
		
		bool insertPrev(T trem){
			Node<T> *P = Node<T>::montaNode(trem);
			if(!P) return false;
			if(!Head){
				P-> prev = P->next = Head = It = P;
			}
			else{
				Node<T> *antes = It;
				It = Head;
				while(size() && ((It->next)->D[0] < trem[0] || ((It->next)->D[0] == trem[0] && It->D[1] > trem[1]))) {
					It = It->next;
				}
				P->next = It;
				P->prev = It->prev;
				It->prev = (P->prev)->next = P;
				It = antes;
				if(Head == P->next){
					Head = P;
				}
			}
			n++;
			return true;
		}
		
		string jogaCarta(string topo) {
			It = Head->prev;
			
			for(int i = 0; i < size(); i++) {
				if(It->D[0] == topo[0]) {
					erase();
					return It->D;
				}
				else if(It->D[1] == topo[1]) {
					erase();
					return It->D;
				}
				It = It->prev;
			}
			return "-1";
		}
		
		void erase(){
			if(It){
				Node<T> *P = It;
				if(It->next == It){
					Node<T>::desmontaNode(P);
					Head = It = 0;
				}
				else{
					(It->next)->prev = It->prev;
					(It->prev)->next = It->next;
					It = It->next;
					if(Head == P){
						Head = P->next;
					}
					Node<T>::desmontaNode(P);
				}
				n--;
			}
		}
		
		void clear() {
			Node<T> *P;
			while(n){
				P = Head;
				Head = Head->next;
				Node<T>::desmontaNode(P);
				n--;
			}
		}
		
		bool Itpp() {
			if(It) {
				It = It->next;
				return true;
			}
			return false;
		}
		
		bool Itmm() {
			if(It) {
				It = It->prev;
				return true;
			}
			return false;
		}
		
		T ItRet() {
			T trem;
			if(It) return It->D;
			return trem;
		}
		
		void begin() {
			It = Head;
		}
		
		void end() {
			if(Head) {
				It = Head->prev;
			}
		}
		
		int size() {
			return n;
		}
		
		bool empty() {
			return !n;
		}
};

void inicializaDados(int numJog, stack<string> &monte, stack<string> &lixo, ListCDE<string> jogador[11]) { 
	while(!lixo.empty()) {
		monte.push(lixo.top());
		lixo.pop();
	}
	
	for(int j = 0; j < numJog; j++) {
		jogador[j].begin();
		while(!jogador[j].empty()) {
			monte.push(jogador[j].ItRet());
			jogador[j].Itpp();
		}
		jogador[j].clear();
	}
	
	for(int j = 0; j < numJog; j++) {
		for(int k = 0; k < 5; k++) {
			jogador[j].insertNext(monte.top());
			monte.pop();
		}
	}
}

void decidePerdedor(int numJog, ListCDE<string> jogador[11]) {
	int pts[numJog], maior = 0, jog;
	
	for(int i = 0; i < numJog; i++) {
		int cont = 0;
		jogador[i].begin();
		for(int j = 0; j < jogador[i].size(); j++){
			cont += jogador[j].ItRet()[0] - 'A' + 1;
		}
		pts[i] = cont;
		if(pts[i] > maior) {
			maior = pts[i];
			jog = i;
		}
	}
	jogador[jog].clear();
}

int vencedor = 0;

bool temMaisDeUmJogador(ListCDE<string> lista[11], int numJog) {
	int cont = 0;
	for(int i = 0; i < numJog; i++) {
		if(lista[i].empty()) cont++;
		else vencedor = i;
		if(cont > 1) return true;
	}
	return false;
}

void inverteMonte(stack<string> &monte, stack<string> &lixo) {
	string topo = lixo.top();
	lixo.pop();
	while(!lixo.empty()) {
		monte.push(lixo.top());
		lixo.pop();
	}
	lixo.push(topo);
}

int main(){
    int partidas, numJog;
    cin >> partidas;
    
    for(int i = 1; i <= partidas; i++) {
    	cin >> numJog;
    	
    	stack<string> monte, lixo;
		ListCDE<string> jogador[11];  
		
		for(int j = 0; j < 104; j++) {
			string carta;
			cin >> carta;
			monte.push(carta);
		}
		for(int j = 0; j < numJog; j++) {
			for(int k = 0; k < 5; k++) {
				jogador[j].insertNext(monte.top());
				monte.pop();
			}
		}
		
		int pos = 1;
		bool horario = true;
		
		while(temMaisDeUmJogador(jogador, numJog)) {
			bool acabouRodada = false;
			if(monte.empty()) {
				inverteMonte(monte, lixo);
			}
			
			string carta;
			if(lixo.empty()) {
				carta = jogador[0].ItRet();
				jogador[0].erase();
				lixo.push(carta);
			}
			else {
				pos = pos % numJog;
				carta = jogador[pos].jogaCarta(lixo.top());
				
				if(carta == "-1") {
					jogador[pos].insertNext(monte.top());
					monte.pop();
					carta = jogador[pos].jogaCarta(lixo.top());
					if(carta != "-1") lixo.push(carta);
				}
				else lixo.push(carta);
				
				if(jogador[pos].empty()) {
					acabouRodada = true;
					pos = 1;
					decidePerdedor(numJog, jogador);
					inicializaDados(numJog, monte, lixo, jogador);
				}
			}
			
			if(!acabouRodada) {
				if(carta[0] == 'A') {
					if(horario) pos = pos + numJog + 2;
					else pos = pos + numJog - 2;
				}
				else {
					if(carta[0] == 'L') {
						if(horario) horario = false;
						else horario = true;
					}
					else if(carta[1] == 'G') {
						for(int j = 0; j < 2; j++) {
							if(horario) jogador[(pos + numJog + 1) % numJog].insertNext(monte.top());
							else jogador[(pos + numJog - 1) % numJog].insertNext(monte.top());
							monte.pop();
							if(monte.empty()) inverteMonte(monte, lixo);
						}
					}
					else if(carta[1] == 'I') {
						for(int j = 0; j < 3; j++) {
							if(horario) jogador[(pos + numJog - 1) % numJog].insertNext(monte.top());
							else jogador[(pos + numJog + 1) % numJog].insertNext(monte.top());
							monte.pop();
							if(monte.empty()) inverteMonte(monte, lixo);
						}
					}
					if(horario) pos = pos + numJog + 1;
					else pos = pos + numJog - 1;
				}
			}
		}
		cout << "Vencedor da partida " << i << ": Jogador " << vencedor << endl;
	}
}
