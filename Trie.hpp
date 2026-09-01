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
        NoTrie* criarNo();

    public:
    Trie();
    void inserir(std::string palavra);
    bool buscar(std::string palavra);
    void remover(std::string palavra);
};