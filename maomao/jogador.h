//Silvania Alves Oliveira
#include "ClassList.h"
using namespace std;

class Jogador{
	public:
		int IdJog;
		Lista mao; 
		int pontos;
	public:
		Jogador(){
			IdJog=0;
			pontos=0;
		}
		void SomarPontos(){
			pontos = 0;
			while(mao.SizeL()!=0){
				pontos=pontos+mao.Ret() - 64;
				mao.PopL();
			}
		}
		void LimparPontos(){
			pontos=0;
		}
};
