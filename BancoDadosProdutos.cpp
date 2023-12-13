#include "BancoDadosProdutos.h"
#include "Produto.h"

#include <algorithm>
#include <iostream>
#include <fstream>

void BancoDadosProdutos::adicionarProduto(Produto *p)
{
    produtos.push_back(p);
}

void BancoDadosProdutos::removerProduto(Produto *p)
{
    auto it = find_if(produtos.begin(), produtos.end(), [p](const Produto *produto)
                      { return produto == p; });
    if (it != produtos.end())
    {
        produtos.erase(it);
        std::cout << "Produto removido do banco de dados: " << p->nome << std::endl;
    }
}
// atualiza a quantidade de produtos ainda restantes no estoque
void BancoDadosProdutos::atualizarQuantidade(Produto *p, int quantidade)
{
    if (quantidade > 0 || (p->quantidade + quantidade) >= 0)
    {
        p->quantidade += quantidade;
    }
    else
    {
        std::cout << p->nome << "." << std::endl;
    }
}
//função que sobrescreve os valores no banco de dados
void BancoDadosProdutos::escreverCSV(const std::string &arquivoCSV)
{
    std::ofstream arquivo(arquivoCSV);
    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo CSV para escrita." << std::endl;
        return;
    }

    // Escreve os cabeçalhos
    arquivo << "Nome,Preco,Quantidade,Categoria" << std::endl;

    // Escreve os dados dos produtos
    for (const auto &produto : produtos)
    {
        arquivo << produto->nome << "," << produto->preco << "," << produto->quantidade << "," << produto->categoria << std::endl;
    }

    arquivo.close();
    std::cout << "Dados escritos no arquivo CSV." << std::endl;
}

BancoDadosProdutos::~BancoDadosProdutos()
{
    // Libera a memória alocada para os produtos
    for (const auto &produto : produtos)
    {
        delete produto;
    }
}
