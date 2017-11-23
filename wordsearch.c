/*
Time complexity analysis:

Task1:O(n^2*m)
To choose two words to compare differences, we need to loop twice. The outer loop to choose word1 and the inner loop to choose word2 and both of them loop n(the number of words input) times. By now the time complexity is O(n^2). Then when comparing differencs between two words inside the inner loop, there will be one more loop at most which loops m(the length of words) times. So the time complexity in total is O(n^2*m).

Task2:o(n^n)
There are n words in the graph. Considering the worst case, the first node is followed by n-1 words, the second word is followed by n-2 words, the third is followed by n-2 words and so on. As I used BFS recursion, in this case, it will loop n! + (n-1)! + ... + 2! + 1! times , so the time complexity in total is O(n^n).
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "queue.h"
#include "Graph.h"

#define LINE_LENGTH 1024
#define WORD_LENGTH 20

// if two words only have one difference then return 1, else return 0
int compare(char *word1,char *word2){
	int length1 = strlen(word1);
	int length2 = strlen(word2);
	
	// if the difference of the lengths of two words is larger than 1
	if(abs(length1 - length2) > 1){
		return 0;
	}
	// if the difference of the lengths of two words is 1
	else if (abs(length1 - length2) == 1){
		// put the long word into longword and the short word into shortword
		char longword[WORD_LENGTH]="";
		char shortword[WORD_LENGTH]="";
		int length,i,j;
		if(length1 > length2){
			for (i=0; i<length1; i++){
				longword[i] = word1[i];
			}
			for (j=0; j<length2; j++){
				shortword[j] = word2[j];
			}
			length = length2;
		}
		else{			
			for (i=0; i<length2; i++){
				longword[i] = word2[i];
			}
			for (j=0; j<length1; j++){
				shortword[j] = word1[j];
			}
			length = length1;
		}
		// find the different letter
		int index = 0;
		while(longword[index] == shortword[index]){
			index++;
		}
		// remove the different letter from long word
		memmove(&longword[index], &longword[index + 1], strlen(longword) - index);
		// compare the short word and long word
		int re = strcmp(longword, shortword);
		if(re == 0){
			return 1;
		}
		else{
			return 0;
		}
	}
	// if the two words share the same length then check the amount of differences between them
	else{
		int diff = 0;
		int i = 0;
		while(i<length1 && diff < 2){
			if(word1[i] != word2[i]){
				diff++;
			}
			i++;
		}
		if(diff == 1){
			return 1;
		}
		else{
			return 0;
		}
	}
}

/*
implementation of breadth first seach
graph: 	  	  the grapths which store the relation of words
start:		  the start node
number: 	  the numebr of input words
*/
//void BFS(Graph graph, int start, int number){
//	int i;
//	
//	int visited[number];
//	for(i=0; i<number; i++){
//		visited[i] = 0;
//	}
//	visited[start] = 1;
//	
//	queue nodes = newQueue();
//	QueueEnqueue(nodes, start);
//	while (!QueueIsEmpty(nodes)) {
//		int current_node = QueueDequeue(nodes);
//		printf("%d ", current_node);
//		for(i=start+1; i<number; i++){
//			bool adjacence = adjacent(graph, current_node, i);
//			if(adjacence == true && visited[i] == 0){
//				visited[i] = 1;
//				QueueEnqueue(nodes, i);
//			}
//		}
//	}
//	printf("\n");
//}

