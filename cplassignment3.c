// Name :- Om Ashok Nalage
// Enrollment No. :-BT22CSE117
// Batch No. :-R5
// Subject :- CPL



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 100

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

typedef struct Scope {
    Entry *entries[HASH_SIZE];
    struct Scope *outer_scope;
} Scope;

Scope *current_scope = NULL;

// Hash function
int hash_key(const char *key) {
    int hashval = 0;
    for (; *key != '\0'; key++) {
        hashval = *key + 31 * hashval;
    }
    return hashval % HASH_SIZE;
}

// Initialize a new scope
Scope *create_new_scope(Scope *outer_scope) {
    Scope *new_scope = (Scope *)malloc(sizeof(Scope));
    if (!new_scope) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    memset(new_scope->entries, 0, sizeof(new_scope->entries));
    new_scope->outer_scope = outer_scope;
    return new_scope;
}

// Insert a variable into the current scope
void set_variable(Scope *scope, const char *key, int value) {
    int index = hash_key(key);
    Entry *entry = (Entry *)malloc(sizeof(Entry));
    if (!entry) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    entry->key = strdup(key);
    entry->value = value;
    entry->next = scope->entries[index];
    scope->entries[index] = entry;
}

// Lookup the value of a variable in the current or outer scopes
int get_variable(Scope *scope, const char *key) {
    int index = hash_key(key);
    while (scope != NULL) {
        Entry *entry = scope->entries[index];
        while (entry != NULL) {
            if (strcmp(entry->key, key) == 0) {
                return entry->value;
            }
            entry = entry->next;
        }
        scope = scope->outer_scope;
    }
    return -1; // Variable not found
}

// Finalize the current scope
void end_current_scope(Scope **scope) {
    if (*scope == NULL) {
        fprintf(stderr, "No scope to end\n");
        exit(1);
    }
    Scope *outer_scope = (*scope)->outer_scope;
    while ((*scope)->entries[0] != NULL) {
        Entry *entry = (*scope)->entries[0];
        (*scope)->entries[0] = entry->next;
        free(entry->key);
        free(entry);
    }
    free(*scope);
    *scope = outer_scope;
}

int main() {
    current_scope = create_new_scope(NULL);
    set_variable(current_scope, "a", 1);
    set_variable(current_scope, "b", 2);
    current_scope = create_new_scope(current_scope);
    set_variable(current_scope, "a", 3);
    set_variable(current_scope, "c", 4);
    printf("print b => %d\n", get_variable(current_scope, "b")); // prints value 2
    current_scope = create_new_scope(current_scope);
    set_variable(current_scope, "c", 5);
    printf("print b => %d\n", get_variable(current_scope, "b")); // prints value 2
    printf("print a => %d\n", get_variable(current_scope, "a")); // prints value 3
    printf("print c => %d\n", get_variable(current_scope, "c")); // prints value 5
    end_current_scope(&current_scope);
    printf("print a => %d\n", get_variable(current_scope, "a")); // prints value 3
    printf("print c => %d\n", get_variable(current_scope, "c")); // prints value 4
    end_current_scope(&current_scope);
    printf("print a => %d\n", get_variable(current_scope, "a")); // prints value 1
    end_current_scope(&current_scope);
    return 0;
}
