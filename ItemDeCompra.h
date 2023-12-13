#ifndef ITEMDECOMPRA_H
#define ITEMDECOMPRA_H

#include "Produto.h"

class ItemDeCompra
{
private:
    Produto *produto;
    int quantidade;

public:
    void setProduto(Produto *novoProduto, int novaQuantidade);
    Produto *getProduto() const;
    int getQuantidade() const;
    void calcularValorTotal() const;
};

#endif // ITEMDECOMPRA_H
