/*
Authors: Tyce Webster and Isaac Essex
Date:11/15/2023
Filename:markovList.h
Purpose: Utilize an AI algorithm called a Markov Chain. This one is done 
using an adjancency list.
*/
#ifndef MARKOVLIST_H
#define MARKOVLIST_H

#include<map>
#include<fstream>
#include<sstream>
#include<iostream>
#include<stdlib.h>
#include <ctime>
using namespace std;

class markovList
{
	private:
		struct edge
		{
			string word;
			float weight;
			edge* next;
		};
		map<string, edge*> corpus;
		int corpusSize; 
	public:
		markovList(const char*);
		~markovList();
		
		string generate(int);
};

markovList::markovList(const char* filename)
{
	ifstream file(filename);
	stringstream parser, splitter;
	string line, index, word;
	float weight;
	int i = 0;
	srand (time(0)); //Seeding randomness
	
	if(file.good()) { //Checking file
	file >> corpusSize;
	file.ignore(1, '\n');
	
	while(getline(file, line, '\n')) //map every word to a position in the matrix, keep the line in an array of buffers for later
	{
		parser.clear();
		parser << line;
		getline(parser, index,',');	//pulls the first word of the line, which is the node for which we're making a list of neighbors

		//corpus[index] = NULL;
		if(corpus.find(index) == corpus.end())
		{
			corpus[index] = NULL;
		}

		edge* curr = NULL;

		//initialize an empty list at the index---
		while(getline(parser, word, ','))
		{
			edge* newEdge;
			//allocate a new node in the edge list---
			newEdge = new edge;

			splitter.clear();
			splitter.str(word);
			splitter >> word >> weight;

			//stick word and weight on the node you've just allocated---
			newEdge->weight = weight;
			newEdge->word = word;
			newEdge->next = NULL;

			//make sure your new node is attached to the list---
			if(curr == NULL)
			{
				corpus[index] = newEdge;
				curr = newEdge;
			}
			else
			{
				curr->next = newEdge;
				curr = newEdge;
			}
		}
	}}
}

markovList::~markovList()
{
	//pointers for tracking position in list
	edge* curr;
	edge* temp;
	//write this
	//iterate through the entire list and deallocate
	for(map<string, edge*>::iterator it = corpus.begin(); it != corpus.end(); ++it)
	{
		curr = it->second;

		while(curr)
		{
			temp = curr->next;
			delete curr;
			curr = temp;
		}
	}
}
		
string markovList::generate(int length)
{
	map<string, edge*>::iterator it = corpus.begin();	//initialize an iterator to find a random node in the next line
	advance(it,rand() % corpusSize);	//this grabs a random node from your corpus as a starting point

	//write the rest of this
	string word;
	float roll, total;
	edge* curr;

	word = it->first; //establish a start to our string
	curr = it->second;

	//Loop for as many words as we want to generate
	for(int i = 1; i < length; i++)
	{
		if(curr == NULL)
		{
			break;
		}

		roll =  (float)rand() / RAND_MAX; //determine what node we traverse to

		total = 0.0;

		//traverse to that random node
		while(curr != NULL)
		{
			total += curr->weight;//keep adding the weights of the individual nodes until they are greater than roll

			if(total > roll)
			{
				word += " " + curr->word;
				curr = corpus[curr->word];

				break;
			}

			//if the total is not great enough yet, check the next node and add it to the total
			curr = curr->next;
		}
	}

	//finally, we have enough random words and can return them to be printed
	return word;
}

#endif