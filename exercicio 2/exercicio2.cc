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
	cout << "Iniciando o FCFS" << endl;
    int tempoDeExecucao = 0;
    for( int processo=0; processo<temposDeExecucao.size(); processo++){
        tempoDeExecucao += temposDeExecucao[processo];
    }
    cout << "Finalizando o FCFS" << endl;
    return tempoDeExecucao;
}

int makeRR(){
	cout << "Iniciando o RR" << endl;
	
    int tempoDeExecucao = 0;
    queue<int> fila;
    vector<int> copiaIngressos, copiaTemposDeExecucao;
    vector<int> test;
    int temp;
    int next = 0;

    copiaIngressos = ingressos;
    copiaTemposDeExecucao = temposDeExecucao;
    
    list<int> processos;
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
            cout << "Executando processo: " << temp << endl;
            copiaIngressos[temp] += tempoDeExecucao + preempcao;
            copiaTemposDeExecucao[temp] -= preempcao;
            
            if(copiaTemposDeExecucao[temp] < 0) {
                //cout << temp << endl;

                next += preempcao + copiaTemposDeExecucao[temp];
                copiaIngressos[temp] = -1;
                processos.remove(temp);
            }
            else {
                if(copiaTemposDeExecucao[temp] == 0){
                    //cout << temp << endl;
                    copiaIngressos[temp] = -1;
                    processos.remove(temp);
                }
                next += preempcao;
            }
            fila.pop();
        }
        tempoDeExecucao += 1;
    }
    cout << "Finalizando o RR" << endl;
    return tempoDeExecucao;
}

int makeSJF(){
    cout << "Iniciando o SJF" << endl;
	
	int tempoDeExecucao = 0;
	vector<int> copiaTemposDeExecucao;
	int menorTempo = -1;
	int escolhido = -1;
	
	list<int> processos;
    for(int i=0;i<quant;i++ ){
        processos.push_back(i);
    }
	
	copiaTemposDeExecucao = temposDeExecucao;
	while(!processos.empty()){
		for( auto processo: processos){
			if ( ingressos[processo] <= tempoDeExecucao && (copiaTemposDeExecucao[processo] < menorTempo || menorTempo == -1 )){
				menorTempo = copiaTemposDeExecucao[processo];
				escolhido = processo;
			}
		} 
		cout << "Executando processo: " << escolhido << endl;
		tempoDeExecucao += copiaTemposDeExecucao[escolhido];
		processos.remove(escolhido);
		menorTempo = -1;
		escolhido = -1;
	}
    cout << "Finalizando o SJF" << endl;
    
    return tempoDeExecucao;

}

int makeSTRF(){
    cout << "Iniciando o STRF" << endl;
	
    int tempoDeExecucao = 0;
    list<int> possiveis;
    vector<int> copiaTemposDeExecucao;
    vector<int> test;

    copiaTemposDeExecucao = temposDeExecucao;
    
    list<int> processos;
    for(int i=0;i<quant;i++ ){
        processos.push_back(i);
    }
    
    while(!processos.empty()){
        int escolhido = -1;
        int tempoEscolhido = -1;

        for( auto processo: processos){
            if (tempoDeExecucao == ingressos[processo]){
                possiveis.push_back(processo);
            }
        }

        for( auto processoEscolhido: possiveis){
            if(escolhido == -1 || tempoEscolhido>copiaTemposDeExecucao[processoEscolhido]){
                tempoEscolhido = copiaTemposDeExecucao[processoEscolhido];
                escolhido = processoEscolhido;
            }
        }

        cout << "Executando processo: " << escolhido << endl;
        copiaTemposDeExecucao[escolhido] = copiaTemposDeExecucao[escolhido] - 1;
        if(copiaTemposDeExecucao[escolhido] <= 0){
            possiveis.remove(escolhido);
            processos.remove(escolhido);
        }
        tempoDeExecucao += 1;
    }
    cout << "Finalizando o STRF" << endl;
    return tempoDeExecucao;
}

int makePRIOc(){
    cout << "Iniciando o PRIOc" << endl;
    int tempoDeExecucao = 0;
    list<int> possiveis;
    vector<int> copiaIngressos;
    copiaIngressos = ingressos;

    list<int> processos;
    for(int i=0;i<quant;i++ ){
        processos.push_back(i);
    }
    
    while(!processos.empty()){
        int escolhido = -1;
        int prioridade = -1;

        for( auto processo: processos){
            if (tempoDeExecucao >= copiaIngressos[processo] && copiaIngressos[processo] != -1){
                possiveis.push_back(processo);
                copiaIngressos[processo] = -1;
            }
        }

        for( auto processoEscolhido: possiveis){
            if(escolhido == -1 || prioridade<prioridades[processoEscolhido]){
                prioridade = prioridades[processoEscolhido];
                escolhido = processoEscolhido;
            }
        }

        cout << "Executando processo: " << escolhido << endl;
        possiveis.remove(escolhido);
        processos.remove(escolhido);
        tempoDeExecucao += temposDeExecucao[escolhido];
    }
    
    cout << "Finalizando o PRIOc" << endl;
    return tempoDeExecucao;
}

