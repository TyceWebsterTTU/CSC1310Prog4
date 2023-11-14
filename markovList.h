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
	edge* newEdge;
	int i = 0;
	srand (time(0));
	
	if(file.good()) {
	file >> corpusSize;
	file.ignore(1, '\n');
	
	while(getline(file, line, '\n')) //map every word to a position in the matrix, keep the line in an array of buffers for later
	{
		parser.clear();
		parser << line;
		getline(parser, index,',');	//pulls the first word of the line, which is the node for which we're making a list of neighbors

		corpus[index] = NULL;

		//initialize an empty list at the index---
		while(getline(parser, word, ','))
		{
			//allocate a new node in the edge list---
			newEdge = NULL;
			newEdge = new edge;

			splitter.clear();
			splitter.str(word);
			splitter >> word >> weight;

			//stick word and weight on the node you've just allocated---
			newEdge->weight = weight;
			newEdge->word = word;

			//make sure your new node is attached to the list---
			if(corpus[index] == NULL)
			{
				corpus[index] = newEdge;
				corpus[index]->next = NULL;
			}
			else
			{
				edge* entry;

				entry = corpus[index];

				while(entry->next != NULL)
				{
					entry = entry->next;
				}

				entry->next = newEdge;
				newEdge->next = NULL;
			}
		}
	}}
}

markovList::~markovList()
{
	//write this
	for(map<string, edge*>::iterator it = corpus.begin(); it != corpus.end(); it++)
	{
		delete corpus[it->first];
	}
}
		
string markovList::generate(int length)
{
	map<string, edge*>::iterator it = corpus.begin();	//initialize an iterator to find a random node in the next line
	advance(it,rand() % corpusSize);	//this grabs a random node from your corpus as a starting point

	//write the rest of this
	string word, first;
	int weight;
	float roll;
	edge* second;

	first = it->first;
	second = it->second;
	weight = second->weight;

	for(int i = 0; i < length; i++)
	{
		roll = (float)rand() / RAND_MAX;

		while(roll > weight)
		{
			weight += second->weight;
			second = second->next;
		}

		second = corpus[second->word];

		word += first + second->word;
		word += "\n";
		first = second->word;
	}

	return word;
}


#endif