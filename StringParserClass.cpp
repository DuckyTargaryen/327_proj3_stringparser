/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>
#include <iostream>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

using namespace KP_StringParserClass;
using namespace std;

/**
 * Constructor: initializes member variables.
 */
StringParserClass::StringParserClass(){
	pStartTag = NULL;
	pEndTag = NULL;
	areTagsSet = false;
}

/**
 * Destructor: calls cleanup to release allocated memory.
 */
StringParserClass::~StringParserClass(){
	cleanup();
}

/**
 * Sets the tags that are going to be searched for.
 * @param pStart - Pointer to opening tag.
 * @param pEnd - Pointer to closing tag.
 * @return int - States whether or not the tags were successfully set.
 */
int StringParserClass::setTags(const char *pStart, const char *pEnd){
	if(pStart == NULL || pEnd == NULL){
		return ERROR_TAGS_NULL;
	}
	//Creates a deep copy of the pointers
	int lenSt = strlen(pStart);
	int lenEn = strlen(pEnd);
	pStartTag = new char[lenSt + 1];
	pEndTag = new char[lenEn + 1];
	strncpy(pStartTag, pStart, lenSt);
	strncpy(pEndTag, pEnd, lenEn);
	areTagsSet = true;
	return SUCCESS;
}

/**
 * Gets the data between the tags and puts it into a vector.
 * @param pDataToSearchThru - The data being searched thru.
 * @param myVector - The vector that contains the targeted data.
 * @return int - States whether or not the data was able to be processed.
 */
int StringParserClass::getDataBetweenTags(char *pDataToSearchThru, std::vector<std::string> &myVector){
	myVector.clear();
	if(pStartTag == NULL || pEndTag == NULL){
		return ERROR_TAGS_NULL;
	}
	if(pDataToSearchThru == NULL){
		return ERROR_DATA_NULL;
	}
	int result = SUCCESS;
	//Creates pointers to track various instances of tags being found.
	char* endOp = pDataToSearchThru;
	char* endCl = pDataToSearchThru;
	while(result == SUCCESS){
		char* tStarOp = endOp;
		//Searches for an instance of the opening tag.
		result = findTag(pStartTag, tStarOp, endOp);
		if(result == ERROR_TAGS_NULL){
			return ERROR_TAGS_NULL;
		}
		char* tStarCl = endCl;
		//Won't search for closing tag if opening tag cannot be found.
		if(result != FAIL){
			//Searches for an instance of the closing tag.
			result = findTag(pEndTag, tStarCl, endCl);
		}
		//If the opening and closing tags can be found, get the data between them.
		if(result != FAIL){
			string str = "";
			int i = 1;
			bool end = false;
			while(!end){
				if(*(endOp + i) == *tStarCl){
					int j = 0;
					//Makes sure the closing tag found is the create closing tag.
					while(*(endOp + i + j) != *endCl){
						if(*(endOp + i + j) != *(tStarCl + j)){
							end = false;
							break;
						}
						end = true;
						j++;
					}
				}
				if(end != true){
					str += *(endOp + i);
				}
				i++;
			}
			myVector.push_back(str);
		}
	}
	return SUCCESS;
}

/**
 * Releases allocated memory.
 */
void StringParserClass::cleanup(){
	if(pStartTag)
		delete[] pStartTag;
	if(pEndTag)
		delete[] pEndTag;
}


/**
 * Finds the next instance of the desired tag.
 * @param pTagToLookFor - The desired opening or closing tag.
 * @param pStart - The point at which the program starts looking for the opening tag.
 * @param pEnd - The point at which the tag ends.
 * @return int - Indicates whether or not the tag was successfully found.
 */
int StringParserClass::findTag(char *pTagToLookFor, char *&pStart, char *&pEnd){
	if(pStart == NULL || pEnd == NULL){
		return ERROR_TAGS_NULL;
	}
	int dataLen = strlen(pStart);
	for(int i = 0; i < dataLen; i++){
		//Checks if the beginning of a tag is found.
		if(*pTagToLookFor == *(pStart + i)){
			int k = 0;
			while(*(pTagToLookFor + k) == *(pStart + i + k)){
				//Checks if the tag matches the desired tag.
				if (*(pTagToLookFor + k) == '>'){
					pStart = (pStart + i);
					pEnd = (pEnd + k + i);
					return SUCCESS;
				}
				k++;
			}
		}
	}
	pEnd = 0;
	return FAIL;
}




