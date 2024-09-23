#include <iostream>
#include <fstream> // Untuk file I/O
#include <string>
using namespace std;

// Struct untuk menyimpan data penyewa apartemen
struct Penyewa {
    int id;                 // ID unik penyewa
    string nama;            // Nama penyewa
    int umur;               // Umur penyewa
    string apartemen;       // Apartemen yang disewa
    int durasiSewa;         // Durasi sewa dalam bulan
    float hargaSewa;        // Harga sewa per bulan
};

// Maksimal data penyewa
const int MAX_PENYEWA = 100;

// Array untuk menyimpan data penyewa
Penyewa penyewaList[MAX_PENYEWA];
int jumlahPenyewa = 0; // Jumlah penyewa saat ini

// Nama file tempat penyimpanan data
const string fileName = "data_penyewa.txt";

// Fungsi untuk menambahkan penyewa baru
void tambahPenyewa(Penyewa *list) {
    if (jumlahPenyewa < MAX_PENYEWA) {
        Penyewa penyewaBaru;
        penyewaBaru.id = jumlahPenyewa + 1; 2

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

        list[jumlahPenyewa] = penyewaBaru;
        jumlahPenyewa++;

        cout << "Penyewa berhasil ditambahkan!" << endl;
    } else {
        cout << "Data penyewa sudah penuh!" << endl;
    }
}

// Fungsi untuk menampilkan data semua penyewa
void tampilkanPenyewa(Penyewa *list) {
    if (jumlahPenyewa == 0) {
        cout << "Belum ada penyewa yang terdaftar." << endl;
        return;
    }
    
    for (int i = 0; i < jumlahPenyewa; i++) {
        cout << "ID: " << list[i].id << endl;
        cout << "Nama: " << list[i].nama << endl;
        cout << "Umur: " << list[i].umur << endl;
        cout << "Apartemen: " << list[i].apartemen << endl;
        cout << "Durasi Sewa: " << list[i].durasiSewa << " bulan" << endl;
        cout << "Harga Sewa: " << list[i].hargaSewa << " per bulan" << endl;
        cout << "-----------------------------" << endl;
    }
}

// Fungsi untuk mencari penyewa berdasarkan ID
int cariPenyewaBerdasarkanID(Penyewa *list, int id) {
    for (int i = 0; i < jumlahPenyewa; i++) {
        if (list[i].id == id) {
            return i;
        }
    }
    return -1; // Tidak ditemukan
}

// Fungsi untuk mengupdate data penyewa
void updatePenyewa(Penyewa *list) {
    int id;
    cout << "Masukkan ID penyewa yang akan diupdate: ";
    cin >> id;

    int index = cariPenyewaBerdasarkanID(list, id);
    if (index != -1) {
        cout << "Masukkan data baru untuk penyewa " << list[index].nama << endl;

        cout << "Masukkan umur baru: ";
        cin >> list[index].umur;

        cout << "Masukkan apartemen baru: ";
        cin.ignore();
        getline(cin, list[index].apartemen);

        cout << "Masukkan durasi sewa baru (bulan): ";
        cin >> list[index].durasiSewa;

        cout << "Masukkan harga sewa baru: ";
        cin >> list[index].hargaSewa;

        cout << "Data penyewa berhasil diupdate!" << endl;
    } else {
        cout << "Penyewa dengan ID " << id << " tidak ditemukan." << endl;
    }
}

// Fungsi untuk menghapus penyewa
void hapusPenyewa(Penyewa *list) {
    int id;
    cout << "Masukkan ID penyewa yang akan dihapus: ";
    cin >> id;

    int index = cariPenyewaBerdasarkanID(list, id);
    if (index != -1) {
        for (int i = index; i < jumlahPenyewa - 1; i++) {
            list[i] = list[i + 1]; // Geser data penyewa
        }
        jumlahPenyewa--;
        cout << "Penyewa berhasil dihapus!" << endl;
    } else {
        cout << "Penyewa dengan ID " << id << " tidak ditemukan." << endl;
    }
}

