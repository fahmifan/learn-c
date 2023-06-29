#include <stdio.h>
#include <string.h>
#include <stdlib.h>

use namespace std;

struct node {
   int data; // value
   
   struct node *next; // pointer
};
struct node *awal = NULL;
struct node *current = NULL;

/**
 * 1 -> 2 -> 87
 * A -> A -> A
*/

// fixed size
// array = [1000]int{}

// list dgn ukuran/jumlah-N


int main(){
    // kondisi ketidak adaan value alamat
    int *point_node_x;

    int node_a = 10;
    int node_b = node_a;

    cout << "node_a: " << node_a << endl;
    cout << "node_b: " << node_b << endl;
    printf("node_a: %d\n", node_a);
    printf("&node_a:"); printf(&node_a);
    printf("point_node_x:"); printf(point_node_x);

    // simpan "alamant" node_a ke *point_node_x
    point_node_x = &node_a;
    *point_node_x = 9;

    printf("node_a: %d\n", node_a);
    printf("*point_node_x: %d\n", *point_node_x);
}

// insertion, traversal, dll