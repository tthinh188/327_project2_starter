/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
//	TODO add necessary includes here
#include <stdio.h>
#include "array_functions.h"
#include "constants.h"
#include "utilities.h"

using namespace std;
using namespace constants;
//============================================================================

//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur
struct entry {
	string word;
	int number_occurence;
};
//TODO add a global array of entry structs (global to this file)
entry *entryArray = new entry[MAX_WORDS];
//TODO add variable to keep track of next available slot in array
int arraySize = 0;
//TODO define all functions in header file
void clearArray() {
	entryArray = new entry[MAX_WORDS];
	arraySize = 0;
}

int getArraySize() {
	return arraySize;
}

std::string getArrayWordAt(int i) {
	return entryArray[i].word;
}

int getArrayWord_NumbOccur_At(int i) {
	return entryArray[i].number_occurence;
}

bool processFile(std::fstream &myfstream) {
	if (myfstream.is_open()) {
		return false;
	} else {
		std::string line;
		while (!myfstream.eof()) {
			getline(myfstream, line);
			processLine(line);
		}
		return true;
	}
}

void processLine(std::string &myString) {
	stringstream ss(myString);
	string tempToken;
	while (getline(ss, tempToken, CHAR_TO_SEARCH_FOR)) {
		processToken(tempToken);
	}
}

int find(std::string &token) {
	for (int i = 0; i < getArraySize(); i++) {
		if (token == entryArray[i].word) {
			return i;
		}
	}
	return FAIL;
}

void processToken(std::string &token) {
	bool strip;
	strip = strip_unwanted_chars(token);
	if (find(token) != FAIL) {
		entryArray[find(token)].number_occurence = +1;
	} else {
		entryArray[getArraySize()].word = token;
		entryArray[getArraySize()].number_occurence += 1;
		arraySize += 1;
	}
}
bool openFile(std::fstream &myfile, const std::string &myFileName,
		std::ios_base::openmode mode = std::ios_base::in) {
	myfile.open(myFileName.c_str());
	if(myfile.is_open()){
		return true;
	}
	else{
		return false;
	}
}

void closeFile(std::fstream &myfile) {
	if (myfile.is_open()) {
		myfile.close();
	}
}

int writeArraytoFile(const std::string &outputfilename) {
	ofstream myOutputfile;
	myOutputfile.open(outputfilename.c_str());
	if (getArraySize() == 0) {
		return FAIL_NO_ARRAY_DATA;
	} else if (!myOutputfile.is_open()) {
		return FAIL_FILE_DID_NOT_OPEN;
	} else {
		for (int i = 0; i < getArraySize(); i++) {
			myOutputfile
					<< entryArray[i].word + " ";
//							+ std::to_string(entryArray[i].number_occurence);
		}
		return SUCCESS;
	}
}

void sortArray(constants::sortOrder so) {
	entry temp;
	switch(so){
		case ASCENDING:
			for(int i=0;i< getArraySize() ;i++)
				{
					for(int j=i+1;j< getArraySize();j++)
					{
						if(entryArray[i].word > entryArray[j].word)
						{
							temp  =entryArray[i];
							entryArray[i]=entryArray[j];
							entryArray[j]=temp;
						}
					}
				}
			break;
		case DESCENDING:
			for(int i=0;i< getArraySize() ;i++)
						{
							for(int j=i+1;j< getArraySize();j++)
							{
								if(entryArray[i].word < entryArray[j].word)
								{
									temp  =entryArray[i];
									entryArray[i]=entryArray[j];
									entryArray[j]=temp;
								}
							}
						}
			break;
		case NUMBER_OCCURRENCES:
			for(int i=0;i< getArraySize() ;i++)
						{
							for(int j=i+1;j< getArraySize();j++)
							{
								if(entryArray[i].number_occurence > entryArray[j].number_occurence)
								{
									temp  =entryArray[i];
									entryArray[i]=entryArray[j];
									entryArray[j]=temp;
								}
							}
						}
			break;
		default:
			break;
	}
}
//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!
