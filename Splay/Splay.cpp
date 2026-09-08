#include "Splay.hpp"

Splay::Splay() {
    raiz = nullptr;
    totalNos = 0;
}

void Splay::rotacaoEsquerda(NoSplay* x, long long &operacoes) {
    operacoes++;
    NoSplay* y = x->direita;
    x->direita = y->esquerda;
    
    if (y->esquerda != nullptr) {
        y->esquerda->pai = x;
    }
    
    y->pai = x->pai;
    if (x->pai == nullptr) {
        raiz = y;
    } else if (x == x->pai->esquerda) {
        x->pai->esquerda = y;
    } else {
        x->pai->direita = y;
    }
    
    y->esquerda = x;
    x->pai = y;
}

void Splay::rotacaoDireita(NoSplay* x, long long &operacoes) {
    operacoes++;
    NoSplay* y = x->esquerda;
    x->esquerda = y->direita;
    
    if (y->direita != nullptr) {
        y->direita->pai = x;
    }
    
    y->pai = x->pai;
    if (x->pai == nullptr) {
        raiz = y;
    } else if (x == x->pai->direita) {
        x->pai->direita = y;
    } else {
        x->pai->esquerda = y;
    }
    
    y->direita = x;
    x->pai = y;
}

void Splay::splay(NoSplay* x, long long &operacoes) {
    while (x->pai != nullptr) {
        operacoes++; 
        
        if (x->pai->pai == nullptr) {
            // Zig (Apenas o pai existe)
            if (x == x->pai->esquerda) {
                rotacaoDireita(x->pai, operacoes);
            } else {
                rotacaoEsquerda(x->pai, operacoes);
            }
        } else {
            NoSplay* p = x->pai;
            NoSplay* g = p->pai; // Avô
            
            if (x == p->esquerda && p == g->esquerda) {
                // Zig-Zig (esquerda-esquerda)
                rotacaoDireita(g, operacoes);
                rotacaoDireita(p, operacoes);
            } else if (x == p->direita && p == g->direita) {
                // Zig-Zig (direita-direita)
                rotacaoEsquerda(g, operacoes);
                rotacaoEsquerda(p, operacoes);
            } else if (x == p->direita && p == g->esquerda) {
                // Zig-Zag (esquerda-direita)
                rotacaoEsquerda(p, operacoes);
                rotacaoDireita(g, operacoes);
            } else {
                // Zig-Zag (direita-esquerda)
                rotacaoDireita(p, operacoes);
                rotacaoEsquerda(g, operacoes);
            }
        }
    }
}

void Splay::inserir(int chave, long long &operacoes) {
    NoSplay* novo = new NoSplay(chave);
    NoSplay* y = nullptr;
    NoSplay* x = raiz;

    while (x != nullptr) {
        operacoes++; 
        y = x;
        if (novo->chave < x->chave) {
            x = x->esquerda;
        } else if (novo->chave > x->chave) {
            x = x->direita;
        } else {
            splay(x, operacoes);
            delete novo;
            return;
        }
    }

    novo->pai = y;
    if (y == nullptr) {
        raiz = novo;
    } else if (novo->chave < y->chave) {
        y->esquerda = novo;
    } else {
        y->direita = novo;
    }

    totalNos++;
    
    splay(novo, operacoes);
}

bool Splay::buscar(int chave, long long &operacoes) {
    NoSplay* atual = raiz;
    NoSplay* ultimo = nullptr;

    while (atual != nullptr) {
        operacoes++;
        ultimo = atual;
        
        if (chave < atual->chave) {
            atual = atual->esquerda;
        } else if (chave > atual->chave) {
            atual = atual->direita;
        } else {
            // traz o nó acessado para a raiz
            splay(atual, operacoes);
            return true;
        }
    }

    // se a chave não é encontrada,
    // o último nó acessado deve ser levado para a raiz.
    if (ultimo != nullptr) {
        splay(ultimo, operacoes);
    }
    
    return false;
}

void Splay::remover(int chave, long long &operacoes) {
    if (raiz == nullptr) return;

    // a busca traz o nó (se existir) para a raiz, facilitando a remoção
    if (!buscar(chave, operacoes)) {
        return;
    }

    NoSplay* temp = raiz;

    if (raiz->esquerda == nullptr) {
        raiz = raiz->direita;
        if (raiz != nullptr) {
            raiz->pai = nullptr;
        }
    } else {
        NoSplay* x = raiz->esquerda;
        x->pai = nullptr; // desconecta da raiz atual
        
        // encontra o maior elemento da subárvore esquerda
        while (x->direita != nullptr) {
            operacoes++; // Conta a descida
            x = x->direita;
        }
        
        // faz o splay desse maior elemento (agora ele não tem filho à direita)
        splay(x, operacoes);
        
        //cConecta a subárvore direita original à nova raiz
        x->direita = temp->direita;
        if (temp->direita != nullptr) {
            temp->direita->pai = x;
        }
        raiz = x;
    }

    delete temp;
    totalNos--;
}

long long Splay::getConsumoMemoriaEmBytes() {
    return totalNos * sizeof(NoSplay);
}

// função auxiliar para deletar os nós recursivamente da memória
void Splay::destruirArvore(NoSplay* no) {
    if (no != nullptr) {
        destruirArvore(no->esquerda);
        destruirArvore(no->direita);
        delete no;
    }
}

// destrutor
Splay::~Splay() {
    destruirArvore(raiz);
}