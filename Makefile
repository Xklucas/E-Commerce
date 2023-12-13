all: vai

vai: main.o Admin.o BancoDadosProdutos.o CarrinhoDeCompra.o Desconto.o DescontoFixo.o ItemDeCompra.o Produto.o Usuario.o UsuarioComum.o
	g++ -o vai main.o Admin.o BancoDadosProdutos.o CarrinhoDeCompra.o Desconto.o DescontoFixo.o ItemDeCompra.o Produto.o Usuario.o UsuarioComum.o

main.o: main.cpp
	g++ -c main.cpp

Admin.o: Admin.cpp Admin.h
	g++ -c Admin.cpp

BancoDadosProdutos.o: BancoDadosProdutos.cpp BancoDadosProdutos.h
	g++ -c BancoDadosProdutos.cpp

CarrinhoDeCompra.o: CarrinhoDeCompra.cpp CarrinhoDeCompra.h
	g++ -c CarrinhoDeCompra.cpp

Desconto.o: Desconto.cpp Desconto.h
	g++ -c Desconto.cpp

DescontoFixo.o: DescontoFixo.cpp DescontoFixo.h
	g++ -c DescontoFixo.cpp

ItemDeCompra.o: ItemDeCompra.cpp ItemDeCompra.h
	g++ -c ItemDeCompra.cpp

Produto.o: Produto.cpp Produto.h
	g++ -c Produto.cpp

Usuario.o: Usuario.cpp Usuario.h
	g++ -c Usuario.cpp

UsuarioComum.o: UsuarioComum.cpp UsuarioComum.h
	g++ -c UsuarioComum.cpp

clean:
	rm -rf *.o vai
