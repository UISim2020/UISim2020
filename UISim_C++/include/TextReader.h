/*
 * TextReader.h
 *
 *  Created on: 2019Äê3ÔÂ13ÈÕ
 *      Author: yichen_shen
 */

#ifndef TEXTREADER_H_
#define TEXTREADER_H_
#include<fstream>
#include<string>
#include<vector>

using namespace std;

class TextReader {

	private:
	bool ignoreEmptyLine;
	vector<string> ignoreStart;
	ifstream in;
public:
	TextReader(const string &filename);
	virtual ~TextReader();
	void setIgnoreEmptyLine(const bool &val);
	void setIgnoreStart(const vector<string> &words);
	bool hasIgnoredStart(const string &line);
	void close();
	string readln();
	string readOrigninalLine();
};

#endif /* TEXTREADER_H_ */
