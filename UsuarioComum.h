#ifndef USUARIOCOMUM_H
#define USUARIOCOMUM_H

#include "Usuario.h"

class UsuarioComum : public Usuario
{
public:
    void adicionarProduto(std::vector<Produto *> &produtos, CarrinhoDeCompra &carrinho, BancoDadosProdutos &bancoDeDados) const override;
    bool isAdmin() const override;
    virtual void removerProduto(CarrinhoDeCompra &carrinho) override;
};

#endif
