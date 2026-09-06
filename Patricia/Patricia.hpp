#ifndef PATRICIA_HPP
#define PATRICIA_HPP

#include <string>

#define TAM_ALFABETO 26

struct NoPatricia {
    std::string prefixo;
    bool fimPalavra;
    NoPatricia* filhos[TAM_ALFABETO];
};

class Patricia {
private:
    NoPatricia* raiz;
    long long totalNos;

    NoPatricia* criarNo(std::string prefixo);

public:
    Patricia();
    
    void inserir(std::string palavra, long long &operacoes);
    bool buscar(std::string palavra, long long &operacoes);
    void remover(std::string palavra, long long &operacoes);
    
    long long getConsumoMemoriaEmBytes();
};

#endif