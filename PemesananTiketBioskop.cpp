#include <iostream>
#include <string>
using namespace std;

// Struktur untuk menyimpan informasi film
struct Film {
    string judul;
    int harga;
    int kapasitas;
    int tersedia;
};

// Node untuk linked list pemesanan tiket
struct Node {
    int nomorFilm;
    int jumlahTiket;
    Node* next;
};

// Fungsi untuk membuat node baru
Node* createNode(int nomorFilm, int jumlahTiket) {
    Node* newNode = new Node;
    newNode->nomorFilm = nomorFilm;
    newNode->jumlahTiket = jumlahTiket;
    newNode->next = nullptr;
    return newNode;
}

// Fungsi untuk menampilkan daftar film
void displayFilms(Film* films, int jumlahFilm) {
    cout << "Daftar Film:" << endl;
    for (int i = 0; i < jumlahFilm; ++i) {
        cout << i + 1 << ". " << films[i].judul << " (Harga: " << films[i].harga << " | Tersedia: " << films[i].tersedia << ")" << endl;
    }
    cout << endl;
}

// Fungsi untuk memesan tiket
void pesanTiket(Film* films, int jumlahFilm, Node*& head) {
    int nomorFilm;
    int jumlahTiket;

    displayFilms(films, jumlahFilm);

    cout << "Masukkan nomor film yang ingin dipesan: ";
    cin >> nomorFilm;
    cout << endl;

    if (nomorFilm < 1 || nomorFilm > jumlahFilm) {
        cout << "Nomor film tidak valid." << endl << endl;
        return;
    }

    cout << "Masukkan jumlah tiket yang ingin dipesan: ";
    cin >> jumlahTiket;

    // Cari film yang diinginkan
    Film* film = &films[nomorFilm - 1];

    if (jumlahTiket > film->tersedia) {
        cout << "Maaf, tiket tidak mencukupi." << endl << endl;
        return;
    }

    // Kurangi jumlah tiket yang tersedia
    film->tersedia -= jumlahTiket;

    // Tambahkan ke linked list pemesanan
    if (head == nullptr) {
        head = createNode(nomorFilm, jumlahTiket);
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = createNode(nomorFilm, jumlahTiket);
    }

    cout << "Pemesanan berhasil!" << endl << endl;
}

// Fungsi untuk menampilkan pemesanan
void displayPemesanan(Node* head, Film* films) {
    if (head == nullptr) {
        cout << "Belum ada pemesanan." << endl << endl;
        return;
    }

    cout << "Daftar Pemesanan:" << endl;
    Node* temp = head;
    while (temp != nullptr) {
        cout << films[temp->nomorFilm - 1].judul << " - " << temp->jumlahTiket << " tiket" << endl << endl;
        temp = temp->next;
    }
}

int main() {
    const int jumlahFilm = 3;
    Film films[jumlahFilm] = {
        {"Avengers: Endgame", 50000, 100, 100},
        {"Joker", 40000, 80, 80},
        {"Godzilla II: King of the Monsters", 45000, 120, 120}
    };

    Node* head = nullptr;
    int pilihan;

    do {
        cout << "Menu:" << endl;
        cout << "1. Pesan Tiket" << endl;
        cout << "2. Tampilkan Pemesanan" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cout << endl;

        switch(pilihan) {
            case 1:
                pesanTiket(films, jumlahFilm, head);
                break;
            case 2:
                displayPemesanan(head, films);
                break;
            case 3:
                cout << "Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 3);

    // Menghapus linked list
    Node* temp = head;
    while (temp != nullptr) {
        Node* toDelete = temp;
        temp = temp->next;
        delete toDelete;
    }

    return 0;
}