/*
wordGraph: 	  the grapths which stores the relations of words
number: 	  the numebr of words input
paths: 		  a two-dimensional array to store the temporary paths
allpaths:	  the pointer which points to the address the two-dimensional array which stores all paths
maximumPaths: possible maximum number of paths
*/
void findAllPaths(Graph wordGraph, int number, int paths[number][number+1], int *allPaths, int maximumPaths){
	int m,n,i,j;
	int pathIndex=0;

	while(paths[pathIndex][0] != -1){
		// get the last node of the path
		int length = paths[pathIndex][0];
		int lastNode = paths[pathIndex][length];
		
		// find all the adjacent nodes of this last ndoe and enqueue in the queue
		queue adjacentNodes = newQueue();
		for(i = lastNode + 1; i<number; i++){
			bool adjacence = adjacent(wordGraph, lastNode, i);
			if(adjacence == true){
				//printf("adjacentNode: %d\n",i);
				QueueEnqueue(adjacentNodes, i);
			}
		}
		
		// if the queue storing adjacent nodes is empty, it means this path has reached end
		if(QueueIsEmpty(adjacentNodes)){
			// store the path into allPaths
			for(i=0; i<maximumPaths; i++) {
				// find the empty line in allPaths, insert the current path and break the loop;
				if (*(allPaths + i * (number + 1)) == -1){
					for(j=0; j<length+1; j++){
						*(allPaths + i * (number + 1) + j) = paths[pathIndex][j];
					}
					break;
				}
			}
		}
		// if the queue storing adjacent nodes is not empty, it means this path has not reached end
		// then put the adjacent nodes at the end of the current paths
		// use recursion to find the remaining parts of these paths
		else{
			// init a new two-dimensional array to store the latest paths
			int newPathIndex = 0;
			int new_paths[number][number+1];
			for(m=0; m<number; m++){
				for(n=0; n<number+1; n++){
					new_paths[m][n] = -1;
				}
			}
			while (!QueueIsEmpty(adjacentNodes)) {
				int newLastNode = QueueDequeue(adjacentNodes);
				
				// unpdate the current paths into the new_paths array 
				for (i=1;i<length+1;i++) {
					new_paths[newPathIndex][i] = paths[pathIndex][i];
				}
				new_paths[newPathIndex][length+1] = newLastNode;
				new_paths[newPathIndex][0] = length+1;
				newPathIndex++;
			}
			
			findAllPaths(wordGraph, number, new_paths, allPaths, maximumPaths);
		}
		
		dropQueue(adjacentNodes);
		pathIndex++;
	}
}

int main(int argc, char *argv[]) {
	int i, j, m, n;
	// read the numebr of words
	printf("Enter a number: ");
	int number;
	scanf("%d", &number);
	// store the words
	char words[number][WORD_LENGTH];
	for (i=0; i<number; i++){
		printf("Enter word: ");
		char word[WORD_LENGTH];
		scanf("%s", word);
		strcpy(words[i],word);
	}
	
	Graph wordGraph = newGraph(number);
	printf("\n");
	for (i=0; i<number-1; i++){
		char *word1 = words[i];
		printf("%s:", word1);
		for (int j=i+1; j<number; j++){
			char *word2 = words[j];
			//compare if every two words have only one difference
			int result = compare(word1,word2);
			// if there is only one difference then insert their indexs into graph
			if(result == 1){
				printf(" %s", word2);
				Edge e;
				e.v = i;
				e.w = j;
				insertEdge(wordGraph,e);
			}
		}
		printf("\n");
	}
	char *lastword = words[number-1];
	printf("%s:\n", lastword);
	
	// possible maximum number of paths is number * (number-1) * ... * 2 * 1;
	int maximumPaths = 1;
	for(i=number; i>0; i--){
		maximumPaths = maximumPaths * i;
	}
	// init a two-dimensional array to store all paths and the first column of each row is the length of this path
	int allPaths[maximumPaths][number+1];
	for(m=0; m<maximumPaths; m++){
		for(n=0; n<number+1; n++){
			allPaths[m][n] = -1;
		}
	}
	
	// find paths starting from every node one by one
	for(i=0; i<number; i++){
		// init a two-dimensional array to store the temporary paths and the first column of each row is the length of this path
		int paths[number][number+1];
		for(m=0; m<number; m++){
			for(n=0; n<number+1; n++){
				paths[m][n] = -1;
			}
		}
		// init the starting node and length
		paths[0][0] = 1;
		paths[0][1] = i;
		findAllPaths(wordGraph, number, paths, &allPaths[0][0], maximumPaths);
	}
	
	// find the maximum length
	int maximumLength = 0;
	for(m=0; m<maximumPaths; m++){
		if(allPaths[m][0] > maximumLength){
			maximumLength = allPaths[m][0];
		}
	}
	
	freeGraph(wordGraph);
	
	printf("\n");
	printf("Maximum chain length: %d\n", maximumLength);
	printf("Maximal chains:");
	
	// print the word chains
	int wordIndex;
	for(m=0; m<maximumPaths; m++){
		if(allPaths[m][0] == maximumLength){
			printf("\n");
			for(n=1; n<maximumLength; n++){
				wordIndex = allPaths[m][n];
				printf("%s -> ",words[wordIndex]);
			}
			wordIndex = allPaths[m][maximumLength];
			printf("%s",words[wordIndex]);
		}
	}
}