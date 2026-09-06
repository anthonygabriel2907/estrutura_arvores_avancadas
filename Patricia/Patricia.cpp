#include "Patricia.hpp"
#include <iostream>

NoPatricia* Patricia::criarNo(std::string prefixo) {
    NoPatricia* novoNo = new NoPatricia();
    novoNo->prefixo = prefixo;
    novoNo->fimPalavra = false;
    
    for(int i = 0; i < TAM_ALFABETO; i++) {
        novoNo->filhos[i] = nullptr;
    }

    totalNos++; // conta o nó alocado
    return novoNo;
}

Patricia::Patricia() {
    totalNos = 0;
    // a raiz armazena uma string vazia, ela serve apenas como ponto de partida
    raiz = criarNo(""); 
}

long long Patricia::getConsumoMemoriaEmBytes() {
    return totalNos * sizeof(NoPatricia);
}

bool Patricia::buscar(std::string palavra, long long &operacoes) {
    NoPatricia* atual = raiz;
    int i = 0; // ponteiro para iterar pela palavra que estamos buscando

    while (i < palavra.length()) {
        operacoes++;
        
        char c = palavra[i];
        int indice = c - 'a';

        // se não há filho para a próxima letra, a palavra não existe
        if (atual->filhos[indice] == nullptr) {
            return false;
        }

        // descemos para o filho e avaliamos o prefixo dele
        atual = atual->filhos[indice];
        std::string prefixoNo = atual->prefixo;
        int j = 0; // ponteiro para iterar pelo prefixo do nó atual

        // compara os caracteres do prefixo do nó com a palavra
        while (j < prefixoNo.length() && i < palavra.length() && prefixoNo[j] == palavra[i]) {
            operacoes++; // conta a comparação de caracteres
            i++;
            j++;
        }

        // se o laço parou antes de terminar o prefixo do nó, ela não existe.
        if (j < prefixoNo.length()) {
            return false;
        }
    }

    

    return atual->fimPalavra;
}

void Patricia::inserir(std::string palavra, long long &operacoes) {
    NoPatricia* atual = raiz;
    int i = 0; // índice para iterar na palavra que está sendo inserida

    while (i < palavra.length()) {
        operacoes++;
        char c = palavra[i];
        int indice = c - 'a';

        // não existe ramificação para a letra atual.
        // criamos um único nó armazenando todo o resto da palavra
        if (atual->filhos[indice] == nullptr) {
            NoPatricia* novo = criarNo(palavra.substr(i));
            novo->fimPalavra = true;
            atual->filhos[indice] = novo;
            return;
        }

        // existe um caminho, então vamos avaliá-lo.
        NoPatricia* proximo = atual->filhos[indice];
        std::string prefixoNo = proximo->prefixo;
        int j = 0;

        // encontrar o prefixo comum mais longo
        // comparamos a palavra com o prefixo do nó atual até onde forem iguais
        while (j < prefixoNo.length() && i < palavra.length() && prefixoNo[j] == palavra[i]) {
            operacoes++;
            i++;
            j++;
        }

        // a palavra divergiu no meio do prefixo do nó atual. Precisamos quebrar este nó em dois.
        if (j < prefixoNo.length()) {
            // 1. Cria um novo nó que vai receber o pedaço restante do prefixo antigo
            NoPatricia* noSplit = criarNo(prefixoNo.substr(j));
            noSplit->fimPalavra = proximo->fimPalavra;

            // transfere todos os filhos do nó original para este novo nó
            for (int k = 0; k < TAM_ALFABETO; k++) {
                noSplit->filhos[k] = proximo->filhos[k];
                proximo->filhos[k] = nullptr; 
            }

            // o nó original é atualizado para conter apenas o prefixo comum
            proximo->prefixo = prefixoNo.substr(0, j);
            proximo->fimPalavra = false; // Temporariamente não é fim de palavra

            // o novo nó (com o resto do prefixo antigo) vira filho do nó original
            proximo->filhos[noSplit->prefixo[0] - 'a'] = noSplit;

            if (i == palavra.length()) {
                // a nova palavra terminou exatamente no ponto de corte
                proximo->fimPalavra = true;
            } else {
                // a nova palavra tem letras sobrando. Criamos um nó para esse resto.
                NoPatricia* novoResto = criarNo(palavra.substr(i));
                novoResto->fimPalavra = true;
                proximo->filhos[novoResto->prefixo[0] - 'a'] = novoResto;
            }
            return;
        }

        // consumimos todo o prefixo do nó, mas ainda tem letras na palavra.
        // atualizamos o ponteiro e o loop 'while' recomeça para descer ao próximo nível.
        atual = proximo;
    }

    // a palavra inteira foi consumida e é exatamente igual a um caminho já existente.
    // marcamos o último nó visitado como o final de uma palavra válida.
    atual->fimPalavra = true;
}

