#include <stdio.h>
#include <string.h>
#include "symtab.h"

SymNode SymTab[SYMTAB_SIZE];

void init_symtab() {
    for(int i = 0; i < SYMTAB_SIZE; i++)
        SymTab[i].is_occupied = 0;
}

// Hash = sum of ASCII values % table size
int hash(char *str) {
    int sum = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        sum += str[i];
    }
    return sum % SYMTAB_SIZE;
}

int insert_symbol(char *symbol, int address) {
    int index = hash(symbol);

    // Linear probing
    int start = index;

    while(SymTab[index].is_occupied) {
        // Duplicate check
        if(strcmp(SymTab[index].symbol, symbol) == 0) {
            return 0; // Duplicate
        }
        index = (index + 1) % SYMTAB_SIZE;

        // Table full
        if(index == start) return 0;
    }

    // Insert
    strcpy(SymTab[index].symbol, symbol);
    SymTab[index].address = address;
    SymTab[index].is_occupied = 1;

    return 1; // Success
}

int search_symbol(char *symbol) {
    int index = hash(symbol);
    int start = index;

    while(SymTab[index].is_occupied) {
        if(strcmp(SymTab[index].symbol, symbol) == 0) {
            return SymTab[index].address;
        }
        index = (index + 1) % SYMTAB_SIZE;

        if(index == start) break;
    }

    return -1; // Not found
}

void display_symtab() {
    printf("\n[Symbol Table]\n");
    printf("Index\tLabel\tAddress\n");
    for(int i=0; i<SYMTAB_SIZE; i++) {
        if(SymTab[i].is_occupied) 
            printf("%d\t%s\t%X\n", i, SymTab[i].symbol, SymTab[i].address);
    }
}