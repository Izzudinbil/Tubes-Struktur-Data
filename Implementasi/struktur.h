#ifndef STRUKTUR_H
#define STRUKTUR_H

#include <iostream>
#include <string>
using namespace std;

// Struktur data Lagu sesuai spesifikasi Tugas Besar
struct Lagu {
    string idLagu;
    string judulLagu;
    string namaPenyanyi;
    string genre;
    int tahunRilis;
    Lagu* next;
    Lagu* prev;
};

// Struktur untuk Doubly Linked List
struct DoublyLinkedList {
    Lagu* head;
    Lagu* tail;
    int size;
};

// Inisialisasi DLL
void initDLL(DoublyLinkedList& list);

// Deklarasi fungsi-fungsi manajemen lagu
void tambahLagu(DoublyLinkedList& list, string id, string judul, string penyanyi, string genre, int tahun);
void tampilkanSemuaLagu(const DoublyLinkedList& list);
Lagu* cariLaguByID(const DoublyLinkedList& list, string idLagu);
Lagu* cariLaguByJudul(const DoublyLinkedList& list, string judul);
void cariLaguByPenyanyi(const DoublyLinkedList& list, string penyanyi);
void updateLagu(DoublyLinkedList& list, string idLagu, string newJudul, string newPenyanyi, string newGenre, int newTahun);
void hapusLagu(DoublyLinkedList& list, string idLagu);
void hapusSemuaLagu(DoublyLinkedList& list);

#endif