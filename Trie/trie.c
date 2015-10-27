#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

//Alphabet_size
#define ALPHABET_SIZE (26)
// Converts key current character into index
// use only 'a' through 'z' and low case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

//trie node
typedef struct trie_node trie_node_t;
struct trie_node
{
	int value;
	trie_node_t *children[ALPHABET_SIZE];
};

// trie ADT
typedef struct trie trie_t;
struct trie
{
	trie_node_t *root;
	int count;
};

// Returns new trie node (initialized to NULLs)
trie_node_t *getNode(void)
{
	trie_node_t *pNode = NULL;
	pNode = (trie_node_t*)malloc(sizeof(trie_node_t));
	if(pNode)
	{
		int i;
		pNode->value = 0;
		for(i = 0;i < ALPHABET_SIZE;++i)
		{
			pNode->children[i] = NULL;
		}
	}
	return pNode;
}

//Initializes trie (root is dummy node)
void initialize(trie_t *pTrie)
{
	pTrie->root = getNode();
	pTrie->count = 0;
}

//if not present,inserts key into trie
//if the key is prefix of trie node,just marks leaf node
void insert(trie_t *pTrie,char key[])
{
	int level;
	int length = strlen(key);
	int index;
	trie_node_t *pCrawl;

	pTrie->count++;
	pCrawl = pTrie->root;

	for(level = 0;level < length;++level)
	{
		index = CHAR_TO_INDEX(key[level]);
		if(!pCrawl->children[index])
		{
			pCrawl->children[index] = getNode();
		}
		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf
	pCrawl->value = pTrie->count;
}

// Return non zero,if key prsents in trie
int search(trie_t *pTrie,char key[])
{
	int level;
	int length = strlen(key);
	int index;
	trie_node_t *pCrawl;

	pCrawl = pTrie->root;

	for(level = 0;level < length;++level)
	{
		index = CHAR_TO_INDEX(key[level]);
		if(!pCrawl->children[index])
		{
			return 0;
		}
		pCrawl = pCrawl->children[index];
	}
	return (0 != pCrawl && pCrawl->value);
}

void destroyTrie(trie_node_t *root)
{
	trie_node_t *pCrawl = root;
	for(int i = 0;i < ALPHABET_SIZE;++i)   //free children
	{
		if(pCrawl->children[i])   //not null
		{
			if(pCrawl->children[i]->value != 0)   //end
			{
				free(pCrawl->children[i]);
				pCrawl->children[i] = NULL;
			}
			else     //not the end
			{
				destroyTrie(pCrawl->children[i]);
			}
		}
	}
	free(root);   //free itself
	root = NULL;
}

// Driver
int main()
{
	// Input keys (use only 'a' through 'z' and low case)
	char keys[][8] = {"the","a","there","answer","any","by","bye","their"};
	trie_t trie;

	char output[][32] = {"Not present in trie","Present in trie"};
	initialize(&trie);

	//Construct trie
	for(int i = 0;i < ARRAY_SIZE(keys);++i)
	{
		insert(&trie,keys[i]);
	}

	//Search for different keys
	printf("%s --- %s\n","the",output[search(&trie,"the")]);
	printf("%s --- %s\n","these",output[search(&trie,"these")]);
	printf("%s --- %s\n","their",output[search(&trie,"their")]);
	printf("%s --- %s\n","thaw",output[search(&trie,"thaw")]);

	// Destroy Trie
	destroyTrie(trie.root);   
	return 0;
}
