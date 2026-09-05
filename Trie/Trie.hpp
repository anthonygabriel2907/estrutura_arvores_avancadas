#pragma once
#include <string>

#define TAM_ALFABETO 26

struct NoTrie {
    NoTrie* filhos[TAM_ALFABETO];
    bool fimPalavra;
};

class Trie {
    private:
        NoTrie* raiz;
        long long totalNos; // contador de nos

        NoTrie* criarNo();

    public:
    Trie();
    void inserir(std::string palavra, long long &operacoes);
    bool buscar(std::string palavra, long long &operacoes);
    void remover(std::string palavra, long long &operacoes);

    long long getConsumoMemoriaEmBytes();
};