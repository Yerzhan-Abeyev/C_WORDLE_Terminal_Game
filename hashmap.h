#ifndef _HASHMAP_H_
#define _HASMAP_H_
typedef struct Node
{
    char key;
    int value;
    struct Node *next;
} Node;

// Hash map structure
typedef struct Map
{
    int size;
    Node **table;
} Map;

// Function declarations

// Creates a new hash map with the specified size
Map* Map_create(size_t size);

// Destroys the hash map and frees all memory
void Map_destroy(Map* map, size_t size);

// Hash function for character keys
unsigned int hash(char c, size_t size);

// Finds a node with the given key in the linked list
Node* findNode(Node* node, char key);

int  Map_contains( Map * map, char key, size_t size );

int Map_get( Map * map,  char key, size_t size );


    void Map_add( Map * map, char key, int value, size_t size );
#endif /* #ifndef _MYLIST_H_ */
