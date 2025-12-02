#ifndef ADMIN_H
#define ADMIN_H

#include "../struktur.h"

// Deklarasi fungsi admin
void menuTambahLagu(DoublyLinkedList& list);
void menuLihatSemuaLagu(const DoublyLinkedList& list);
void menuUpdateLagu(DoublyLinkedList& list);
void menuHapusLagu(DoublyLinkedList& list);
void menuCariLagu(const DoublyLinkedList& list);
void displayMenuAdmin();

#endif