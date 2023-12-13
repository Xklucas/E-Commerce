#ifndef ADMIN_H
#define ADMIN_H

#include "Usuario.h"
#include <vector>

class Admin : public Usuario
{
public:
    void adicionarProduto(std::vector<Produto *> &produtos, CarrinhoDeCompra &carrinho, BancoDadosProdutos &bancoDeDados) const override;
    bool isAdmin() const override;
    virtual void removerProduto(CarrinhoDeCompra &carrinho) override;

private:
    void adicionarAoCarrinho(std::vector<Produto *> &produtos, CarrinhoDeCompra &carrinho) const;
    void adicionarAoBancoDeDados(std::vector<Produto *> &produtos, BancoDadosProdutos &bancoDeDados) const;
};

#endif // ADMIN_H
