#include "Treap.hpp"

Treap::Treap() {
    raiz = nullptr;
    totalNos = 0;
}

Treap::~Treap() {
    destruirArvore(raiz);
}

void Treap::destruirArvore(NoTreap* no) {
    if (no) {
        destruirArvore(no->esq);
        destruirArvore(no->dir);
        delete no;
    }
}

NoTreap* Treap::rotacaoDireita(NoTreap* y, long long &operacoes) {
    operacoes++; 
    NoTreap* x = y->esq;
    NoTreap* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    return x;
}

NoTreap* Treap::rotacaoEsquerda(NoTreap* x, long long &operacoes) {
    operacoes++;
    NoTreap* y = x->dir;
    NoTreap* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    return y;
}

NoTreap* Treap::inserirRec(NoTreap* no, int chave, long long &operacoes) {
    if (!no) {
        totalNos++; 
        return new NoTreap(chave);
    }

    operacoes++; // comparação de chaves

    if (chave <= no->chave) {
        no->esq = inserirRec(no->esq, chave, operacoes);
        
        // mantém a propriedade de Max-Heap usando as prioridades
        if (no->esq->prioridade > no->prioridade) {
            no = rotacaoDireita(no, operacoes);
        }
    } else {
        no->dir = inserirRec(no->dir, chave, operacoes);
        
        if (no->dir->prioridade > no->prioridade) {
            no = rotacaoEsquerda(no, operacoes);
        }
    }
    return no;
}

void Treap::inserir(int chave, long long &operacoes) {
    raiz = inserirRec(raiz, chave, operacoes);
}

bool Treap::buscarRec(NoTreap* no, int chave, long long &operacoes) {
    if (!no) return false;

    operacoes++;

    if (no->chave == chave) return true;
    
    if (chave < no->chave)
        return buscarRec(no->esq, chave, operacoes);
    
    return buscarRec(no->dir, chave, operacoes);
}

bool Treap::buscar(int chave, long long &operacoes) {
    return buscarRec(raiz, chave, operacoes);
}

NoTreap* Treap::removerRec(NoTreap* no, int chave, long long &operacoes) {
    if (!no) return no;

    operacoes++; 

    if (chave < no->chave) {
        no->esq = removerRec(no->esq, chave, operacoes);
    } else if (chave > no->chave) {
        no->dir = removerRec(no->dir, chave, operacoes);
    } else {
        if (!no->esq) {
            NoTreap* temp = no->dir;
            delete no;
            totalNos--;
            return temp;
        } else if (!no->dir) {
            NoTreap* temp = no->esq;
            delete no;
            totalNos--;
            return temp;
        }

        if (no->esq->prioridade > no->dir->prioridade) {
            no = rotacaoDireita(no, operacoes);
            no->dir = removerRec(no->dir, chave, operacoes);
        } else {
            no = rotacaoEsquerda(no, operacoes);
            no->esq = removerRec(no->esq, chave, operacoes);
        }
    }
    return no;
}

void Treap::remover(int chave, long long &operacoes) {
    raiz = removerRec(raiz, chave, operacoes);
}

long long Treap::getConsumoMemoriaEmBytes() {
    return totalNos * sizeof(NoTreap);
}