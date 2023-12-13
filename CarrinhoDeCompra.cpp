#include "CarrinhoDeCompra.h"
#include "ItemDeCompra.h"
#include "Produto.h"
#include "Desconto.h"
#include "BancoDadosProdutos.h"
#include "Usuario.h"

#include <map>
#include <iostream>
#include <algorithm>

CarrinhoDeCompra::CarrinhoDeCompra(Desconto *desc) : desconto(desc), bancoDeDados(nullptr) {}

CarrinhoDeCompra::CarrinhoDeCompra(Desconto *desc, BancoDadosProdutos *bd) : desconto(desc), bancoDeDados(bd) {}

void CarrinhoDeCompra::adicionarProduto(Produto *p, int quantidade)
{
    // Verifica se a quantidade desejada está disponível
    if (quantidade > p->quantidade)
    {
        std::cout << "Quantidade indisponível de " << p->nome << "." << std::endl;
        return;
    }

    // Verifica se o produto já está no carrinho
    auto it = std::find_if(itens.begin(), itens.end(), [p](const ItemDeCompra &item)
                           { return item.getProduto() == p; });

    if (it != itens.end())
    {
        // Se o produto já estiver no carrinho, apenas atualiza a quantidade
        it->setProduto(p, it->getQuantidade() + quantidade);
    }
    else
    {
        // Se o produto não estiver no carrinho, adiciona um novo item
        ItemDeCompra item;
        item.setProduto(p, quantidade);
        itens.push_back(item);
    }
    p->quantidade -= quantidade;
    std::cout << quantidade << " " << p->nome << "(s) adicionado(s) ao carrinho." << std::endl;

    // Exibe informações do produto adicionado ao carrinho
    p->exibirDetalhes();
}

void CarrinhoDeCompra::removerProduto(int numeroProduto)
{
    if (numeroProduto > 0 && numeroProduto <= static_cast<int>(itens.size()))
    {
        itens.erase(itens.begin() + numeroProduto - 1);
        std::cout << "Produto removido do carrinho." << std::endl;
    }
    else
    {
        std::cout << "Número de produto inválido." << std::endl;
    }
}

void CarrinhoDeCompra::exibirProdutosComprados() const
{
    std::cout << "\nProdutos comprados:" << std::endl;

    // Cria um mapa para rastrear a quantidade de cada produto
    std::map<std::string, int> quantidadePorProduto;

    for (const auto &item : itens)
    {
        const std::string &nomeProduto = item.getProduto()->nome;
        quantidadePorProduto[nomeProduto] += item.getQuantidade();
    }

    // Exibe os produtos agregados
    for (const auto &par : quantidadePorProduto)
    {
        std::cout << "Produto: " << par.first << ", Quantidade: " << par.second << std::endl;
    }
}

// Itens do carrinho sem permitir modificar
const std::vector<ItemDeCompra> &CarrinhoDeCompra::getItens() const
{
    return itens;
}

// Total
void CarrinhoDeCompra::calcularTotal()
{
    double total = 0.0;
    for (const auto &item : itens)
    {
        total += item.getQuantidade() * item.getProduto()->preco;
    }
    std::cout << "Total: " << total << std::endl;
}

void CarrinhoDeCompra::aplicarDesconto()
{
    double total = 0.0;
    for (const auto &item : itens)
    {
        total += item.getQuantidade() * item.getProduto()->preco;
    }

    double totalComDesconto = desconto->calcularDesconto(total);
    std::cout << "Total com desconto: " << totalComDesconto << std::endl;
}

CarrinhoDeCompra::~CarrinhoDeCompra()
{
    // Libera a memória alocada para os itens no carrinho
    for (const auto &item : itens)
    {
        delete item.getProduto();
    }
}
