/*
 * TextReader.cpp
 *
 *  Created on: 2019Äê3ÔÂ13ÈÕ
 *      Author: yichen_shen
 */

#include "TextReader.h"
#include <iostream>
#include <cassert>
#include <Trim.h>
TextReader::TextReader(const string& filename) {
	in.open(filename.c_str(), ios::in);
	assert(in.is_open());
	ignoreEmptyLine = true;
}

TextReader::~TextReader() {
	in.close();
	// TODO Auto-generated destructor stub
}

void TextReader::setIgnoreEmptyLine(const bool& val) {
	ignoreEmptyLine=val;
}

void TextReader::setIgnoreStart(const vector<string> &words) {
		ignoreStart = words;

}

bool TextReader::hasIgnoredStart(const string& line) {
	for (auto &s : ignoreStart)
	{
		if(line.find(s)==0)
			return true;
	}
	return false;
}

void TextReader::close() {
	in.close();
}

string TextReader::readln() {
	string s;
    while (!in.eof() )
    {

        getline(in,s);
        //trim
        Trim(s);

		  if((ignoreEmptyLine && s.empty()) || this->hasIgnoredStart(s))

			  	s.resize(0);
			else
				break;
    }
    return s;
}

string TextReader::readOrigninalLine() {
	string s;
    getline(in,s);
    return s;
}
