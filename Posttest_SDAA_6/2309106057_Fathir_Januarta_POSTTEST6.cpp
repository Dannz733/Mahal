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

struct Stack {
    Node* top;

    Stack() : top(nullptr) {}

    void push(Penyewa penyewaBaru) {
        Node* newNode = new Node;
        newNode->penyewa = penyewaBaru;
        newNode->next = top;
        top = newNode;
        cout << "Penyewa berhasil ditambahkan ke Stack!" << endl;
    }

    void pop() {
        if (top == nullptr) {
            cout << "Stack kosong!" << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        cout << "Penyewa dengan ID " << temp->penyewa.id << " dihapus dari Stack." << endl;
        delete temp;
    }

    void display() {
        if (top == nullptr) {
            cout << "Stack kosong!" << endl;
            return;
        }
        Node* temp = top;
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

    bool isEmpty() {
        return top == nullptr;
    }
};

struct Queue {
    Node* front;
    Node* rear;

    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(Penyewa penyewaBaru) {
        Node* newNode = new Node;
        newNode->penyewa = penyewaBaru;
        newNode->next = nullptr;
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Penyewa berhasil ditambahkan ke Queue!" << endl;
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "Queue kosong!" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        cout << "Penyewa dengan ID " << temp->penyewa.id << " dihapus dari Queue." << endl;
        delete temp;
    }

    void display() {
        if (front == nullptr) {
            cout << "Queue kosong!" << endl;
            return;
        }
        Node* temp = front;
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

    bool isEmpty() {
        return front == nullptr;
    }
};

void submenuStack(Stack &stack) {
    int pilihanStack;
    do {
        cout << "\n=== Menu Stack ===" << endl;
        cout << "1. Push Penyewa ke Stack" << endl;
        cout << "2. Pop Penyewa dari Stack" << endl;
        cout << "3. Tampilkan Stack" << endl;
        cout << "0. Kembali ke Menu Utama" << endl;
        cout << "Pilihan: ";
        cin >> pilihanStack;

        switch (pilihanStack) {
            case 1: {
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

                stack.push(penyewaBaru);
                jumlahPenyewa++;
                break;
            }
            case 2:
                stack.pop();
                if (jumlahPenyewa > 0)
                    jumlahPenyewa--;
                break;
            case 3:
                stack.display();
                break;
            case 0:
                cout << "Kembali ke Menu Utama." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    } while (pilihanStack != 0);
}

void submenuQueue(Queue &queue) {
    int pilihanQueue;
    do {
        cout << "\n=== Menu Queue ===" << endl;
        cout << "1. Enqueue Penyewa ke Queue" << endl;
        cout << "2. Dequeue Penyewa dari Queue" << endl;
        cout << "3. Tampilkan Queue" << endl;
        cout << "0. Kembali ke Menu Utama" << endl;
        cout << "Pilihan: ";
        cin >> pilihanQueue;

        switch (pilihanQueue) {
            case 1: {
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

                queue.enqueue(penyewaBaru);
                jumlahPenyewa++;
                break;
            }
            case 2:
                queue.dequeue();
                if (jumlahPenyewa > 0)
                    jumlahPenyewa--;
                break;
            case 3:
                queue.display();
                break;
            case 0:
                cout << "Kembali ke Menu Utama." << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }
    } while (pilihanQueue != 0);
}

Node* mergeAscending(Node* left, Node* right) {
    if (!left)
        return right;
    if (!right)
        return left;

    Node* result = nullptr;

    if (left->penyewa.id <= right->penyewa.id) {
        result = left;
        result->next = mergeAscending(left->next, right);
    }
    else {
        result = right;
        result->next = mergeAscending(left, right->next);
    }
    return result;
}

Node* mergeSortAscending(Node* headRef) {
    if (!headRef || !headRef->next)
        return headRef;

    Node* slow = headRef;
    Node* fast = headRef->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* mid = slow->next;
    slow->next = nullptr;

    Node* left = mergeSortAscending(headRef);
    Node* right = mergeSortAscending(mid);

    return mergeAscending(left, right);
}

Node* partitionDescending(Node* head, Node** newHead, Node** newEnd) {
    Node* pivot = head;
    Node* prev = nullptr;
    Node* cur = head->next;
    Node* tail = pivot;

    while (cur != nullptr) {
        if (cur->penyewa.id > pivot->penyewa.id) {
            if ((*newHead) == nullptr)
                (*newHead) = cur;
            prev = cur;
            cur = cur->next;
            tail->next = nullptr;
        }
        else {
            if (prev)
                prev->next = cur->next;
            Node* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newHead) == nullptr)
        (*newHead) = pivot;

    (*newEnd) = tail;

    return pivot;
}

Node* getTail(Node* head) {
    while (head != nullptr && head->next != nullptr) {
        head = head->next;
    }
    return head;
}

Node* quickSortDescendingRec(Node* head, Node* end) {
    if (!head || head == end)
        return head;

    Node *newHead = nullptr, *newEnd = nullptr;
    Node* pivot = partitionDescending(head, &newHead, &newEnd);

    if (newHead != pivot) {
        Node* temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortDescendingRec(newHead, temp);

        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortDescendingRec(pivot->next, newEnd);

    return newHead;
}

Node* quickSortDescending(Node* headRef) {
    return quickSortDescendingRec(headRef, getTail(headRef));
}

void sortAscending() {
    head = mergeSortAscending(head);
    cout << "Data penyewa telah diurutkan secara ascending menggunakan Merge Sort." << endl;
}

void sortDescending() {
    head = quickSortDescending(head);
    cout << "Data penyewa telah diurutkan secara descending menggunakan Quick Sort." << endl;
}

void bersihkanLinkedList() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* hapus = temp;
        temp = temp->next;
        delete hapus;
    }
    head = nullptr;
    jumlahPenyewa = 0;
}

int main() {
    bacaDariFile();

    Stack stack;
    Queue queue;

    int pilihan;
    do {
        cout << "\n=== Program Pendataan Sewa Apartemen ===" << endl;
        cout << "1. Tambah Penyewa" << endl;
        cout << "2. Tampilkan Penyewa" << endl;
        cout << "3. Update Penyewa" << endl;
        cout << "4. Hapus Penyewa" << endl;
        cout << "5. Cari Penyewa Berdasarkan Nama" << endl;
        cout << "6. Operasi Stack" << endl;
        cout << "7. Operasi Queue" << endl;
        cout << "8. Sort Penyewa Ascending (Merge Sort)" << endl;
        cout << "9. Sort Penyewa Descending (Quick Sort)" << endl;
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
            case 6:
                submenuStack(stack);
                break;
            case 7:
                submenuQueue(queue);
                break;
            case 8:
                sortAscending();
                break;
            case 9:
                sortDescending();
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

    bersihkanLinkedList();

    while (!stack.isEmpty()) {
        stack.pop();
    }

    while (!queue.isEmpty()) {
        queue.dequeue();
    }

    return 0;
}
