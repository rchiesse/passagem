//TESTE DE VELOCIDADE DE ACESSO (2 INDIREÇÕES)
#include <iostream>
#include <chrono>
#include <functional>

void timestamp(const std::string& message) {
	const char TIMESTAMP_COLUMNS = 26;
	char timestamp_string[TIMESTAMP_COLUMNS];
	std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	ctime_s(timestamp_string, sizeof timestamp_string, &t);
	std::cout << std::endl << timestamp_string << message;
}

struct no { // Lista encadeada (minimalista)
	int val = 0;
	no* prox = nullptr;
};
void apagarLista(no* target) {
	no* aux;
	do {
		aux = target->prox;
		delete target;
		target = aux;
	} while (target);
}
void inserirViaPont(no** elem, no* lista) {
	no* aux = lista->prox;
	lista->prox = *elem;
	(*elem)->prox = aux;
}
void inserirViaRef(no& elem, no& lista) {
	no* aux = lista.prox;
	lista.prox = &elem;
	elem.prox = aux;
}
double tempoGasto(std::function<void(no**, no*)> metodo, no* lista, int tam) {
	clock_t t = clock();
	while (--tam) {
		no* novoItem = new no;
		metodo(&novoItem, lista);
	}
	return (double)(clock()) - t;
}
double tempoGasto(std::function<void(no&, no&)> metodo, no* lista, int tam) {
	clock_t t = clock();
	while (--tam) {
		no* novoItem = new no;
		metodo(*novoItem, *lista);
	}
	return (double)(clock()) - t;
}

void stats(double& tempo, double& melhor, double& pior, double& media) {
	if (tempo < melhor)  melhor = tempo;
	else if (tempo > pior) pior = tempo;
	media += tempo;
}

int main() {
	constexpr int REP = (int)2e9; //2 bilhões
	constexpr int TAM = (int)5e7; //50 milhões
	constexpr int rodadas = 32;
	no* inicioP;
	no* inicioR;

	double melhorREF = INT_MAX, piorREF = 0;
	double melhorPONT = INT_MAX, piorPONT = 0;
	double tempoMedioREF = 0;
	double tempoMedioPONT = 0;
	double decorrido;
	timestamp("Inicio");
	std::cout << "\nCalculando o tempo medio de acesso para " << rodadas << " rodadas...\n";
	for (size_t k = 0; k < rodadas; k++) {
		std::cout << "\n\t\t** Rodada " << k + 1 << " **\n";

		std::cout << "Por ponteiro: ";
		inicioP = new no;
		decorrido = tempoGasto(&inserirViaPont, inicioP, TAM); //Operação central, sem I/O interno.
		std::cout << decorrido << "ms. Apagando... ";
		apagarLista(inicioP);
		std::cout << "OK.\n";
		stats(decorrido, melhorPONT, piorPONT, tempoMedioPONT);

		std::cout << "Por referencia: ";
		inicioR = new no;
		decorrido = tempoGasto(&inserirViaRef, inicioR, TAM); //Operação central, sem I/O interno.
		std::cout << decorrido << "ms. Apagando... ";
		apagarLista(inicioR);
		std::cout << "OK.\n";
		stats(decorrido, melhorREF, piorREF, tempoMedioREF);
	}
	tempoMedioREF -= (melhorREF + piorREF);
	tempoMedioPONT -= (melhorPONT + piorPONT);
	std::cout << "\nTempo medio por referencia (melhor e pior descartados): " << (tempoMedioREF / (rodadas - 2)) << "ms.";
	std::cout << "\nTempo medio por ponteiro (melhor e pior descartados):   " << (tempoMedioPONT / (rodadas - 2)) << "ms.";
	timestamp("Fim.");
	return 0;
}
