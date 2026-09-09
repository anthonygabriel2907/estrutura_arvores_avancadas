#include "Trie.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

void executarExperimento(std::string nomeArquivo, std::ofstream &saida) {
    Trie minhaArvore;
    std::ifstream arquivo(nomeArquivo);
    std::string palavra;

    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir o arquivo de entrada: " << nomeArquivo << std::endl;
        return;
    }

    std::cout << "\nTestando arquivo: " << nomeArquivo << " ---" << std::endl;
    saida << "\nTestando arquivo: " << nomeArquivo << " ---" << std::endl;

    // inserção
    auto inicioInsercao = std::chrono::high_resolution_clock::now();
    int contInsercoes = 0;
    long long opsInsercao = 0;
    
    while (std::getline(arquivo, palavra)) {
        minhaArvore.inserir(palavra, opsInsercao);
        contInsercoes++;
    }
    auto fimInsercao = std::chrono::high_resolution_clock::now();
    auto tempoInsercao = std::chrono::duration_cast<std::chrono::milliseconds>(fimInsercao - inicioInsercao).count();

    std::cout << "Insercao: " << contInsercoes << " palavras em " << tempoInsercao << " ms. (Operacoes: " << opsInsercao << ")" << std::endl;
    saida << "Insercao: " << contInsercoes << " palavras em " << tempoInsercao << " ms. (Operacoes: " << opsInsercao << ")" << std::endl;

    arquivo.clear();
    arquivo.seekg(0, std::ios::beg);

    // busca
    auto inicioBusca = std::chrono::high_resolution_clock::now();
    int contBuscas = 0;
    long long opsBusca = 0;
    
    while (std::getline(arquivo, palavra)) {
        minhaArvore.buscar(palavra, opsBusca);
        contBuscas++;
    }
    auto fimBusca = std::chrono::high_resolution_clock::now();
    auto tempoBusca = std::chrono::duration_cast<std::chrono::milliseconds>(fimBusca - inicioBusca).count();

    std::cout << "Busca:    " << contBuscas << " palavras em " << tempoBusca << " ms. (Operacoes: " << opsBusca << ")" << std::endl;
    saida << "Busca:    " << contBuscas << " palavras em " << tempoBusca << " ms. (Operacoes: " << opsBusca << ")" << std::endl;

    arquivo.clear();
    arquivo.seekg(0, std::ios::beg);

    // remoção
    auto inicioRemocao = std::chrono::high_resolution_clock::now();
    int contRemocoes = 0;
    long long opsRemocao = 0;
    
    while (std::getline(arquivo, palavra)) {
        minhaArvore.remover(palavra, opsRemocao);
        contRemocoes++;
    }
    auto fimRemocao = std::chrono::high_resolution_clock::now();
    auto tempoRemocao = std::chrono::duration_cast<std::chrono::milliseconds>(fimRemocao - inicioRemocao).count();

    std::cout << "Remocao:  " << contRemocoes << " palavras em " << tempoRemocao << " ms. (Operacoes: " << opsRemocao << ")" << std::endl;
    saida << "Remocao:  " << contRemocoes << " palavras em " << tempoRemocao << " ms. (Operacoes: " << opsRemocao << ")" << std::endl;

    // consumo de memoria
    long long memoriaBytes = minhaArvore.getConsumoMemoriaEmBytes();
    double memoriaKB = memoriaBytes / 1024.0;
    double memoriaMB = memoriaKB / 1024.0;

    std::cout << "Memoria:  " << memoriaBytes << " bytes (" << memoriaKB << " KB / " << memoriaMB << " MB)" << std::endl;
    saida << "Memoria:  " << memoriaBytes << " bytes (" << memoriaKB << " KB / " << memoriaMB << " MB)" << std::endl;

    arquivo.close();
}

int main() {
    std::ofstream arquivoSaida("output/resultados_trie.txt");
    if (!arquivoSaida.is_open()) {
        std::cout << "Erro ao criar arquivo de saida na pasta output!" << std::endl;
        return 1;
    }

    std::cout << "Iniciando testes da Trie" << std::endl;

    executarExperimento("input/dados_teste_string/tam_10/dicionario.txt", arquivoSaida);
    executarExperimento("input/dados_teste_string/tam_10/aleatorio.txt", arquivoSaida);
    executarExperimento("input/dados_teste_string/tam_10/prefixo_comum.txt", arquivoSaida);

    executarExperimento("input/dados_teste_string/tam_100/dicionario.txt", arquivoSaida);
    executarExperimento("input/dados_teste_string/tam_100/aleatorio.txt", arquivoSaida);
    executarExperimento("input/dados_teste_string/tam_100/prefixo_comum.txt", arquivoSaida);
    
    executarExperimento("input/dados_teste_string/tam_1000/aleatorio.txt", arquivoSaida);
    executarExperimento("input/dados_teste_string/tam_1000/dicionario.txt", arquivoSaida);
    executarExperimento("input/dados_teste_string/tam_1000/prefixo_comum.txt", arquivoSaida);

    executarExperimento("input/dados_teste_string/tam_10000/aleatorio.txt", arquivoSaida);
    executarExperimento("input/dados_teste_string/tam_10000/dicionario.txt", arquivoSaida);
    executarExperimento("input/dados_teste_string/tam_10000/prefixo_comum.txt", arquivoSaida);

    executarExperimento("input/dados_teste_string/tam_100000/aleatorio.txt", arquivoSaida);
    executarExperimento("input/dados_teste_string/tam_100000/dicionario.txt", arquivoSaida);
    executarExperimento("input/dados_teste_string/tam_100000/prefixo_comum.txt", arquivoSaida);

    executarExperimento("input/dados_teste_string/tam_1000000/aleatorio.txt", arquivoSaida);
    executarExperimento("input/dados_teste_string/tam_1000000/prefixo_comum.txt", arquivoSaida);
    
    arquivoSaida.close();
    std::cout << "\nTestes finalizados. Resultados salvos em 'output/resultados_trie.txt'" << std::endl;
    
    return 0;
}