// Fungsi untuk mencari penyewa berdasarkan nama
void cariPenyewaBerdasarkanNama(Penyewa *list) {
    string nama;
    cout << "Masukkan nama penyewa yang akan dicari: ";
    cin.ignore();
    getline(cin, nama);

    bool ditemukan = false;
    for (int i = 0; i < jumlahPenyewa; i++) {
        if (list[i].nama == nama) {
            cout << "ID: " << list[i].id << endl;
            cout << "Nama: " << list[i].nama << endl;
            cout << "Umur: " << list[i].umur << endl;
            cout << "Apartemen: " << list[i].apartemen << endl;
            cout << "Durasi Sewa: " << list[i].durasiSewa << " bulan" << endl;
            cout << "Harga Sewa: " << list[i].hargaSewa << " per bulan" << endl;
            cout << "-----------------------------" << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "Penyewa dengan nama " << nama << " tidak ditemukan." << endl;
    }
}

// Fungsi untuk mengurutkan penyewa berdasarkan harga sewa
void urutkanPenyewaBerdasarkanHarga(Penyewa *list) {
    for (int i = 0; i < jumlahPenyewa - 1; i++) {
        for (int j = i + 1; j < jumlahPenyewa; j++) {
            if (list[i].hargaSewa > list[j].hargaSewa) {
                Penyewa temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    cout << "Penyewa berhasil diurutkan berdasarkan harga sewa!" << endl;
}

// Fungsi untuk menyimpan data penyewa ke file
void simpanKeFile(Penyewa *list) {
    ofstream fileOut(fileName); // Membuka file untuk ditulis
    for (int i = 0; i < jumlahPenyewa; i++) {
        fileOut << list[i].id << endl;
        fileOut << list[i].nama << endl;
        fileOut << list[i].umur << endl;
        fileOut << list[i].apartemen << endl;
        fileOut << list[i].durasiSewa << endl;
        fileOut << list[i].hargaSewa << endl;
    }
    fileOut.close(); // Menutup file
    cout << "Data berhasil disimpan ke file." << endl;
}

// Fungsi untuk membaca data penyewa dari file
void bacaDariFile(Penyewa *list) {
    ifstream fileIn(fileName); // Membuka file untuk dibaca
    if (fileIn.is_open()) {
        while (!fileIn.eof()) {
            Penyewa penyewaBaru;
            fileIn >> penyewaBaru.id;
            fileIn.ignore(); // Mengabaikan newline sebelum membaca string
            getline(fileIn, penyewaBaru.nama);
            fileIn >> penyewaBaru.umur;
            fileIn.ignore();
            getline(fileIn, penyewaBaru.apartemen);
            fileIn >> penyewaBaru.durasiSewa;
            fileIn >> penyewaBaru.hargaSewa;

            if (!fileIn.fail()) { // Cek apakah data valid
                list[jumlahPenyewa] = penyewaBaru;
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
    // Membaca data dari file saat program dimulai
    bacaDariFile(penyewaList);

    int pilihan;
    do {
        cout << "\n=== Program Pendataan Sewa Apartemen ===" << endl;
        cout << "1. Tambah Penyewa" << endl;
        cout << "2. Tampilkan Penyewa" << endl;
        cout << "3. Update Penyewa" << endl;
        cout << "4. Hapus Penyewa" << endl;
        cout << "5. Cari Penyewa Berdasarkan Nama" << endl;
        cout << "6. Urutkan Penyewa Berdasarkan Harga Sewa" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPenyewa(penyewaList);
                break;
            case 2:
                tampilkanPenyewa(penyewaList);
                break;
            case 3:
                updatePenyewa(penyewaList);
                break;
            case 4:
                hapusPenyewa(penyewaList);
                break;
            case 5:
                cariPenyewaBerdasarkanNama(penyewaList);
                break;
            case 6:
                urutkanPenyewaBerdasarkanHarga(penyewaList);
                break;
            case 0:
                cout << "Menyimpan data ke file..." << endl;
                simpanKeFile(penyewaList);
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    } while (pilihan != 0);

    return 0;
}
