stdio.h>
#include <string.h>
#include <stdlib.h>
#include "static_stack.h"
#include "static_queue.h"
#include "static_tree.h"

#define TAMNICK 15
#define TAMNAME 50
#define TAMTREE 50
#define ERROR 1

void newTree( TREE* myt ){
	myt->full = 0;
	myt->root = -1;
}
void newUser( NODE* myuser, char* name, char* nick ){
	newStack( &((*myuser).texts) );
	newQueue( &((*myuser).asks) );
	strcpy( myuser->name, name );
	strcpy( myuser->nick, nick );
	myuser->numfriends = 0;
	myuser->left = -1;
	myuser->right = -1;
	myuser->father = -1;
}
int addUser( TREE* myt, int node, char* name, char* nick ){
	if( node == -1 ) return ERROR;
	int i = strcmp( nick, myt->users[node].nick );
	if( i == 0 ) return ERROR;
	if( i < 0 ){
		if( myt->users[node].left == -1 ){
			newUser( &((*myt).users[ myt->full ]), name, nick );
			(*myt).users[ myt->full ].father = node;
			(*myt).users[ node ].left = myt->full;
			myt->full++;
			return !ERROR;
		}
		return addUser( myt, myt->users[node].left, name, nick );
	}
	if( myt->users[node].right == -1 ){
		newUser( &((*myt).users[ myt->full ]), name, nick );
		(*myt).users[ myt->full ].father = node;
		(*myt).users[ node ].right = myt->full;
		myt->full++;
		return !ERROR;
	}
	return addUser( myt, myt->users[node].right, name, nick );
}

int wrapAddUser( TREE* myt, char* name, char* nick ){
	if( myt->root == -1 ){
		myt->root = 0;
		newUser( &(myt->users[0] ), name, nick );
		myt->full++;
		return 0;
	}
	if( isFull( myt ) ) return ERROR;
	else return addUser( myt, myt->root, name, nick );
}

NODE* findUser( TREE* myt, int node, char* nick ){
	if( node == -1 ) return NULL;
	int cmp = strcmp( myt->users[node].nick, nick );
	if( cmp == 0 ) return &( (*myt).users[ node ] );
	if( cmp < 0 ) return findUser( myt, myt->users[ node ].right, nick );
	return findUser( myt, myt->users[ node ].left, nick );
}

NODE* wrapFindUser( TREE* myt, char* nick ){
	return findUser( myt, myt->root, nick );
}

void dumpTree( TREE* myt, int node ){
	if( node == -1 ) return;
	int i;
	dumpTree( myt, myt->users[node].left );
	printf(" %s\n %s\n\n", myt->users[node].name, myt->users[node].nick );
	for( i=0; i< myt->users[node].numfriends; i++ ){
		printf("%s ", myt->users[ node ].friends[ i ]->name );
	}
	dumpTree( myt, myt->users[node].right );
}

void dump( TREE* myt ){
	if( myt == NULL ) return;
	int i;
	for( i=0; i<myt->full; i++ ){
		printf("%s  %s ", myt->users[i].name, myt->users[i].nick );
//		printf("%d %d %d %d\n", myt->users[i].father, myt->users[i].left, myt->users[i].right,i );

	}
}

void clearTree( TREE* myt ){
	myt->root = -1;
	myt->full = 0;
}
void addTree( TREE* myt, TREE* myt2, int myno ){
	if( myno == -1 ) return;
	wrapAddUser( myt, myt2->users[ myno ].name, myt2->users[ myno ].nick );
	addTree( myt, myt2, myt2->users[ myno ].right );
	addTree( myt, myt2, myt2->users[ myno ].left );
}
void wrapAddTree( TREE* first, TREE* sec ){
	addTree( first, sec, sec->root );
}

NODE* findFriend( NODE* myuser, char* nick ){
	int i;
	for( i=0; i<myuser->numfriends; i++ ){
		if( strcmp( nick, myuser->friends[i]->nick ) == 0 )
			return ( myuser->friends[i] );
	}
	return NULL;
}

int isFull( TREE* myt ){
	if( myt->full == TAMTREE ) return 1;
	return 0;
}
