#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define N 51
// Tezwinder Singh (991491410)
// Harpreet kaur (991490561)
// Jaspinder Dhanesar (991486065)
// Gurvir Singh (991496917)



// This hashing function is the djb2 hash function implementation.
// You do NOT have to use this hash function - if you find another hash
// function you like better, feel free to use it.
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    // adding extra () to supress CLion warning messages about
    // using the "result of an assignment as a condition w/o parentheses"
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}


struct Block {
    // @TODO: Fill in the properites of a block
    long hash;
	char data[N];
	long currentTime;
	unsigned long previousHash;
	struct Block *next;
};

struct BlockChain {
    // @TODO: Fill in the properties of a block chain
    struct Block *root;
};

unsigned long calculateHash(unsigned char * blockData, long currentTime, unsigned long previousHash) {
    // @TODO: Write a function to calculate the hash of a block.
    
    return previousHash + currentTime + hash(blockData);
}

void disp(struct BlockChain *ptr) {
	int no = 1;
	struct Block *p;
	
	p = ptr->root;
	
	while(p != NULL) {
		
		printf("Block %d: %lu\n", no ++, p->hash);
		printf("\tData = \"%s\"\n", p->data);
		printf("Previous has = %lu\n", p->previousHash);
		p = p->next; 
	}
	
}

void addBlock(struct BlockChain *ptr, char *str) {
	struct Block *p, *q, *r;
	
	p = (struct Block*)malloc(sizeof(struct Block));
	p->currentTime = time(NULL);
	strcpy(p->data, str);
	p->previousHash = 0;
	p->next = NULL;
	
	if(ptr->root == NULL) {
		p->hash = calculateHash(str, p->currentTime, p->previousHash);
		
		ptr->root = p;
		
		return;
	}
	
	r = ptr->root;
	while(r != NULL) {
		q = r;
		r = r->next;
	}
		
	p->previousHash = q->hash;
	p->hash = calculateHash(str, p->currentTime, p->previousHash);
	
	q->next = p;
	
}

void checkChain(struct Block *genesisBlock) {
    //@TODO: Write the code to check if the block chain is valid
    // Your code should look something like this:

    // if (chainValid == true) { printf("CHAIN IS VALID!\n"); }
    // else { printf("CHAIN INVALID"); }
	
	if( genesisBlock == NULL ) {
		printf("CHAIN IS VALID!\n");
		return;
	}
	
	if (genesisBlock->previousHash != 0) {
		printf("CHAIN IS INVALID");
		return;
	}

	long hashVal;
	struct Block *p, *q;
	
	p = genesisBlock;

	while(1) {
		q = p->next;
		if(q == NULL) {
			printf("CHAIN IS VALID!\n");
			return;
		}
		
		if( calculateHash(q->data, q->currentTime, p->hash) != q->hash ) {
			printf("CHAIN IS INVALID!\n");
			return;
		}
		p = q; 
	}
	
}



int main() {

    // Example 1: How to generate a HASH of a string
    // ---------------------------

    unsigned char data[] = "Here is some nonsense";
    unsigned long hashValue = hash(data);
    printf("Data to hash: %s\n", data);
    printf("Hash value: %lu\n", hashValue);


    // Example 2: How to use C's time/date functions
    // ---------------------------


    // ---------------
    // Variables for detecting current time
    // ---------------
    time_t currentTime;
    char* formattedTime;


    // Get the current time (epoch time)
    // Epoch time = number of seconds that have passed since the year 1970.

    // See: https://www.epochconverter.com/
    currentTime = time(NULL);
    // Format epoch time into human readable time
    formattedTime = ctime(&currentTime);

    printf("Current formatted time is: %s", formattedTime);
    printf("Current epoch time is: %ld\n", currentTime);
    printf("----------\n");
	
	
	struct BlockChain *myBlockChain;
	
	myBlockChain = (struct BlockChain*)malloc(sizeof(struct BlockChain));
	
	myBlockChain->root = NULL;
	
	char inputStr[N];
	
	while(1) {
		printf("\nIf you need to add a new block, please input 'n'.\n");
		printf("If you need to display current blockchain, please input 'd'.\n");
		printf("If you need to check current blockchain, please input 'c'.\n");
		printf("If you need to finish this program, please input 'x'.\n\n");
		
		scanf("%s", inputStr);
		
		switch(inputStr[0]) {
			case 'n':
				printf("\nPlease input a string for block data.\n\n");
				scanf("%s", inputStr);
				addBlock(myBlockChain, inputStr);
				break;
			case 'd':
				disp(myBlockChain);
				break;
			case 'c':
				checkChain(myBlockChain->root);
				break;
			case 'x':
				return 0;
		}
	}
	
	
	
    return 0;
}