void Patricia::remover(std::string palavra, long long &operacoes) {
    NoPatricia* pai = nullptr;
    int indiceNoPai = -1;
    NoPatricia* atual = raiz;
    int i = 0;

    // descemos na árvore para encontrar o nó alvo
    while (i < palavra.length()) {
        operacoes++;
        char c = palavra[i];
        int indice = c - 'a';

        if (atual->filhos[indice] == nullptr) return; // A palavra não existe

        pai = atual;
        indiceNoPai = indice;
        atual = atual->filhos[indice];

        std::string prefixoNo = atual->prefixo;
        int j = 0;
        
        while (j < prefixoNo.length() && i < palavra.length() && prefixoNo[j] == palavra[i]) {
            operacoes++;
            i++; 
            j++;
        }

        // se o prefixo divergiu antes do fim, a palavra não está na árvore
        if (j < prefixoNo.length()) return; 
    }

    //sSe encontramos o nó, mas ele não marca o fim de uma palavra, não fazemos nada
    if (!atual->fimPalavra) return; 

    // A Remoção Lógica (Desmarca o fim da palavra)
    atual->fimPalavra = false;

    // contagem de filhos do nó atual para decidir a reorganização estrutural
    int qtdFilhos = 0;
    int indiceUnicoFilho = -1;
    for (int k = 0; k < TAM_ALFABETO; k++) {
        if (atual->filhos[k] != nullptr) {
            qtdFilhos++;
            indiceUnicoFilho = k;
        }
    }

    // nó folha (0 filhos). Podemos excluí-lo da memória.
    if (qtdFilhos == 0) {
        delete atual;
        totalNos--; // Reduz o contador de memória
        if (pai != nullptr) pai->filhos[indiceNoPai] = nullptr;

        // como excluímos um filho, o pai pode ter ficado com apenas 1 filho.
        // se o pai não for raiz e não for fim de palavra, ele deve se fundir com o filho restante.
        if (pai != nullptr && pai != raiz && !pai->fimPalavra) {
            int filhosDoPai = 0;
            int indiceFilhoDoPai = -1;
            for (int k = 0; k < TAM_ALFABETO; k++) {
                if (pai->filhos[k] != nullptr) {
                    filhosDoPai++;
                    indiceFilhoDoPai = k;
                }
            }
            
            // faz o merge do pai com seu único filho
            if (filhosDoPai == 1) {
                NoPatricia* filhoUnico = pai->filhos[indiceFilhoDoPai];
                pai->prefixo += filhoUnico->prefixo; // Junta as strings
                pai->fimPalavra = filhoUnico->fimPalavra;
                
                for (int k = 0; k < TAM_ALFABETO; k++) {
                    pai->filhos[k] = filhoUnico->filhos[k];
                }
                delete filhoUnico;
                totalNos--;
            }
        }
    }
    // nó interno com exatamente 1 filho. 
    // como ele deixou de ser fim de palavra, ele não tem mais utilidade sozinho. Fundimos com o filho.
    else if (qtdFilhos == 1) {
        NoPatricia* filhoUnico = atual->filhos[indiceUnicoFilho];
        atual->prefixo += filhoUnico->prefixo;
        atual->fimPalavra = filhoUnico->fimPalavra;
        
        for (int k = 0; k < TAM_ALFABETO; k++) {
            atual->filhos[k] = filhoUnico->filhos[k];
        }
        delete filhoUnico;
        totalNos--;
    }
}