#include "IntMatrix.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <nome_do_arquivo>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Não foi possível abrir o arquivo: " << argv[1] << "\n";
        return 1;
    }

    size_t rows, cols;
    if (!(file >> rows >> cols)) {
        std::cerr << "Erro ao ler dimensões da matriz\n";
        return 1;
    }

    try {
        IntMatrix matrix(rows, cols);
        matrix.readFromStream(file);

        int command, param1, param2;
        while (std::cin >> command >> param1 >> param2) {
            try {
                if (command == 1) {
                    size_t pos = (param1 == 0) ? 0 : param1;
                    matrix.addRow(pos, param2);
                    matrix.print(std::cout);
                } else if (command == 2) {
                    size_t pos = (param1 == 0) ? 0 : param1;
                    matrix.addColumn(pos, param2);
                    matrix.print(std::cout);
                } else {
                    std::cerr << "Comando inválido: " << command << "\n";
                    return 3;
                }
            } catch (const std::bad_alloc& e) {
                std::cerr << "Falha na alocação de memória: " << e.what() << "\n";
                return 2;
            } catch (const std::exception& e) {
                std::cerr << "Erro: " << e.what() << "\n";
                return 3;
            }
        }
    } catch (const std::bad_alloc& e) {
        std::cerr << "Falha na alocação de memória: " << e.what() << "\n";
        return 2;
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
