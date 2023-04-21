#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Trie {
    int flag;
    struct Trie *next[26];
} Trie;

void insert(Trie **ppTrie, char *word) {
    int length = strlen(word);
    Trie *temp = *ppTrie;
    for (int i = 0; i < length; i++) {
        int index = word[i] - 'a'; //keeps the index within the valid range of 26
        if (temp->next[index] == NULL) {
            temp->next[index] = (Trie *)calloc(1, sizeof(Trie));
        }
        temp = temp->next[index];
    }
    temp->flag++;
}

int numberOfOccurrences(Trie *pTrie, char *word) {
    int length = strlen(word);
    Trie *temp = pTrie;
    for (int i = 0; i < length; i++) {
        int index = word[i] - 'a'; //keeps the index within the valid range of 26
        if (temp->next[index] == NULL) {
            return 0;
        }
        temp = temp->next[index];
    }
    return temp->flag;
}

Trie *deallocateTrie(Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < 26; i++) {
        deallocateTrie(pTrie->next[i]);
    }
    free(pTrie);
    return NULL;
}

int main(void) {
    Trie *trie = (Trie *)calloc(1, sizeof(Trie));
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    int nWords = sizeof(pWords) / sizeof(pWords[0]);
    for (int i = 0; i < nWords; i++) {
        insert(&trie, pWords[i]);
    }
    for (int i = 0; i < nWords; i++) {
        printf("%s: %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}
