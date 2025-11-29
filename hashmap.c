#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>



typedef struct Node
{
    char key;
    int value;
    struct Node * next;
} Node;
typedef struct Map
{
    int size;
    Node ** table;
} Map;



Map* Map_create(size_t size){
     Map* map = (Map*)malloc(sizeof(Map));
     map->size = 0;
     map->table = (Node**) calloc( size, sizeof( Node* ) );
     return map;

}


void Map_destroy(Map* map, size_t size){
    for ( size_t index = 0; index < size; index++ )
    {
        Node * node = map->table[ index ];
        while ( node != NULL )
        {
            Node * temp = node;
            node = node->next;
            free( temp );
        }}
    free(map->table);
    free(map);
     

}

unsigned int hash(char c, size_t size){
        return (int) c % size;

}


Node* findNode(Node* node, char key){
    while(node != NULL){
if ( node->key == key ) 
        {
            return node;
        }
        node = node->next;
    }
    
    return NULL;

}
void Map_add( Map * map, char key, int value, size_t size )
{
    unsigned int index = hash( key, size );
    Node * node = findNode( map->table[ index ], key );

    if ( node == NULL)
    {
        node = (Node*) malloc( sizeof( Node ) );
        node->key = key;
        node->value = value;
        node->next = map->table[ index ];
        map->table[ index ] = node;
        map->size++;
    }
    else{
        node->value = value;
    }
}
int  Map_contains( Map * map, char key, size_t size )
{
    unsigned int index = hash( key, size );
    Node * node = findNode( map->table[ index ], key );

    return ( node != NULL );
}

int Map_get( Map * map,  char key, size_t size )
{
    unsigned int index = hash( key, size );
    Node * node = findNode( map->table[ index ], key );

    if ( node != NULL ) return node->value;

    return -1;
}

/*int main(){
 Map * complementMap = Map_create( 26 );
 char a[9] = {'a','b','c','d','a','a','b','d','b'};
 for (int i = 0; i < 9; i++){
     if(Map_contains(complementMap, a[i], 26) != 0){
        Map_add(complementMap, a[i], Map_get(complementMap, a[i], 26)+1, 26);
     }
     else{
     Map_add( complementMap, a[i], 1, 26);
     }
 }
 printf("%d", Map_contains( complementMap, 'a', 26 ));    
 printf("%d", Map_contains( complementMap, 'e', 26 ));    
 printf("%d", Map_contains( complementMap, 'b', 26 ));    
 printf("%d", Map_get( complementMap, 'b', 26 ));    
 printf("%d", Map_get( complementMap, 'a', 26 ));    
}
*/


