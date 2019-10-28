#include <iostream>
#include <vector>

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
    // cout<<"FIFO: "<<falhas<<endl;
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
        // for(int i=0;i<quantQuadros;i++){
        //     cout<<fila[i]<<" ";
        // }
        // cout<<endl;
        // for(int i=0;i<quantQuadros;i++){
        //     cout<<tempo[i]<<" ";
        // }
        //cout<<endl;
        //cout<<pagina;
        bool estaNaFila = false;
        for(int i=0;i<quantQuadros;i++){
            if(fila[i]==pagina){
                estaNaFila = true;
                tempo[i]=0;
                break;
            }
        }
        if(!estaNaFila){
            //cout<<" falha";
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
        //cout<<endl<<endl;
    }
    // cout<<"LRU: "<<falhas<<endl;
    return falhas;
}
int makeOPT(){
    int fila[quantQuadros];
    int falhas = 0;
    int posNaListaDePaginas =-1;
    for(int i=0;i<quantQuadros;i++){
        fila[i]=-1;
    }
    for(int pagina : paginas){
        // for(int i=0;i<quantQuadros;i++){
        //     cout<<fila[i]<<" ";
        // }
        // cout<<endl;
        // for(int i=0;i<quantQuadros;i++){
        //     cout<<tempo[i]<<" ";
        // }
        //cout<<endl;
        //cout<<pagina;
        posNaListaDePaginas++;
        bool estaNaFila = false;
        for(int i=0;i<quantQuadros;i++){
            if(fila[i]==pagina){
                estaNaFila = true;
                break;
            }
        }
        if(!estaNaFila){
            //cout<<" falha";
            falhas += 1;
            int quantCertos = 0;
            int certos[quantQuadros];
            for(int i=0;i<quantQuadros;i++){
                certos[i]=0;
            }
            for(int i=posNaListaDePaginas;i<paginas.size();i++){
                for (int j = 0;j<quantQuadros;j++){
                    if(quantCertos==quantQuadros-1){
                        break;
                    }
                    if(paginas[i]==fila[j] && certos[j]==0){
                        quantCertos++;
                        certos[j]=1;
                    }
                }
                if(quantCertos==quantQuadros-1){
                    break;
                }
            }
            int sobrou;
            for(int i=0;i<quantQuadros;i++){
                if(certos[i]==0){
                    sobrou=i;
                    break;
                }
            }
            fila[sobrou]=pagina;
        }
        //cout<<endl<<endl;
    }
    // cout<<"OPT: "<<falhas<<endl;
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
    //OPT
    int falhasOpt = makeOPT();
    //LRU
    int falhasLru = makeLRU();

    cout<<quantQuadros<<" quadros, "<<paginas.size()<<" refs: FIFO: "<<falhasFifo<<" PFs, LRU: "<<falhasLru<<" Pfs, OPT: "<<falhasOpt<<" Pfs"<<endl; 
    return 0;
}