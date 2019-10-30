#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

vector<int> paginas;
int quantQuadros;

vector<int> entradaPaginas;

int makeFIFO(){
    int fila[quantQuadros];
    int falhas = 0;
    for(int i=0;i<quantQuadros;i++){
        fila[i]=-1;
    }
    int pos = 0;
    for(int pagina : paginas){
        bool estaNaFila = false;
        for(int i=0;i<quantQuadros;i++){
            if(fila[i]==pagina){
                estaNaFila = true;
                break;
            }
        }
        if(!estaNaFila){
            falhas += 1;
            fila[pos] = pagina;
            pos += 1;
            if(pos==quantQuadros){
                pos=0;
            }
        }
    }
    return falhas;
}
int makeLRU(){
    int fila[quantQuadros];
    int tempo[quantQuadros];
    int falhas = 0;
    for(int i=0;i<quantQuadros;i++){
        fila[i]=-1;
        tempo[i]=-1;
    }
    for(int pagina : paginas){
        
        bool estaNaFila = false;
        for(int i=0;i<quantQuadros;i++){
            if(fila[i]==pagina){
                estaNaFila = true;
                tempo[i]=0;
                break;
            }
        }
        if(!estaNaFila){
            falhas += 1;
            int maior = -1;
            int tempoMaior = -2;
            for(int i=0;i<quantQuadros;i++){
                if(tempo[i]>tempoMaior){
                    maior=i;
                    tempoMaior=tempo[i];
                }
                if(tempo[i]==-1){
                    maior=i;
                    break;
                }
            }
            fila[maior]=pagina;
            tempo[maior]=0;
        }
        for(int i=0;i<quantQuadros;i++){
            if(tempo[i]>=0){
                tempo[i]++;
            }
        }
    }
    return falhas;
}
int makeOPT(){
    int fila[quantQuadros];
    int falhas = 0;
    int posNaListaDePaginas =-1;
    
    int count =0;
    map<int, queue<int>> mapPaginas;
    for(int pagina: paginas){
		mapPaginas[pagina].push(count);
		count++;
    }
    
    for(int i=0;i<quantQuadros;i++){
        fila[i]=-1;
    }
    int posAtual =0;
    for(int pagina : paginas){
        posNaListaDePaginas++;
        bool estaNaFila = false;
        for(int i=0;i<quantQuadros;i++){
            if(fila[i]==pagina){
                estaNaFila = true;
                break;
            }
        }
        if(!estaNaFila){
            falhas += 1;
            int maiorPos=0;
            int paginaSelecionada=-1; 
            bool inicio = true;
            for(int i=0;i<quantQuadros;i++){
				if(fila[i]==-1){
					paginaSelecionada=i;
					inicio=true;
					break;
				}
				inicio=false;
				queue<int> listaPos = mapPaginas[fila[i]];
				bool escolhido = false;
				while(1){
					if(listaPos.empty()){
						paginaSelecionada=fila[i];
						escolhido=true;
						break;
					}
					if(listaPos.front()<posAtual){
						listaPos.pop();
						continue;
					}
					if(listaPos.front()>maiorPos){
						maiorPos=listaPos.front();
						paginaSelecionada=fila[i];
					}
					break;
				}
				if(escolhido){
					break;
				}
			}
			int sobrou;
            if(inicio){
				sobrou=paginaSelecionada;
			}
			else{
				for(int i=0;i<quantQuadros;i++){
					if(fila[i]==paginaSelecionada){
						sobrou=i;
						break;
					}
				}
			}
            fila[sobrou]=pagina;
        }
        posAtual++;
    }
    return falhas;
}

int main(int argc, char *argv[ ]){
    quantQuadros = atoi(argv[1]);
    //ler arquivo
    int temp;
    while (scanf ("%d\n", &temp) == 1 ){
        paginas.push_back(temp);
    }
    //FIFO
    int falhasFifo = makeFIFO();
    cout<<"terminou o FIFO"<<endl;
    //OPT
    int falhasOpt = makeOPT();
    cout<<"terminou o FIFO"<<endl;
    //LRU
    int falhasLru = makeLRU();
	cout<<"terminou o FIFO"<<endl;

    cout<<quantQuadros<<" quadros, "<<paginas.size()<<" refs: FIFO: "<<falhasFifo<<" PFs, LRU: "<<falhasLru<<" Pfs, OPT: "<<falhasOpt<<" Pfs"<<endl; 
    return 0;
}
