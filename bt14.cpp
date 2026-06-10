#include <iostream>
#include <algorithm>
using namespace std;

struct NutAVL {
    int giatri;
    NutAVL* trai;
    NutAVL* phai;
    int chieucao;

    NutAVL(int e, NutAVL* l, NutAVL* r, int h) {
        giatri = e;
        trai = l;
        phai = r;
        chieucao = h;
    }
};

int chieuCao(NutAVL* t) {
    return t == NULL ? -1 : t->chieucao;
}


