#ifndef MARKOVMAT_H
#define MARKOVMAT_H

#include<map>
#include<fstream>
#include<sstream>
#include<iostream>
#include<stdlib.h>
using namespace std;

class markovMat
{
	private:
		struct matrix{
			map<string, int> buckets;
		};
		matrix corpus;
	public:
		markovMat(const char*);
		~markovMat();
		
		string generate(int);
};

markovMat::markovMat(const char* filename)
{
	ifstream file(filename);
	stringstream* parser;
	stringstream splitter;
	string line, word;
	float weight;
	int i = 0;
	srand (time(0));
	
	if(file.good()) {
	file >> corpusSize;
	file.ignore(1, '\n');
	//allocate memory for the matrix and set every value to 0---

	parser = new stringstream[corpusSize];
	
	while(getline(file, line, '\n')) //map every word to a position in the matrix, keep the line in an array of buffers for later
	{
		parser[i] << line;
		getline(parser[i], word,',');
		//assign an index number to the map for the current word
		i++;
	}
	for(i = 0; i < corpusSize; i++) //populate matrix using buffer array
	{
		while(getline(parser[i], word, ','))
		{
			splitter.clear();
			splitter.str(word);
			splitter >> word >> weight;
			//add weight into the matrix, with the first index as the starting node and the second index at the destination node
		}
	}}
}

markovMat::~markovMat()
{
//write this
}

string markovMat::generate(int length)
{
	//pick random starting node
	map<string, int>::iterator it = corpus.buckets.begin();		//initialize an iterator to find a random node in the next line
	advance(it,rand() % corpusSize);	//this grabs a random node from your corpus as a starting point
//you'll need to write the rest of this
}

#endif