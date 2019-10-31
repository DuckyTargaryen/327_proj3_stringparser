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
	if(pDataToSearchThru == NULL){
		return ERROR_DATA_NULL;
	}
	if(pStartTag == NULL || pEndTag == NULL){
		return ERROR_TAGS_NULL;
	}
	int dataLen = strlen(pDataToSearchThru);
	for(int i = 0; i < dataLen; i++){
		if(pDataToSearchThru[i] == *pStartTag){
			//findTag(*pStartTag, *pStartTag, *pStartTag);
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
int findTag(char *pTagToLookFor, char *&pStart, char *&pEnd){
	if(pStart == NULL || pEnd == NULL){
		return ERROR_TAGS_NULL;
	}
	//cout << *pStart << endl;

	return 0;
}





