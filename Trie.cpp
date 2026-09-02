#include "Trie.hpp"
#include <iostream>

NoTrie* Trie::criarNo() {
    NoTrie* novoNo = new NoTrie();
    novoNo->fimPalavra = false;
    
    for(int i = 0; i < TAM_ALFABETO; i++) {
        novoNo->filhos[i] = nullptr;
    }
    return novoNo;
};

Trie::Trie() {
    raiz = criarNo();
}

void Trie::inserir(std::string palavra) {
    NoTrie* atual = raiz;
    for(char c : palavra) {
        int indice = c - 'a';
        if(atual->filhos[indice] == nullptr) {
            atual->filhos[indice] = criarNo();
        }
        atual = atual->filhos[indice];
    }
    atual->fimPalavra = true;
}