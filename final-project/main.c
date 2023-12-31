#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int idCounter = 1;
typedef int Key;
struct Node {
    Key key;
    int data;

    struct Node *next;
};

typedef struct Node Node;

int run();
int runTest();
void printNode(Node node);
Node* createNode(int data);
int isEmpty(Node *awal, Node *akhir);
Node* search(Node *awal, Node *akhir, Key key);
void traversPrint(Node *awal, Node *akhir);
void insertFirst(Node **awal, Node **akhir, Node *node);
void insertLast(Node **awal, Node **akhir, Node *node);
void insertAfter(Node** nodeTarget, Node *node);
int deleteByKey(Node **awal, Node **akhir, Key key);
void update(Node **node, int data);
int loopMenu();
Node* captureInsert();
Key captureDeleteByKey();
Key captureSearch();
int captureUpdate(Node *node);
int captureMenu();
void captureAnykey();
void clearConsole();

int main() {
    int exitCode = run();
    if (exitCode != 0) {
       printf("error with exit code %d\n", exitCode);
    }
}

int run() {
    return loopMenu();
    // return runTest();
}

int runTest() {
    Node *awal = NULL;
    Node *akhir = NULL;
    Node *node = NULL;

    // insert first
    node = createNode(10);
    insertFirst(&awal, &akhir, node);

    node = createNode(20);
    insertFirst(&awal, &akhir, node);

    node = createNode(5);
    insertFirst(&awal, &akhir, node);

    node = createNode(15);
    insertLast(&awal, &akhir, node);

    printf("\ntraverse\n");
    traversPrint(awal, akhir);

    printf("\nsearch key:4\n");
    Node *searchRes = search(awal, akhir, 4);
    printNode(*searchRes);

    printf("\nupdate key:4\n");
    update(&searchRes, 100);
    printNode(*searchRes);

    printf("\ndelete key:1\n");
    if (!deleteByKey(&awal, &akhir, 1)) {
        printf("delete failed\n");
    } else {
        traversPrint(awal, akhir);
    }

    printf("\ndelete key:3\n");
    if (!deleteByKey(&awal, &akhir, 3)) {
        printf("delete failed\n");
    } else {
        traversPrint(awal, akhir);
    }

    printf("\ndelete key:5 not foun\n");
    if (!deleteByKey(&awal, &akhir, 5)) {
        printf("delete failed\n");
    } else {
        traversPrint(awal, akhir);
    }

    return 0;
}

void printNode(Node node) {
    printf("key:%d data:%d\n", node.key, node.data);
}

Node* createNode(int data) {
    Node *node = (Node*) malloc(sizeof(Node));
    
    node->key = idCounter;
    node->data = data;
    node->next = NULL;

    idCounter++;

    return node;
}

// isEmpty return 1 jika kosong, 0 jika isi
int isEmpty(Node *awal, Node *akhir) {
    return awal == NULL && akhir == NULL;
}

Node* search(Node *awal, Node *akhir, Key key) {
    Node *current = awal;

    while (current != NULL) {
        if (current->key == key) {
            break;
        }

        current = current->next;
    }

    return current; 
}

void traversPrint(Node *awal, Node *akhir) {
    // Print table headers
    printf("| %-10s | %-15s |\n", "Key", "Data");
    printf("|------------|-----------------|\n");
    
    if (isEmpty(awal, akhir)) {
        return;
    }

    Node *current = awal;
    int counter = 0;
    while (current != NULL) {
        counter++;
        printf("| %-10d | %-15d |\n", current->key, current->data);
        current = current->next;
    }
}

void insertFirst(Node **awal, Node **akhir, Node *node) {
    if (isEmpty(*awal, *akhir)) {
        *awal = node;
        *akhir = node;
    } else {
        node->next = *awal;
        *awal = node;
    }
}

void insertLast(Node **awal, Node **akhir, Node *node) {
    if (isEmpty(*awal, *akhir)) {
        *awal = node;
        *akhir = node;
    } else {
        (*akhir)->next = node;
        *akhir = node;
    }
}

void insertAfter(Node** nodeTarget, Node *node) {
    if (nodeTarget == NULL) {
        return;
    }

    node->next = (*nodeTarget)->next;
    (*nodeTarget)->next = node;
}

