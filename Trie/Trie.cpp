#include "Trie.hpp"
#include <iostream>

NoTrie* Trie::criarNo() {
    NoTrie* novoNo = new NoTrie();
    novoNo->fimPalavra = false;
    
    for(int i = 0; i < TAM_ALFABETO; i++) {
        novoNo->filhos[i] = nullptr;
    }
    return novoNo;
}

Trie::Trie() {
    raiz = criarNo();
}

void Trie::inserir(std::string palavra, long long &operacoes) {
    NoTrie* atual = raiz;
    
    for (char c : palavra) {
        operacoes++; // operações realizadas
        
        int indice = c - 'a';
        if (atual->filhos[indice] == nullptr) {
            atual->filhos[indice] = criarNo();
        }
        atual = atual->filhos[indice];
    }
    atual->fimPalavra = true;
}

bool Trie::buscar(std::string palavra, long long &operacoes) {
    NoTrie* atual = raiz;
    for (char c : palavra) {
        operacoes++; // conta o pulo
        int indice = c - 'a';
        if (atual->filhos[indice] == nullptr) {
            return false;
        }
        atual = atual->filhos[indice];
    }
    return atual->fimPalavra;
}

void Trie::remover(std::string palavra, long long &operacoes) {
    NoTrie* atual = raiz;
    for (char c : palavra) {
        operacoes++; // conta o pulo
        int indice = c - 'a';
        if (atual->filhos[indice] == nullptr) {
            return;
        }
        atual = atual->filhos[indice];
    }
    
    // desmarca o nó final
    if (atual->fimPalavra) {
        atual->fimPalavra = false;
    }
}