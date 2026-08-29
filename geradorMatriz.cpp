#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Matriz base corrigida com as linhas duplicadas para dar 
    // espessura (formato de retângulo) aos blocos do mapa clássico.
    vector<string> base = {
        "111111111111111111111", // 0: Parede superior
        "100000000010000000001", // 1: Caminho
        "101110111010111011101", // 2: 4 Blocos superiores (Metade de cima)
        "101110111010111011101", // 3: 4 Blocos superiores (Metade de baixo - dá espessura)
        "100000000000000000001", // 4: Caminho
        "101110101111101011101", // 5: Bloco lateral e Topo do T
        "101110101111101011101", // 6: Bloco lateral e Topo do T (Metade de baixo)
        "100000100010001000001", // 7: Caminho
        "111110111010111011111", // 8: Base do T e Borda lateral
        "111110100000001011111", // 9: Caminho em volta da casa dos fantasmas
        "111110101101101011111", // 10: Teto da casa dos fantasmas
        "000000001000100000000", // 11: Caminho do teletransporte
        "111110101111101011111", // 12: Chão da casa dos fantasmas
        "111110100000001011111", // 13: Caminho debaixo da casa
        "111110101111101011111", // 14: Topo do T inferior
        "100000000010000000001", // 15: Caminho
        "101110111010111011101", // 16: Blocos inferiores
        "101110111010111011101", // 17: Blocos inferiores (Metade de baixo - dá espessura)
        "100010000000000010001", // 18: Caminho
        "111010101111101010111", // 19: Blocos em formato L
        "100000100010001000001", // 20: Caminho
        "101111111010111111101", // 21: Parede inferior grossa
        "101111111010111111101", // 22: Parede inferior grossa (Metade de baixo)
        "100000000000000000001", // 23: Caminho final
        "111111111111111111111"  // 24: Borda de baixo
    };

    int R = base.size();
    int C = base[0].size();
    int nR = 2 * R - 1;
    int nC = 2 * C - 1;

    vector<string> nova(nR, string(nC, ' '));

    for (int r = 0; r < nR; r++) {
        for (int c = 0; c < nC; c++) {
            if (r % 2 == 0 && c % 2 == 0) {
                nova[r][c] = base[r/2][c/2];
            } else if (r % 2 == 0 && c % 2 != 0) {
                char esq = base[r/2][c/2];
                char dir = base[r/2][c/2 + 1];
                if (esq == dir) nova[r][c] = esq;
                else nova[r][c] = '5';
            } else if (r % 2 != 0 && c % 2 == 0) {
                char cima = base[r/2][c/2];
                char baixo = base[r/2 + 1][c/2];
                if (cima == baixo) nova[r][c] = cima;
                else nova[r][c] = '5';
            } else {
                char c1 = base[r/2][c/2];
                char c2 = base[r/2][c/2 + 1];
                char c3 = base[r/2 + 1][c/2];
                char c4 = base[r/2 + 1][c/2 + 1];
                if (c1 == c2 && c2 == c3 && c3 == c4) nova[r][c] = c1;
                else nova[r][c] = '5';
            }
        }
    }

    // A segunda dimensão ganha +1 para o terminador de string '\0' do C/C++
    cout << "char mapa[" << nR << "][" << nC + 1 << "] = {\n";
    for (int r = 0; r < nR; r++) {
        cout << "  \"" << nova[r] << "\"";
        if (r < nR - 1) cout << ",";
        cout << "\n";
    }
    cout << "};\n";

    return 0;
}