#include <iostream>
using namespace std;

void MenaraHanoi(int JumlahPiringan, char MenaraAsal, char MenaraTujuan, char MenaraSementara) {
     if (JumlahPiringan == 1) {
        cout << "Pindahkan piringan 1 dari " << MenaraAsal << " ke " << MenaraTujuan << endl;
        return;
    }

    MenaraHanoi(JumlahPiringan - 1, MenaraAsal, MenaraSementara, MenaraTujuan);
    cout << "Pindahkan piringan " << JumlahPiringan << " dari " << MenaraAsal << " ke " << MenaraTujuan << endl;
    MenaraHanoi(JumlahPiringan -1, MenaraSementara, MenaraTujuan, MenaraAsal);
}

int main() {
    int JumlahPiringan;
    cout << "Masukkan jumlah piringan ";
    cin >> JumlahPiringan;
    if (JumlahPiringan <= 0) {
        cout << "Jumlah piringan harus lebih besar dari 0!" << endl;
        return 1;
    }

// Memanggil fungsi hanoi dengan menara awal A, menara tujuan T, dan menara sementara S
    MenaraHanoi(JumlahPiringan, 'A', 'T', 'S');
    return 0;
}