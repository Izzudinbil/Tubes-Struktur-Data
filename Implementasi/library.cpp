#include "struktur.h"
#include <algorithm> 
#include <cctype>    

// Helper function for Levenshtein Distance
int levenshteinDist(string s1, string s2) {
    int m = s1.length();
    int n = s2.length();
    
    int dp[m + 1][n + 1];
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (tolower(s1[i - 1]) == tolower(s2[j - 1]))
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min(min(dp[i][j - 1],      
                                   dp[i - 1][j]),      
                                   dp[i - 1][j - 1]);  
        }
    }
    
    return dp[m][n];
}

// Inisialisasi DLL
void initDLL(DoublyLinkedList& list) {
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

// Tambah lagu ke akhir DLL
void tambahLagu(DoublyLinkedList& list, string id, string judul, 
                string penyanyi, string genre, int tahun) {
    
    // Cek apakah ID sudah ada
    Lagu* current = list.head;
    while (current != nullptr) {
        if (current->idLagu == id) {
            cout << "ERROR: Lagu dengan ID '" << id << "' sudah ada!\n";
            return;
        }
        current = current->next;
    }
    
    // Buat lagu baru
    Lagu* newLagu = new Lagu;
    newLagu->idLagu = id;
    newLagu->judulLagu = judul;
    newLagu->namaPenyanyi = penyanyi;
    newLagu->genre = genre;
    newLagu->tahunRilis = tahun;
    newLagu->next = nullptr;
    newLagu->prev = nullptr;
    
    // Tambah ke DLL
    if (list.head == nullptr) {
        list.head = newLagu;
        list.tail = newLagu;
    } else {
        list.tail->next = newLagu;
        newLagu->prev = list.tail;
        list.tail = newLagu;
    }
    
    list.size++;
    cout << "Lagu '" << judul << "' berhasil ditambahkan!\n";
}

// Tampilkan semua lagu
void tampilkanSemuaLagu(const DoublyLinkedList& list) {
    if (list.head == nullptr) {
        cout << "Library lagu kosong!\n";
        return;
    }
    
    cout << "\n=== SEMUA LAGU DI LIBRARY (" << list.size << " lagu) ===\n";
    Lagu* current = list.head;
    cout << "ID - Judul - Penyanyi - Genre - Tahun\n";
    cout << "--------------------------------------\n";
    while (current != nullptr) {
        cout << current->idLagu 
            << " - " << current->judulLagu
            << " - " << current->namaPenyanyi
            << " - " << current->genre
            << " - " << current->tahunRilis << endl;
        current = current->next;
    }
}

// Cari lagu berdasarkan ID
Lagu* cariLaguByID(const DoublyLinkedList& list, string idLagu) {
    Lagu* current = list.head;
    while (current != nullptr) {
        if (current->idLagu == idLagu) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Cari lagu berdasarkan judul (Exact Match)
Lagu* cariLaguByJudul(const DoublyLinkedList& list, string judul) {
    Lagu* current = list.head;
    while (current != nullptr) {
        if (current->judulLagu == judul) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Cari lagu berdasarkan judul (Similarity / Fuzzy Search)
Lagu* cariLaguByJudulSimilarity(const DoublyLinkedList& list, string judul) {
    Lagu* current = list.head;
    Lagu* bestMatch = nullptr;
    int minDistance = 1000; // Initialize with a high value
    
    while (current != nullptr) {
        int dist = levenshteinDist(judul, current->judulLagu);
        
        // Find the absolute minimum distance
        if (dist < minDistance) {
            minDistance = dist;
            bestMatch = current;
        }
        
        current = current->next;
    }
    
    // Define a threshold to accept the match
    // If best match is found, check if it's reasonable
    // E.g., distance <= 50% of the longer string length
    if (bestMatch != nullptr) {
        int threshold = max((int)judul.length(), (int)bestMatch->judulLagu.length()) / 2 + 1;
        if (minDistance <= threshold) {
            return bestMatch;
        }
    }
    
    return nullptr;
}

// Cari lagu berdasarkan penyanyi
void cariLaguByPenyanyi(const DoublyLinkedList& list, string penyanyi) {
    Lagu* current = list.head;
    bool found = false;
    
    cout << "\n=== HASIL PENCARIAN: '" << penyanyi << "' ===";
    cout << "ID - Judul - Genre - Tahun\n";
    cout << "--------------------------------------\n";
    while (current != nullptr) {
        if (current->namaPenyanyi == penyanyi) {
            cout << current->idLagu 
                << " - " << current->judulLagu
                << " - " << current->genre
                << " - " << current->tahunRilis << endl;
            found = true;
        }
        current = current->next;
    }
    
    if (!found) {
        cout << "Tidak ditemukan lagu dari penyanyi '" << penyanyi << "'\n";
    }
}

// Update data lagu
void updateLagu(DoublyLinkedList& list, string idLagu, 
                string newJudul, string newPenyanyi, 
                string newGenre, int newTahun) {
    
    Lagu* lagu = cariLaguByID(list, idLagu);
    if (lagu != nullptr) {
        // Simpan data lama untuk konfirmasi
        string oldJudul = lagu->judulLagu;
        string oldPenyanyi = lagu->namaPenyanyi;
        
        // Update data
        lagu->judulLagu = newJudul;
        lagu->namaPenyanyi = newPenyanyi;
        lagu->genre = newGenre;
        lagu->tahunRilis = newTahun;
        
        cout << "Lagu berhasil diupdate!\n";
        cout << "Sebelum: " << oldJudul << " - " << oldPenyanyi << endl;
        cout << "Sesudah: " << newJudul << " - " << newPenyanyi << endl;
    } else {
        cout << "ERROR: Lagu dengan ID '" << idLagu << "' tidak ditemukan!\n";
    }
}

// Hapus lagu dari DLL
void hapusLagu(DoublyLinkedList& list, string idLagu) {
    Lagu* lagu = cariLaguByID(list, idLagu);
    
    if (lagu == nullptr) {
        cout << "ERROR: Lagu dengan ID '" << idLagu << "' tidak ditemukan!\n";
        return;
    }
    
    // Hapus dari DLL
    if (lagu->prev != nullptr) {
        lagu->prev->next = lagu->next;
    } else {
        list.head = lagu->next;
    }
    
    if (lagu->next != nullptr) {
        lagu->next->prev = lagu->prev;
    } else {
        list.tail = lagu->prev;
    }
    
    cout << "Lagu '" << lagu->judulLagu << "' berhasil dihapus!\n";
    delete lagu;
    list.size--;
}

// Hapus semua lagu (cleanup memory)
void hapusSemuaLagu(DoublyLinkedList& list) {
    Lagu* current = list.head;
    while (current != nullptr) {
        Lagu* temp = current;
        current = current->next;
        delete temp;
    }
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}