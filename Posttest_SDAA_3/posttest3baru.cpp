#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Penyewa {
    int id;
    string nama;
    int umur;
    string apartemen;
    int durasiSewa;
    float hargaSewa;
};

struct Node {
    Penyewa penyewa; 
    Node* next;      
};

Node* head = nullptr;
int jumlahPenyewa = 0; 

const string fileName = "data_penyewa.txt";

void tambahPenyewa() {
    Penyewa penyewaBaru;
    penyewaBaru.id = jumlahPenyewa + 1;

    cout << "Masukkan nama penyewa: ";
    cin.ignore();
    getline(cin, penyewaBaru.nama);

    cout << "Masukkan umur penyewa: ";
    cin >> penyewaBaru.umur;

    cout << "Masukkan apartemen yang disewa: ";
    cin.ignore();
    getline(cin, penyewaBaru.apartemen);

    cout << "Masukkan durasi sewa (bulan): ";
    cin >> penyewaBaru.durasiSewa;

    cout << "Masukkan harga sewa per bulan: ";
    cin >> penyewaBaru.hargaSewa;

    Node* newNode = new Node;
    newNode->penyewa = penyewaBaru;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    jumlahPenyewa++;
    cout << "Penyewa berhasil ditambahkan!" << endl;
}

void tampilkanPenyewa() {
    if (jumlahPenyewa == 0) {
        cout << "Belum ada penyewa yang terdaftar." << endl;
        return;
    }

    Node* temp = head;
    while (temp != nullptr) {
        cout << "ID: " << temp->penyewa.id << endl;
        cout << "Nama: " << temp->penyewa.nama << endl;
        cout << "Umur: " << temp->penyewa.umur << endl;
        cout << "Apartemen: " << temp->penyewa.apartemen << endl;
        cout << "Durasi Sewa: " << temp->penyewa.durasiSewa << " bulan" << endl;
        cout << "Harga Sewa: " << temp->penyewa.hargaSewa << " per bulan" << endl;
        cout << "-----------------------------" << endl;
        temp = temp->next;
    }
}

Node* cariPenyewaBerdasarkanID(int id) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->penyewa.id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void updatePenyewa() {
    int id;
    cout << "Masukkan ID penyewa yang akan diupdate: ";
    cin >> id;

    Node* penyewaDitemukan = cariPenyewaBerdasarkanID(id);
    if (penyewaDitemukan != nullptr) {
        cout << "Masukkan data baru untuk penyewa " << penyewaDitemukan->penyewa.nama << endl;

        cout << "Masukkan umur baru: ";
        cin >> penyewaDitemukan->penyewa.umur;

        cout << "Masukkan apartemen baru: ";
        cin.ignore();
        getline(cin, penyewaDitemukan->penyewa.apartemen);

        cout << "Masukkan durasi sewa baru (bulan): ";
        cin >> penyewaDitemukan->penyewa.durasiSewa;

        cout << "Masukkan harga sewa baru: ";
        cin >> penyewaDitemukan->penyewa.hargaSewa;

        cout << "Data penyewa berhasil diupdate!" << endl;
    } else {
        cout << "Penyewa dengan ID " << id << " tidak ditemukan." << endl;
    }
}

void hapusPenyewa() {
    int id;
    cout << "Masukkan ID penyewa yang akan dihapus: ";
    cin >> id;

    Node* temp = head;
    Node* prev = nullptr;

    while (temp != nullptr && temp->penyewa.id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Penyewa dengan ID " << id << " tidak ditemukan." << endl;
        return;
    }

    if (prev == nullptr) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
    jumlahPenyewa--;
    cout << "Penyewa berhasil dihapus!" << endl;
}

void cariPenyewaBerdasarkanNama() {
    string nama;
    cout << "Masukkan nama penyewa yang akan dicari: ";
    cin.ignore();
    getline(cin, nama);

    Node* temp = head;
    bool ditemukan = false;

    while (temp != nullptr) {
        if (temp->penyewa.nama == nama) {
            cout << "ID: " << temp->penyewa.id << endl;
            cout << "Nama: " << temp->penyewa.nama << endl;
            cout << "Umur: " << temp->penyewa.umur << endl;
            cout << "Apartemen: " << temp->penyewa.apartemen << endl;
            cout << "Durasi Sewa: " << temp->penyewa.durasiSewa << " bulan" << endl;
            cout << "Harga Sewa: " << temp->penyewa.hargaSewa << " per bulan" << endl;
            cout << "-----------------------------" << endl;
            ditemukan = true;
        }
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "Penyewa dengan nama " << nama << " tidak ditemukan." << endl;
    }
}

void simpanKeFile() {
    ofstream fileOut(fileName);
    Node* temp = head;
    while (temp != nullptr) {
        fileOut << temp->penyewa.id << endl;
        fileOut << temp->penyewa.nama << endl;
        fileOut << temp->penyewa.umur << endl;
        fileOut << temp->penyewa.apartemen << endl;
        fileOut << temp->penyewa.durasiSewa << endl;
        fileOut << temp->penyewa.hargaSewa << endl;
        temp = temp->next;
    }
    fileOut.close();
    cout << "Data berhasil disimpan ke file." << endl;
}

void bacaDariFile() {
    ifstream fileIn(fileName);
    if (fileIn.is_open()) {
        while (!fileIn.eof()) {
            Penyewa penyewaBaru;
            fileIn >> penyewaBaru.id;
            fileIn.ignore();
            getline(fileIn, penyewaBaru.nama);
            fileIn >> penyewaBaru.umur;
            fileIn.ignore();
            getline(fileIn, penyewaBaru.apartemen);
            fileIn >> penyewaBaru.durasiSewa;
            fileIn >> penyewaBaru.hargaSewa;

            if (!fileIn.fail()) {
                Node* newNode = new Node;
                newNode->penyewa = penyewaBaru;
                newNode->next = nullptr;

                if (head == nullptr) {
                    head = newNode;
                } else {
                    Node* temp = head;
                    while (temp->next != nullptr) {
                        temp = temp->next;
                    }
                    temp->next = newNode;
                }

                jumlahPenyewa++;
            }
        }
        fileIn.close();
        cout << "Data berhasil dibaca dari file." << endl;
    } else {
        cout << "File tidak ditemukan, mulai dengan data kosong." << endl;
    }
}

int main() {
    bacaDariFile();

    int pilihan;
    do {
        cout << "\n=== Program Pendataan Sewa Apartemen ===" << endl;
        cout << "1. Tambah Penyewa" << endl;
        cout << "2. Tampilkan Penyewa" << endl;
        cout << "3. Update Penyewa" << endl;
        cout << "4. Hapus Penyewa" << endl;
        cout << "5. Cari Penyewa Berdasarkan Nama" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPenyewa();
                break;
            case 2:
                tampilkanPenyewa();
                break;
            case 3:
                updatePenyewa();
                break;
            case 4:
                hapusPenyewa();
                break;
            case 5:
                cariPenyewaBerdasarkanNama();
                break;
            case 0:
                cout << "Menyimpan data ke file..." << endl;
                simpanKeFile();
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    } while (pilihan != 0);

    return 0;
}
