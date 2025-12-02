#include <iostream>
#include "admin/admin.h"
using namespace std;

void displayMenuUtama() {
    int pilihan;
    bool running = true;
    
    cout << "=== APLIKASI PEMUTAR MUSIC ===\n";
    
    while (running) {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Login sebagai Admin\n";
        cout << "2. Login sebagai User\n";
        cout << "3. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1: {
                string username, password;
                cout << "Username: "; cin >> username;
                cout << "Password: "; cin >> password;
                
                if (username == "admin" && password == "admin") {
                    cout << "Login admin berhasil!\n";
                    displayMenuAdmin();
                } else {
                    cout << "Login gagal! Username atau password salah.\n";
                }
                break;
            }
            case 2:
                cout << "Fitur User belum dibuat.\n";
                break;
            case 3:
                running = false;
                cout << "Terima kasih telah menggunakan aplikasi!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    }
}

int main() {
    displayMenuUtama();
    return 0;
}