int makePRIOp(){
    cout << "Iniciando o PRIOp" << endl;
	
    int tempoDeExecucao = 0;
    list<int> possiveis;
    vector<int> copiaTemposDeExecucao;
    vector<int> test;

    copiaTemposDeExecucao = temposDeExecucao;
    
    list<int> processos;
    for(int i=0;i<quant;i++ ){
        processos.push_back(i);
    }
    
    while(!processos.empty()){
        int escolhido = -1;
        int prioridade = -1;

        for( auto processo: processos){
            if (tempoDeExecucao == ingressos[processo]){
                possiveis.push_back(processo);
            }
        }

        for( auto processoEscolhido: possiveis){
            if(escolhido == -1 || prioridade<prioridades[processoEscolhido]){
                prioridade = prioridades[processoEscolhido];
                escolhido = processoEscolhido;
            }
        }

        cout << "Executando processo: " << escolhido << endl;
        copiaTemposDeExecucao[escolhido] = copiaTemposDeExecucao[escolhido] - 1;
        if(copiaTemposDeExecucao[escolhido] <= 0){
            possiveis.remove(escolhido);
            processos.remove(escolhido);
        }
        tempoDeExecucao += 1;
    }
    cout << "Finalizando o PRIOp" << endl;
    return tempoDeExecucao;
}

int makePRIOd(){
    cout << "Iniciando o PRIOd" << endl;
	
    int tempoDeExecucao = 0;
    list<int> possiveis;
    vector<int> prioE, prioD;
    vector<int> copiaTemposDeExecucao;

    copiaTemposDeExecucao = temposDeExecucao;

    list<int> processos;
    for(int i=0;i<quant;i++ ){
        processos.push_back(i);
        prioE.push_back(prioridades[i]);
        prioD.push_back(prioE[i]);
    }

    while(!processos.empty()){
        int escolhido = -1;
        int maiorPrio = -1;

        for( auto processo: processos){
            if (maiorPrio < prioD[processo]){
                escolhido = processo;
                maiorPrio = prioD[processo];
            }
        }

        for (int i=0; i< prioD.size();i++){
            prioD[i] += 1;
        }
        prioD[escolhido] = prioE[escolhido];

        cout << "Executando processo: " << escolhido << endl;
        copiaTemposDeExecucao[escolhido] = copiaTemposDeExecucao[escolhido] - 1;
        if(copiaTemposDeExecucao[escolhido] <= 0){
            processos.remove(escolhido);
        }
        tempoDeExecucao += 1;
    }

    cout << "Iniciando o PRIOd" << endl;
    return tempoDeExecucao;
}


int main(){
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

    int tempoFCFS, tempoRR, tempoSJF, tempoSTRF, tempoPRIOc, tempoPRIOp, tempoPRIOd;
    tempoFCFS = makeFCFS();
    tempoRR = makeRR();
    tempoSJF = makeSJF();
    tempoSTRF = makeSTRF();
    tempoPRIOc = makePRIOc();
    tempoPRIOp = makePRIOp();
    tempoPRIOd = makePRIOd();
    
    
    //cin >> a;
    //cout << "Hello wordl" << endl;
    //cout << quant << endl;
    //cout << ingressos[0] << " " << ingressos[1] << " " << ingressos[2] << " " << ingressos[3] << " " << ingressos[4] << " " << endl;
    //cout << temposDeExecucao[0] << " " << temposDeExecucao[1] << " " << temposDeExecucao[2] << " " << temposDeExecucao[3] << " " << temposDeExecucao[4] << " " << endl;
    //cout << prioridades[0] << " " << prioridades[1] << " " << prioridades[2] << " " << prioridades[3] << " " << prioridades[4] << " " << endl;
    cout << "Resultados" << endl;;
    cout << "tempoFCFS: " << tempoFCFS << endl;
    cout << "tempoRR: " << tempoRR << endl;
    cout << "tempoSJF: " << tempoSJF << endl;
    cout << "tempoSTRF: " << tempoSTRF << endl;
    cout << "tempoPRIOc: " << tempoPRIOc << endl;
    cout << "tempoPRIOp: " << tempoPRIOp << endl;
    cout << "tempoPRIOd: " << tempoPRIOd << endl;
}
