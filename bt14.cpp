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

// Xoay don phai (truong hop trai - trai)
void xoayConTrai(NutAVL*& k2) {
    NutAVL* k1 = k2->trai;
    k2->trai = k1->phai;
    k1->phai = k2;
    k2->chieucao = max(chieuCao(k2->trai), chieuCao(k2->phai)) + 1;
    k1->chieucao = max(chieuCao(k1->trai), k2->chieucao) + 1;
    k2 = k1;
}

// Xoay don trai (truong hop phai - phai)
void xoayConPhai(NutAVL*& k1) {
    NutAVL* k2 = k1->phai;
    k1->phai = k2->trai;
    k2->trai = k1;
    k1->chieucao = max(chieuCao(k1->trai), chieuCao(k1->phai)) + 1;
    k2->chieucao = max(chieuCao(k2->phai), k1->chieucao) + 1;
    k1 = k2;
}

// Xoay kep trai - phai (truong hop trai - phai)
void xoayKepTraiPhai(NutAVL*& k3) {
    xoayConPhai(k3->trai);
    xoayConTrai(k3);
}

// Xoay kep phai - trai (truong hop phai - trai)
void xoayKepPhaiTrai(NutAVL*& k1) {
    xoayConTrai(k1->phai);
    xoayConPhai(k1);
}
