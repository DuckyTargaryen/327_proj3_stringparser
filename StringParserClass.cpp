/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

using namespace KP_StringParserClass;

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
	char tempSt = *pStart;
	char tempEn = *pEnd;

	pStartTag = &tempSt;
	pEndTag = &tempEn;
	return SUCCESS;
}

int StringParserClass::getDataBetweenTags(char *pDataToSearchThru, std::vector<std::string> &myVector){
	return 0;
}

void StringParserClass::cleanup(){
	if(pStartTag)
		delete[] pStartTag;
	if(pEndTag)
		delete[] pEndTag;
}

int findTag(char *pTagToLookFor, char *&pStart, char *&pEnd){
	return 0;
}





