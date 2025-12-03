#include "admin.h"
#include <iostream>
#include <limits> 
using namespace std;

void menuTambahLagu(DoublyLinkedList& list) {
    string id, judul, penyanyi, genre;
    int tahun;
    
    cout << "\n=== TAMBAH LAGU BARU ===\n";
    cout << "ID Lagu: "; 
    cin >> id;
    cout << "Judul Lagu: "; 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
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
    string id;
    int pilihan;
    
    tampilkanSemuaLagu(list);
    
    cout << "\n=== UPDATE DATA LAGU ===\n";
    cout << "Masukkan ID Lagu yang akan diupdate: "; 
    cin >> id;
    
    Lagu* lagu = cariLaguByID(list, id);
    if (lagu == nullptr) {
        cout << "Lagu dengan ID '" << id << "' tidak ditemukan!\n";
        return;
    }
    bool updating = true;
    while (updating) {
        cout << "\nData Lagu Saat Ini:\n";
        cout << "1. Judul    : " << lagu->judulLagu << endl;
        cout << "2. Penyanyi : " << lagu->namaPenyanyi << endl;
        cout << "3. Genre    : " << lagu->genre << endl;
        cout << "4. Tahun    : " << lagu->tahunRilis << endl;
        cout << "5. Update Semua Data\n";
        cout << "6. Selesai Update\n";
        cout << "Pilih bagian yang ingin diupdate (1-6): ";
        cin >> pilihan;
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        string newVal;
        int newInt;
        string uJudul, uPenyanyi, uGenre;
        int uTahun;
        
        switch (pilihan) {
            case 1:
                cout << "Masukkan Judul Baru: ";
                getline(cin, newVal);
                updateLagu(list, id, newVal, lagu->namaPenyanyi, lagu->genre, lagu->tahunRilis);
                break;
            case 2:
                cout << "Masukkan Penyanyi Baru: ";
                getline(cin, newVal);
                updateLagu(list, id, lagu->judulLagu, newVal, lagu->genre, lagu->tahunRilis);
                break;
            case 3:
                cout << "Masukkan Genre Baru: ";
                getline(cin, newVal);
                updateLagu(list, id, lagu->judulLagu, lagu->namaPenyanyi, newVal, lagu->tahunRilis);
                break;
            case 4:
                cout << "Masukkan Tahun Baru: ";
                cin >> newInt;
                updateLagu(list, id, lagu->judulLagu, lagu->namaPenyanyi, lagu->genre, newInt);
                break;
            case 5:
                cout << "Masukkan Judul Baru: ";
                // cin.ignore() removed here
                getline(cin, uJudul);
                cout << "Masukkan Penyanyi Baru: ";
                getline(cin, uPenyanyi);
                cout << "Masukkan Genre Baru: ";
                getline(cin, uGenre);
                cout << "Masukkan Tahun Baru: ";
                cin >> uTahun;
                updateLagu(list, id, uJudul, uPenyanyi, uGenre, uTahun);
                break;
            case 6:
                updating = false;
                cout << "Selesai mengupdate lagu.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    }
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
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
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
                // Use similarity search
                Lagu* result = cariLaguByJudulSimilarity(list, value);
                
                if (result != nullptr) {
                    // Confirmation prompt
                    char confirm;
                    cout << "Apakah yang anda maksud lagu '" << result->judulLagu << "'? (y/n): ";
                    cin >> confirm;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
                    
                    if (tolower(confirm) == 'y') {
                        cout << "\nLagu ditemukan:\n";
                        cout << "ID - Judul - Penyanyi - Genre - Tahun\n";
                        cout << "--------------------------------------\n";
                        cout << result->idLagu 
                            << " - " << result->judulLagu
                            << " - " << result->namaPenyanyi
                            << " - " << result->genre
                            << " - " << result->tahunRilis << endl;
                    } else {
                        cout << "Pencarian dibatalkan. Silakan coba kata kunci lain.\n";
                    }
                } else {
                    cout << "Lagu dengan judul mirip '" << value << "' tidak ditemukan!\n";
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