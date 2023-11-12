//TESTE DE ENDEREÇO:
//#include <iostream>
//#include <vector>
//int*  endereco(int& rval) { return &rval; }
//int** endereco(int* pval) { return &pval; }
//
//int main() {
//	int a = 5;
//	int& r = a;
//	int* p = &a;
//	std::cout << "Endereco de a eh o mesmo de rval DENTRO da funcao? ";
//	std::cout << ((&a == endereco(r) ? "Sim" : "Nao")) << '\n';
//	std::cout << "Endereco de a              = " << &a << '\n';
//	std::cout << "End. rval DENTRO da funcao = " << endereco(r) << "\n\n";
//
//	std::cout << "Endereco de p eh o mesmo de pval DENTRO da funcao? ";
//	std::cout << ((&p == endereco(p) ? "Sim" : "Nao")) << '\n';
//	std::cout << "Endereco de p              = " << &p << '\n';
//	std::cout << "End. pval DENTRO da funcao = " << endereco(p) << "\n\n";
//
//	return 0;
//}