// deleteByKey delete node by key return 1 if success, 0 if failed
int deleteByKey(Node **awal, Node **akhir, Key key) {
    if (isEmpty(*awal, *akhir)) {
        return 0;
    }

    Node *current = *awal;

    // kalau node berada di awal
    if (current->key == key) {
        *awal = (*awal)->next;
        free(current);
        return 1;
    }

    Node *prevNode = NULL;
    prevNode = current;

    current = current->next;
    if (current == NULL) {
        return 0;
    }

    while (current != NULL) {
        if (current->key == key) {
            // link prevNode ke current->next
            prevNode->next = current->next;
            free(current);
            break;
        }

        prevNode = current;
        current = current->next;
    }

    return 1;
}

void update(Node **node, int data) {
    if (*node == NULL) {
        return;
    }

    (*node)->data = data;
}

Node* captureInsert() {
    printf("Masukkan data baru\n---");
    printf("\nData: "); int data; scanf("%d", &data);
    Node *node = createNode(data);

    return node;
}

int captureUpdate(Node *node) {
    if (node == NULL) {
        return 0;
    }
    
    printf("Masukkan data untuk update\n---");
    
    printf("\nData: "); int data; scanf("%d", &data);
    node->data = data;

    return 1;
}

Key captureDeleteByKey() {
    Key key;

    printf("Masukkan key untuk di-delete: ");
    scanf("%d", &key);

    return key; 
}

Key captureSearch() {
    Key key;

    printf("Masukkan key: ");
    scanf("%d", &key);

    return key;
}

// menu set
const int menuListData = 1;
const int menuInsertFirst = 2;
const int menuInsertLast = 3;
const int menuInsertAfter = 4;
const int menuDelete = 5;
const int menuUpdate = 6;
const int menuSearch = 7;
const int menuShowMenu = 8;
const int menuExit = 9;

int captureMenu() {
    printf("\n\nMenu\n---\n");
    printf("%d. list data\n", menuListData);
    printf("%d. insert first\n", menuInsertFirst);
    printf("%d. insert last\n", menuInsertLast);
    printf("%d. insert after\n", menuInsertAfter);
    printf("%d. delete\n", menuDelete);
    printf("%d. update\n", menuUpdate);
    printf("%d. search\n", menuSearch);
    printf("%d. show menu\n", menuShowMenu);
    printf("%d. exit\n", menuExit);

    int menuSelected;
    printf("\n\nPilih menu: "); scanf("%d", &menuSelected);

    return menuSelected;
}

int loopMenu() {
    Node *awal = NULL;
    Node *akhir = NULL;

    int menuSelected;

    while(menuSelected != menuExit) {
        printf("\nList data\n---\n");
        traversPrint(awal, akhir);
        menuSelected = captureMenu();

        switch (menuSelected) {
            default: // menuShowMenu
                break;

            case menuListData:
                printf("\nList data\n---\n");
                traversPrint(awal, akhir);
                break;
           
            case menuInsertFirst: {
                    Node* node = captureInsert();
                    insertFirst(&awal, &akhir, node);
                }
                break;

            case menuInsertLast: {
                    Node* node = captureInsert();
                    insertLast(&awal, &akhir, node);
                }
                break;

            case menuInsertAfter: {
                    printf("Insert after\n\n");
                    Key key = captureSearch();
                    Node *nodeTarget = search(awal, akhir, key);
                    if (nodeTarget == NULL) {
                        printf("Key tidak ditemukan\n");
                        captureAnykey();
                        break;
                    }
                    
                    Node *node = captureInsert();
                    insertAfter(&nodeTarget, node);
                }
                break;

            case menuDelete: {
                    Key key = captureDeleteByKey();
                    if (!deleteByKey(&awal, &akhir, key)) {
                        printf("delete failed\n");
                    } else {
                        printf("delete success\n");
                    }
                }
                break;

            case menuUpdate: {
                    Key key = captureSearch();
                    Node *searchRes = search(awal, akhir, key);
                    if (searchRes == NULL) {
                        printf("data not found\n");
                        break;
                    }

                    captureUpdate(searchRes);
                    break;
                }

            case menuSearch: {
                    Key key = captureSearch();
                    Node *searchRes = search(awal, akhir, key);
                    if (searchRes == NULL) {
                        printf("data not found\n");
                    } else {
                        printNode(*searchRes);
                    }
                }
                break;

            case menuExit:
                printf("Terima kasih\n");
                break;
        }
        sleep(1);
        clearConsole();
    }
    
    return 0;
}

void captureAnykey() {
    printf("Tekan tombol enter untuk melanjutkan");
    fflush(stdout);
    while (getchar() != '\n');
    getchar();
}

void clearConsole() {
    #ifdef _WIN32
        system("cls"); // For Windows
    #else
        system("clear"); // For Unix and macOS
    #endif
}