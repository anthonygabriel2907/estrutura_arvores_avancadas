# Estruturas em Árvores Avançadas

**Trabalho Individual — Algoritmos e Estruturas de Dados II**
CEFET-MG, Campus V — Divinópolis, Brasil

**Autor:** Anthony Gabriel Sotto Mayor Silva

---

## Sobre o trabalho

Este repositório contém a implementação, a instrumentação de desempenho e os dados experimentais de cinco estruturas de dados em árvore especializadas, desenvolvidas como aprofundamento além das estruturas clássicas de Árvore Binária de Busca (BST) e Árvore AVL. O trabalho tem como objetivo comparar diferentes estratégias de organização, busca, balanceamento e indexação de dados, relacionando fundamentação teórica, decisões de projeto e comportamento experimental observado sob diferentes volumes e distribuições de entrada.

As estruturas implementadas são:

| Estrutura | Pasta | Operações implementadas |
|---|---|---|
| Trie (Árvore de Prefixos) | [`Trie/`](./Trie) | Inserção, busca, remoção lógica |
| Patricia (Radix Tree compacta) | [`Patricia/`](./Patricia) | Inserção com divisão de prefixos (*split*), busca, remoção com re-compactação (*merge*) |
| Splay Tree (árvore autoajustável) | [`Splay/`](./Splay) | Inserção, busca, remoção, rotações de auto-ajuste (*splay*) |
| Treap (Tree + Heap) | [`Treap/`](./Treap) | Inserção, busca, remoção por rebaixamento via rotações |
| KD-Tree (K=2) | [`KDTree/`](./KDTree) | Inserção, busca exata, remoção (algoritmo de Bentley), busca do vizinho mais próximo |

O relatório técnico completo — com fundamentação teórica, decisões de projeto, análise de complexidade assintótica, demonstração visual e discussão crítica dos resultados — está disponível separadamente. Em caso de dúvida sobre qualquer detalhe de implementação não coberto por este README, consulte o [repositório no GitHub](https://github.com/anthonygabriel2907/estrutura_arvores_avancadas) para a versão mais atual do código.

## Estrutura do repositório
