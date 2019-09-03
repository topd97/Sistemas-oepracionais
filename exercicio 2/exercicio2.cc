#include <iostream>
#include <string>
#include <vector>
using namespace std;


int quant;
vector<int> ingressos, temposDeExecucao, prioridades;

int executaTarefaIninterrupta(int pos){
    return temposDeExecucao[pos];
}

int makeFCFS(){
    int tempoDeExecucao = 0;
    for( int processo=0; processo<temposDeExecucao.size(); processo++){
        tempoDeExecucao += executaTarefaIninterrupta(processo);
    }
    return tempoDeExecucao;
}

int makeRR(){

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
    cout << "tempoFCS: " << tempoFCS << endl;
}