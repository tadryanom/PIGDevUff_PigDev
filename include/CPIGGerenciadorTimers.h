#ifndef _CPIGGERENCIADORTIMERS_
#define _CPIGGERENCIADORTIMERS_

#include "CPIGTimer.h"

class CPIGGerenciadorTimers{

private:

    static CPIGRepositorio<PIGTimer> *timers;
    static vector<int> grupos[PIG_MAX_GRUPOS_TIMERS];

public:

    static void Inicia(){
        timers = new CPIGRepositorio<PIGTimer>(PIG_MAX_TIMERS,"timers");
    }

    static void Encerra(){
        delete timers;
    }

    static PIGTimer GetTimer(int idTimer){
        return timers->GetElemento(idTimer);
    }

    static int CriaTimer(bool congelado=false){
        return timers->Insere(new CPIGTimer(congelado));
    }

    static void DestroiTimer(int idTimer){
        timers->Remove(idTimer);
    }

    static void PausaTodos(){
        PIGTimer t = timers->GetPrimeiroElemento();
        while (t != NULL){
            t->PausaGeral();
            t = timers->GetProximoElemento();
        }
    }

    static void DespausaTodos(){
        PIGTimer t = timers->GetPrimeiroElemento();
        while (t != NULL){
            t->DespausaGeral();
            t = timers->GetProximoElemento();
        }
    }

    static int AssociaTimerGrupo(int idTimer, int idGrupo){
        if (idGrupo<0||idGrupo>=PIG_MAX_GRUPOS_TIMERS) return 0;
        PIGTimer t = timers->GetElemento(idTimer);
        grupos[idGrupo].push_back(idTimer);
        return 1;
    }

    static int DesassociaTimerGrupo(int idTimer, int idGrupo){
        if (idGrupo<0||idGrupo>=PIG_MAX_GRUPOS_TIMERS) return 0;
        PIGTimer t = timers->GetElemento(idTimer);
        vector<int>::iterator it = find(grupos[idGrupo].begin(), grupos[idGrupo].end(), idTimer);
        if (it!=grupos[idGrupo].end()){
            grupos[idGrupo].erase(it);
            return 1;
        }
        return 0;
    }

    static int PausaGrupo(int idGrupo){
        if (idGrupo<0||idGrupo>=PIG_MAX_GRUPOS_TIMERS) return -1;
        int cont=0;
        for (unsigned int i=0;i<grupos[idGrupo].size();i++){
            PIGTimer t = timers->GetElemento(grupos[idGrupo][i]);
            if (t) t->Pausa();
            cont++;
        }
        return cont;
    }

    static int DespausaGrupo(int idGrupo){
        if (idGrupo<0||idGrupo>=PIG_MAX_GRUPOS_TIMERS) return -1;
        int cont=0;
        for (unsigned int i=0;i<grupos[idGrupo].size();i++){
            PIGTimer t = timers->GetElemento(grupos[idGrupo][i]);
            if (t) t->Despausa();
            cont++;
        }
        return cont;
    }

    static int ReiniciaGrupo(int idGrupo,bool valor){
        if (idGrupo<0||idGrupo>=PIG_MAX_GRUPOS_TIMERS) return -1;
        int cont=0;
        for (unsigned int i=0;i<grupos[idGrupo].size();i++){
            PIGTimer t = timers->GetElemento(grupos[idGrupo][i]);
            if (t) t->Reinicia(valor);
            cont++;
        }
        return cont;
    }

};
CPIGRepositorio<PIGTimer> *CPIGGerenciadorTimers::timers;
vector<int> CPIGGerenciadorTimers::grupos[PIG_MAX_GRUPOS_TIMERS];
#endif // _CPIGGERENCIADORTIMERS_
