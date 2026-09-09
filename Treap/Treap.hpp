#ifndef TREAP_HPP
#define TREAP_HPP

#include <cstdlib>

struct NoTreap {
    int chave;
    int prioridade;
    NoTreap* esq;
    NoTreap* dir;

    NoTreap(int c) {
        chave = c;
        prioridade = rand(); // prioridade
        esq = nullptr;
        dir = nullptr;
    }
};

class Treap {
private:
    NoTreap* raiz;
    long long totalNos;

    NoTreap* rotacaoDireita(NoTreap* y, long long &operacoes);
    NoTreap* rotacaoEsquerda(NoTreap* x, long long &operacoes);
    NoTreap* inserirRec(NoTreap* no, int chave, long long &operacoes);
    bool buscarRec(NoTreap* no, int chave, long long &operacoes);
    NoTreap* removerRec(NoTreap* no, int chave, long long &operacoes);
    void destruirArvore(NoTreap* no);

public:
    Treap();
    ~Treap();
    void inserir(int chave, long long &operacoes);
    bool buscar(int chave, long long &operacoes);
    void remover(int chave, long long &operacoes);
    long long getConsumoMemoriaEmBytes();
};

#endif