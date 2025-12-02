#include "admin.h"
#include <iostream>
using namespace std;

void displayMenuAdmin() {
    int pilihan;
    DoublyLinkedList musicLibrary;
    initDLL(musicLibrary);
    
    // Tambah sample data
    tambahLagu(musicLibrary, "001", "Bohemian Rhapsody", "Queen", "Rock", 1975);
    tambahLagu(musicLibrary, "002", "Hotel California", "Eagles", "Rock", 1976);
    tambahLagu(musicLibrary, "003", "Shape of You", "Ed Sheeran", "Pop", 2017);
    
    do {
        cout << "\n=== MENU ADMIN MUSIC PLAYER ===\n";
        cout << "1. Tambah Lagu ke Library\n";
        cout << "2. Lihat Semua Lagu\n";
        cout << "3. Update Data Lagu\n";
        cout << "4. Hapus Lagu\n";
        cout << "5. Cari Lagu\n";
        cout << "6. Logout\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                menuTambahLagu(musicLibrary);
                break;
            case 2:
                menuLihatSemuaLagu(musicLibrary);
                break;
            case 3:
                menuUpdateLagu(musicLibrary);
                break;
            case 4:
                menuHapusLagu(musicLibrary);
                break;
            case 5:
                menuCariLagu(musicLibrary);
                break;
            case 6:
                cout << "Logout berhasil! Kembali ke menu utama...\n";
                break;
            default:
                cout << "Pilihan tidak valid! Silakan pilih 1-6.\n";
        }
        
        if (pilihan != 6) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }
        
    } while (pilihan != 6);
    
    // Cleanup memory
    hapusSemuaLagu(musicLibrary);
}