#ifndef DESCONTO_H
#define DESCONTO_H

class Desconto
{
public:
    virtual double calcularDesconto(double total) const = 0;
    virtual ~Desconto();
};

#endif // DESCONTO_H
