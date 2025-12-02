#include "admin.h"
#include <iostream>
using namespace std;

void menuTambahLagu(DoublyLinkedList& list) {
    string id, judul, penyanyi, genre;
    int tahun;
    
    cout << "\n=== TAMBAH LAGU BARU ===\n";
    cout << "ID Lagu: "; 
    cin >> id;
    cout << "Judul Lagu: "; 
    cin.ignore(); 
    getline(cin, judul);
    cout << "Nama Penyanyi: "; 
    getline(cin, penyanyi);
    cout << "Genre: "; 
    getline(cin, genre);
    cout << "Tahun Rilis: "; 
    cin >> tahun;
    
    tambahLagu(list, id, judul, penyanyi, genre, tahun);
}

void menuLihatSemuaLagu(const DoublyLinkedList& list) {
    tampilkanSemuaLagu(list);
}

void menuUpdateLagu(DoublyLinkedList& list) {
    string id, judul, penyanyi, genre;
    int tahun;
    
    cout << "\n=== UPDATE DATA LAGU ===\n";
    cout << "Masukkan ID Lagu yang akan diupdate: "; 
    cin >> id;
    
    // Cek apakah lagu ada
    Lagu* lagu = cariLaguByID(list, id);
    if (lagu == nullptr) {
        cout << "Lagu dengan ID '" << id << "' tidak ditemukan!\n";
        return;
    }
    
    // Tampilkan data saat ini
    cout << "Data saat ini:\n";
    cout << "Judul: " << lagu->judulLagu << endl;
    cout << "Penyanyi: " << lagu->namaPenyanyi << endl;
    cout << "Genre: " << lagu->genre << endl;
    cout << "Tahun: " << lagu->tahunRilis << endl;
    
    cout << "\nMasukkan data baru:\n";
    cout << "Judul Baru: "; 
    cin.ignore(); 
    getline(cin, judul);
    cout << "Penyanyi Baru: "; 
    getline(cin, penyanyi);
    cout << "Genre Baru: "; 
    getline(cin, genre);
    cout << "Tahun Baru: "; 
    cin >> tahun;
    
    updateLagu(list, id, judul, penyanyi, genre, tahun);
}

void menuHapusLagu(DoublyLinkedList& list) {
    string id;
    
    cout << "\n=== HAPUS LAGU ===\n";
    cout << "Masukkan ID Lagu yang akan dihapus: "; 
    cin >> id;
    
    hapusLagu(list, id);
}

void menuCariLagu(const DoublyLinkedList& list) {
    int pilihan;
    string value;
    
    cout << "\n=== CARI LAGU ===\n";
    cout << "1. Cari berdasarkan ID\n";
    cout << "2. Cari berdasarkan Judul\n";
    cout << "3. Cari berdasarkan Penyanyi\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    
    cin.ignore(); // Clear buffer
    
    switch (pilihan) {
        case 1:
            cout << "Masukkan ID Lagu: ";
            cin >> value;
            {
                Lagu* result = cariLaguByID(list, value);
                if (result != nullptr) {
                    cout << "\nLagu ditemukan:\n";
                    cout << "ID - Judul - Penyanyi - Genre - Tahun\n";
                    cout << "--------------------------------------\n";
                    cout << result->idLagu 
                        << " - " << result->judulLagu
                        << " - " << result->namaPenyanyi
                        << " - " << result->genre
                        << " - " << result->tahunRilis << endl;
                } else {
                    cout << "Lagu dengan ID '" << value << "' tidak ditemukan!\n";
                }
            }
            break;
            
        case 2:
            cout << "Masukkan Judul Lagu: ";
            getline(cin, value);
            {
                Lagu* result = cariLaguByJudul(list, value);
                if (result != nullptr) {
                    cout << "\nLagu ditemukan:\n";
                    cout << "ID - Judul - Penyanyi - Genre - Tahun\n";
                    cout << "--------------------------------------\n";
                    cout << result->idLagu 
                        << " - " << result->judulLagu
                        << " - " << result->namaPenyanyi
                        << " - " << result->genre
                        << " - " << result->tahunRilis << endl;
                } else {
                    cout << "Lagu dengan judul '" << value << "' tidak ditemukan!\n";
                }
            }
            break;
            
        case 3:
            cout << "Masukkan Nama Penyanyi: ";
            getline(cin, value);
            cariLaguByPenyanyi(list, value);
            break;
            
        default:
            cout << "Pilihan tidak valid!\n";
    }
}