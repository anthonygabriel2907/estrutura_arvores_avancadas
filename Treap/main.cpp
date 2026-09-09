#include "Treap.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>

void executarExperimento(std::string nomeArquivo, std::ofstream &saida) {
    Treap minhaArvore;
    std::ifstream arquivo(nomeArquivo);
    int chave;

    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir o arquivo de entrada: " << nomeArquivo << std::endl;
        return;
    }

    std::cout << "\nTestando arquivo: " << nomeArquivo << " ---" << std::endl;
    saida << "\nTestando arquivo: " << nomeArquivo << " ---" << std::endl;

    // vetor para armazenar as chaves lidas e garantir a mesma ordem na busca e remoção
    std::vector<int> chaves;

    // inserção
    auto inicioInsercao = std::chrono::high_resolution_clock::now();
    int contInsercoes = 0;
    long long opsInsercao = 0;
    
    while (arquivo >> chave) {
        chaves.push_back(chave);
        minhaArvore.inserir(chave, opsInsercao);
        contInsercoes++;
    }
    auto fimInsercao = std::chrono::high_resolution_clock::now();
    auto tempoInsercao = std::chrono::duration_cast<std::chrono::milliseconds>(fimInsercao - inicioInsercao).count();

    std::cout << "Insercao: " << contInsercoes << " elementos em " << tempoInsercao << " ms. (Operacoes: " << opsInsercao << ")" << std::endl;
    saida << "Insercao: " << contInsercoes << " elementos em " << tempoInsercao << " ms. (Operacoes: " << opsInsercao << ")" << std::endl;

    // busca
    auto inicioBusca = std::chrono::high_resolution_clock::now();
    int contBuscas = 0;
    long long opsBusca = 0;
    
    for (int c : chaves) {
        minhaArvore.buscar(c, opsBusca);
        contBuscas++;
    }
    auto fimBusca = std::chrono::high_resolution_clock::now();
    auto tempoBusca = std::chrono::duration_cast<std::chrono::milliseconds>(fimBusca - inicioBusca).count();

    std::cout << "Busca:    " << contBuscas << " elementos em " << tempoBusca << " ms. (Operacoes: " << opsBusca << ")" << std::endl;
    saida << "Busca:    " << contBuscas << " elementos em " << tempoBusca << " ms. (Operacoes: " << opsBusca << ")" << std::endl;

    // consumo de memoria
    long long memoriaBytes = minhaArvore.getConsumoMemoriaEmBytes();
    double memoriaKB = memoriaBytes / 1024.0;
    double memoriaMB = memoriaKB / 1024.0;

    std::cout << "Memoria:  " << memoriaBytes << " bytes (" << memoriaKB << " KB / " << memoriaMB << " MB)" << std::endl;
    saida << "Memoria:  " << memoriaBytes << " bytes (" << memoriaKB << " KB / " << memoriaMB << " MB)" << std::endl;

    // remoção
    auto inicioRemocao = std::chrono::high_resolution_clock::now();
    int contRemocoes = 0;
    long long opsRemocao = 0;
    
    for (int c : chaves) {
        minhaArvore.remover(c, opsRemocao);
        contRemocoes++;
    }
    auto fimRemocao = std::chrono::high_resolution_clock::now();
    auto tempoRemocao = std::chrono::duration_cast<std::chrono::milliseconds>(fimRemocao - inicioRemocao).count();

    std::cout << "Remocao:  " << contRemocoes << " elementos em " << tempoRemocao << " ms. (Operacoes: " << opsRemocao << ")" << std::endl;
    saida << "Remocao:  " << contRemocoes << " elementos em " << tempoRemocao << " ms. (Operacoes: " << opsRemocao << ")" << std::endl;

    arquivo.close();
}

int main() {
    srand(time(NULL));

    std::ofstream arquivoSaida("output/resultados_treap.txt");
    if (!arquivoSaida.is_open()) {
        std::cout << "Erro ao criar arquivo de saida na pasta output!" << std::endl;
        return 1;
    }

    std::cout << "Iniciando testes da Treap:" << std::endl;

    executarExperimento("input/dados_teste_treap/tam_10/insercao_aleatoria.txt", arquivoSaida);
    executarExperimento("input/dados_teste_treap/tam_10/insercao_crescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_treap/tam_10/insercao_decrescente.txt", arquivoSaida);

    executarExperimento("input/dados_teste_treap/tam_100/insercao_aleatoria.txt", arquivoSaida);
    executarExperimento("input/dados_teste_treap/tam_100/insercao_crescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_treap/tam_100/insercao_decrescente.txt", arquivoSaida);

    executarExperimento("input/dados_teste_treap/tam_1000/insercao_aleatoria.txt", arquivoSaida);
    executarExperimento("input/dados_teste_treap/tam_1000/insercao_crescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_treap/tam_1000/insercao_decrescente.txt", arquivoSaida);

    executarExperimento("input/dados_teste_treap/tam_10000/insercao_aleatoria.txt", arquivoSaida);
    executarExperimento("input/dados_teste_treap/tam_10000/insercao_crescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_treap/tam_10000/insercao_decrescente.txt", arquivoSaida);

    executarExperimento("input/dados_teste_treap/tam_100000/insercao_aleatoria.txt", arquivoSaida);
    executarExperimento("input/dados_teste_treap/tam_100000/insercao_crescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_treap/tam_100000/insercao_decrescente.txt", arquivoSaida);

    executarExperimento("input/dados_teste_treap/tam_1000000/insercao_aleatoria.txt", arquivoSaida);
    executarExperimento("input/dados_teste_treap/tam_1000000/insercao_crescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_treap/tam_1000000/insercao_decrescente.txt", arquivoSaida);
    
    arquivoSaida.close();
    std::cout << "\nTestes finalizados. Resultados salvos em 'output/resultados_treap.txt'" << std::endl;
    
    return 0;
}