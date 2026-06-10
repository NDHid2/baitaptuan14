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

void canBang(NutAVL*& t) {
    if (t == NULL) return;

    if (chieuCao(t->trai) - chieuCao(t->phai) > 1) {
        if (chieuCao(t->trai->trai) >= chieuCao(t->trai->phai)) {
            xoayConTrai(t);
        } else {
            xoayKepTraiPhai(t);
        }
    } else if (chieuCao(t->phai) - chieuCao(t->trai) > 1) {
        if (chieuCao(t->phai->phai) >= chieuCao(t->phai->trai)) {
            xoayConPhai(t);
        } else {
            xoayKepPhaiTrai(t);
        }
    }

    t->chieucao = max(chieuCao(t->trai), chieuCao(t->phai)) + 1;
}

void chen(int x, NutAVL*& t) {
    if (t == NULL) {
        t = new NutAVL(x, NULL, NULL, 0);
    } else if (x < t->giatri) {
        chen(x, t->trai);
    } else if (x > t->giatri) {
        chen(x, t->phai);
    }
    // Neu bang thi khong lam gi (khong chen trung)
    canBang(t);
}

// Duyet giua (LNR) - in ra gia tri tang dan
void duyetGiua(NutAVL* t) {
    if (t != NULL) {
        duyetGiua(t->trai);
        cout << t->giatri << " ";
        duyetGiua(t->phai);
    }
}

int main() {
    NutAVL* goc = NULL;

    int arr[] = {32, 51, 27, 83, 96, 11, 45, 75, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Chen lan luot cac gia tri: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
        chen(arr[i], goc);
    }
    cout << endl;

    cout << "Duyet cay AVL theo thu tu LNR (tang dan): ";
    duyetGiua(goc);
    cout << endl;

    return 0;
}
