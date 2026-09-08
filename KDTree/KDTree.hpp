#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <vector>
#include <iostream>
#include <cmath> // cálculos de distância
#include <limits> // inicializar distâncias infinitas

const int K = 2; // dimensionalidade

struct NoKD {
    std::vector<double> coordenadas;
    NoKD* esquerda;
    NoKD* direita;

    NoKD(std::vector<double> coords) {
        coordenadas = coords;
        esquerda = nullptr;
        direita = nullptr;
    }
};

class KDTree {
private:
    NoKD* raiz;
    long long totalNos;

    NoKD* inserirRec(NoKD* no, std::vector<double> ponto, unsigned profundidade, long long &operacoes);
    bool buscarRec(NoKD* no, std::vector<double> ponto, unsigned profundidade, long long &operacoes);
    
    // funções auxiliares para remoção
    NoKD* encontrarMinimoRec(NoKD* no, int dimBuscada, unsigned profundidade, long long &operacoes);
    NoKD* removerRec(NoKD* no, std::vector<double> ponto, unsigned profundidade, long long &operacoes);
    
    // auxiliares para cálculo de geometria (Busca do Vizinho Mais Próximo)
    double calcularDistancia(std::vector<double>& p1, std::vector<double>& p2);
    void vizinhoMaisProximoRec(NoKD* no, std::vector<double> alvo, unsigned profundidade, long long &operacoes, NoKD*& melhor, double& melhorDistancia);

public:
    KDTree();
    void inserir(std::vector<double> ponto, long long &operacoes);
    bool buscar(std::vector<double> ponto, long long &operacoes);
    void remover(std::vector<double> ponto, long long &operacoes);
    std::vector<double> buscarVizinhoMaisProximo(std::vector<double> ponto, long long &operacoes);
    long long getConsumoMemoriaEmBytes();
};

#endif