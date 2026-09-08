#ifndef SPLAY_HPP
#define SPLAY_HPP

#include <iostream>

struct NoSplay {
    int chave;
    NoSplay* esquerda;
    NoSplay* direita;
    NoSplay* pai;

    NoSplay(int valor) {
        chave = valor;
        esquerda = nullptr;
        direita = nullptr;
        pai = nullptr;
    }
};

class Splay {
private:
    NoSplay* raiz;
    long long totalNos;

    // métodos essenciais de reorganização
    void rotacaoEsquerda(NoSplay* x, long long &operacoes);
    void rotacaoDireita(NoSplay* x, long long &operacoes);
    
    // traz o nó 'x' para a raiz
    void splay(NoSplay* x, long long &operacoes);

    // auxiliares
    void destruirArvore(NoSplay* no);
    void imprimirEstruturaRecursivo(NoSplay* no, int espaco);

public:
    Splay();
    ~Splay();

    void inserir(int chave, long long &operacoes);
    bool buscar(int chave, long long &operacoes);
    void remover(int chave, long long &operacoes);

    long long getConsumoMemoriaEmBytes();
    

};

#endif