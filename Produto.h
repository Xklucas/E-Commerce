#ifndef PRODUTO_H
#define PRODUTO_H

#include <iostream>
#include <vector>
#include <string>

class ItemDeCompra; // Declaração antecipada

class Produto
{
public:
    std::string nome;
    double preco;
    int quantidade;
    std::string categoria;

    virtual void adicionarAoCarrinho(int quantidade, std::vector<ItemDeCompra> &carrinho);
    virtual void exibirDetalhes() const;

    virtual ~Produto() = default;
};

#endif // PRODUTO_H
