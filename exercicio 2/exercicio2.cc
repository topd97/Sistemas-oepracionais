#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <time.h>
#include <list>

using namespace std;

int quant;
vector<int> ingressos, temposDeExecucao, prioridades;
int preempcao = 2;

int makeFCFS(){
    int tempoDeExecucao = 0;
    for( int processo=0; processo<temposDeExecucao.size(); processo++){
        tempoDeExecucao += temposDeExecucao[processo];
    }
    return tempoDeExecucao;
}

int makeRR(){
    int tempoDeExecucao = 0;
    queue<int> fila;
    vector<int> copiaIngressos, copiaTemposDeExecucao;
    list<int> processos;

    vector<int> test;

    int temp, quantProcessos;
    int next = 0;

    copiaIngressos = ingressos;
    copiaTemposDeExecucao = temposDeExecucao;
    for(int i=0;i<quant;i++ ){
        processos.push_back(i);
    }
    while(!processos.empty()){

        for( auto processo: processos){
            if(copiaIngressos[processo] == tempoDeExecucao){
                test.push_back(processo);
                fila.push(processo);
            }   
        }
        if(tempoDeExecucao == next){

            temp = fila.front();
            cout << "temp: " << temp << endl;
            copiaIngressos[temp] += tempoDeExecucao + preempcao;
            copiaTemposDeExecucao[temp] -= preempcao;
            
            if(copiaTemposDeExecucao[temp] < 0) {
                cout << temp << endl;

                next += preempcao + copiaTemposDeExecucao[temp];
                copiaIngressos[temp] = -1;
                processos.remove(temp);
            }
            else {
                if(copiaTemposDeExecucao[temp] == 0){
                    cout << temp << endl;
                    copiaIngressos[temp] = -1;
                    processos.remove(temp);
                }
                next += preempcao;
            }
            fila.pop();
        }
        tempoDeExecucao += 1;
    }
    return tempoDeExecucao;
}

int makeSJF(){

}

int makeSTRF(){

}

int makePRIOc(){

}

int makePRIOf(){

}

int makePRIOd(){

}


int main(){
    int a;
    cin >> quant;
    int temp;
    for( int i=0; i<quant;i++){
        cin >> temp;
        ingressos.push_back(temp);
    }
    for( int i=0; i<quant;i++){
        cin >> temp;
        temposDeExecucao.push_back(temp);
    }
    for( int i=0; i<quant;i++){
        cin >> temp;
        prioridades.push_back(temp);
    }

    int tempoFCFS, tempoRR, tempoSJF, tempoSTRF, tempoPRIOc, tempoPRIOf, tempoPRIOd;
    tempoFCFS = makeFCFS();
    tempoRR = makeRR();
    tempoSJF = makeSJF();
    tempoSTRF = makeSTRF();
    tempoPRIOc = makePRIOc();
    tempoPRIOf = makePRIOf();
    tempoPRIOd = makePRIOd();
    
    
    cin >> a;
    cout << "Hello wordl" << endl;
    cout << quant << endl;
    cout << ingressos[0] << " " << ingressos[1] << " " << ingressos[2] << " " << ingressos[3] << " " << ingressos[4] << " " << endl;
    cout << temposDeExecucao[0] << " " << temposDeExecucao[1] << " " << temposDeExecucao[2] << " " << temposDeExecucao[3] << " " << temposDeExecucao[4] << " " << endl;
    cout << prioridades[0] << " " << prioridades[1] << " " << prioridades[2] << " " << prioridades[3] << " " << prioridades[4] << " " << endl;
    cout << "Resultados" << endl;;
    cout << "tempoFCFS: " << tempoFCFS << endl;
    cout << "tempoRR: " << tempoRR << endl;
}