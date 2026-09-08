#include "KDTree.hpp"

KDTree::KDTree() {
    raiz = nullptr;
    totalNos = 0;
}

NoKD* KDTree::inserirRec(NoKD* no, std::vector<double> ponto, unsigned profundidade, long long &operacoes) {
    if (no == nullptr) {
        totalNos++; // conta o nó alocado na RAM
        return new NoKD(ponto);
    }

    operacoes++; // conta a comparação realizada

    // calcula a dimensão atual: 0 para X, 1 para Y (alternância de eixos)
    unsigned dimensao = profundidade % K;

    if (ponto[dimensao] < no->coordenadas[dimensao]) {
        no->esquerda = inserirRec(no->esquerda, ponto, profundidade + 1, operacoes);
    } else {
        no->direita = inserirRec(no->direita, ponto, profundidade + 1, operacoes);
    }

    return no;
}

void KDTree::inserir(std::vector<double> ponto, long long &operacoes) {
    raiz = inserirRec(raiz, ponto, 0, operacoes);
}

long long KDTree::getConsumoMemoriaEmBytes() {
    return totalNos * sizeof(NoKD);
}

// busca eexata
bool KDTree::buscarRec(NoKD* no, std::vector<double> ponto, unsigned profundidade, long long &operacoes) {
    if (no == nullptr) return false;
    
    operacoes++; // Conta a comparação do nó

    // Verifica se os pontos são exatamente iguais
    bool iguais = true;
    for (int i = 0; i < K; ++i) {
        if (no->coordenadas[i] != ponto[i]) {
            iguais = false;
            break;
        }
    }
    if (iguais) return true;

    // Se não for igual, decide para qual lado descer
    unsigned dimensao = profundidade % K;
    if (ponto[dimensao] < no->coordenadas[dimensao]) {
        return buscarRec(no->esquerda, ponto, profundidade + 1, operacoes);
    } else {
        return buscarRec(no->direita, ponto, profundidade + 1, operacoes);
    }
}

bool KDTree::buscar(std::vector<double> ponto, long long &operacoes) {
    return buscarRec(raiz, ponto, 0, operacoes);
}

// remoção
NoKD* KDTree::encontrarMinimoRec(NoKD* no, int dimBuscada, unsigned profundidade, long long &operacoes) {
    if (no == nullptr) return nullptr;
    
    operacoes++;
    unsigned dimAtual = profundidade % K;

    if (dimAtual == dimBuscada) {
        if (no->esquerda == nullptr) return no;
        return encontrarMinimoRec(no->esquerda, dimBuscada, profundidade + 1, operacoes);
    }

    NoKD* esq = encontrarMinimoRec(no->esquerda, dimBuscada, profundidade + 1, operacoes);
    NoKD* dir = encontrarMinimoRec(no->direita, dimBuscada, profundidade + 1, operacoes);
    NoKD* res = no;

    if (esq != nullptr && esq->coordenadas[dimBuscada] < res->coordenadas[dimBuscada]) res = esq;
    if (dir != nullptr && dir->coordenadas[dimBuscada] < res->coordenadas[dimBuscada]) res = dir;

    return res;
}

NoKD* KDTree::removerRec(NoKD* no, std::vector<double> ponto, unsigned profundidade, long long &operacoes) {
    if (no == nullptr) return nullptr;

    operacoes++;
    unsigned dimAtual = profundidade % K;

    bool iguais = true;
    for (int i = 0; i < K; ++i) {
        if (no->coordenadas[i] != ponto[i]) iguais = false;
    }

    if (iguais) {
        // Caso 1: Nó tem filho à direita
        if (no->direita != nullptr) {
            NoKD* min = encontrarMinimoRec(no->direita, dimAtual, profundidade + 1, operacoes);
            no->coordenadas = min->coordenadas;
            no->direita = removerRec(no->direita, min->coordenadas, profundidade + 1, operacoes);
        }
        // Caso 2: Nó tem filho à esquerda (transformamos em subárvore direita e repetimos)
        else if (no->esquerda != nullptr) {
            NoKD* min = encontrarMinimoRec(no->esquerda, dimAtual, profundidade + 1, operacoes);
            no->coordenadas = min->coordenadas;
            no->direita = removerRec(no->esquerda, min->coordenadas, profundidade + 1, operacoes);
            no->esquerda = nullptr;
        }
        // Caso 3: É uma folha
        else {
            delete no;
            totalNos--; // Atualiza contagem de memória
            return nullptr;
        }
        return no;
    }

    // Busca o nó a ser removido
    if (ponto[dimAtual] < no->coordenadas[dimAtual]) {
        no->esquerda = removerRec(no->esquerda, ponto, profundidade + 1, operacoes);
    } else {
        no->direita = removerRec(no->direita, ponto, profundidade + 1, operacoes);
    }
    return no;
}

void KDTree::remover(std::vector<double> ponto, long long &operacoes) {
    raiz = removerRec(raiz, ponto, 0, operacoes);
}

// busca vizinho mais proximo
double KDTree::calcularDistancia(std::vector<double>& p1, std::vector<double>& p2) {
    double soma = 0;
    for (int i = 0; i < K; ++i) {
        soma += (p1[i] - p2[i]) * (p1[i] - p2[i]);
    }
    return soma; // Retorna a distância ao quadrado para otimizar processamento
}

void KDTree::vizinhoMaisProximoRec(NoKD* no, std::vector<double> alvo, unsigned profundidade, long long &operacoes, NoKD*& melhor, double& melhorDistancia) {
    if (no == nullptr) return;
    
    operacoes++;
    double distAtual = calcularDistancia(no->coordenadas, alvo);

    if (melhor == nullptr || distAtual < melhorDistancia) {
        melhor = no;
        melhorDistancia = distAtual;
    }

    unsigned dimAtual = profundidade % K;
    NoKD* proximoCaminho = nullptr;
    NoKD* outroCaminho = nullptr;

    if (alvo[dimAtual] < no->coordenadas[dimAtual]) {
        proximoCaminho = no->esquerda;
        outroCaminho = no->direita;
    } else {
        proximoCaminho = no->direita;
        outroCaminho = no->esquerda;
    }

    vizinhoMaisProximoRec(proximoCaminho, alvo, profundidade + 1, operacoes, melhor, melhorDistancia);

    // verifica se há alguma chance do vizinho estar do outro lado da hiper-reta/plano
    double distEixo = (alvo[dimAtual] - no->coordenadas[dimAtual]) * (alvo[dimAtual] - no->coordenadas[dimAtual]);
    if (distEixo < melhorDistancia) {
        vizinhoMaisProximoRec(outroCaminho, alvo, profundidade + 1, operacoes, melhor, melhorDistancia);
    }
}

std::vector<double> KDTree::buscarVizinhoMaisProximo(std::vector<double> ponto, long long &operacoes) {
    NoKD* melhor = nullptr;
    double melhorDistancia = std::numeric_limits<double>::max();
    vizinhoMaisProximoRec(raiz, ponto, 0, operacoes, melhor, melhorDistancia);
    
    if (melhor != nullptr) return melhor->coordenadas;
    return {}; // arvore vazia
}