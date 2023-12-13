#include "ItemDeCompra.h"
#include <iostream>

void ItemDeCompra::setProduto(Produto *novoProduto, int novaQuantidade)
{
    produto = novoProduto;
    quantidade = novaQuantidade;
}

Produto *ItemDeCompra::getProduto() const
{
    return produto;
}

int ItemDeCompra::getQuantidade() const
{
    return quantidade;
}

void ItemDeCompra::calcularValorTotal() const
{
    double total = quantidade * produto->preco;
    std::cout << "Valor total do item: " << total << std::endl;
}
