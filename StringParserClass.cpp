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

StringParserClass::StringParserClass(){
	pStartTag = NULL;
	pEndTag = NULL;
	areTagsSet = false;
}

StringParserClass::~StringParserClass(){
	cleanup();
}

int StringParserClass::setTags(const char *pStart, const char *pEnd){
	if(pStart == NULL || pEnd == NULL){
		return ERROR_TAGS_NULL;
	}
	int lenSt = strlen(pStart);
	int lenEn = strlen(pEnd);
	pStartTag = new char[lenSt + 1];
	pEndTag = new char[lenEn + 1];
	strncpy(pStartTag, pStart, lenSt);
	strncpy(pEndTag, pEnd, lenEn);
	areTagsSet = true;
	return SUCCESS;
}

//First clears myVector
//going to search thru pDataToSearchThru, looking for info bracketed by
//pStartTag and pEndTag, will add that info only to myVector
//returns
//SUCCESS  finished searching for data between tags, results in myVector (0 or more entries)
//ERROR_TAGS_NULL if either pStart or pEnd is null
//ERROR_DATA_NULL pDataToSearchThru is null
int StringParserClass::getDataBetweenTags(char *pDataToSearchThru, std::vector<std::string> &myVector){
	myVector.clear();
	if(pStartTag == NULL || pEndTag == NULL){
		return ERROR_TAGS_NULL;
	}
	if(pDataToSearchThru == NULL){
		return ERROR_DATA_NULL;
	}
	int result = SUCCESS;
	char* endOp = pDataToSearchThru;
	char* endCl = pDataToSearchThru;
	while(result == SUCCESS){
		char* tStarOp = endOp;
		result = findTag(pStartTag, tStarOp, endOp);
		if(result == ERROR_TAGS_NULL){
			return ERROR_TAGS_NULL;
		}
		char* tStarCl = endCl;
		result = findTag(pEndTag, tStarCl, endCl);
		if(result != FAIL){
			string str = "";
			int i = 1;
			while (*(endOp + i) != *tStarCl){

				str += *(endOp + i);
				i++;
			}
			myVector.push_back(str);
		}
	}
	return SUCCESS;
}

void StringParserClass::cleanup(){
	if(pStartTag)
		delete[] pStartTag;
	if(pEndTag)
		delete[] pEndTag;
}


//Searches a string starting at pStart for pTagToLookFor
//returns:
//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
//FAIL did not find pTagToLookFor and pEnd points to 0
//ERROR_TAGS_NULL if either pStart or pEnd is null
int StringParserClass::findTag(char *pTagToLookFor, char *&pStart, char *&pEnd){
	if(pStart == NULL || pEnd == NULL){
		return ERROR_TAGS_NULL;
	}
	int dataLen = strlen(pStart);
	for(int i = 0; i < dataLen; i++){
		if(*pTagToLookFor == *(pStart + i)){
			int k = 0;
			while(*(pTagToLookFor + k) == *(pStart + i + k)){
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




