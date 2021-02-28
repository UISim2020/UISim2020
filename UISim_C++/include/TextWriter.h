/*
 * TextWriter.h
 *
 *  Created on: 2019Äê3ÔÂ13ÈÕ
 *      Author: yichen_shen
 */

#ifndef TEXTWRITER_H_
#define TEXTWRITER_H_
#include<fstream>
#include<string>
using namespace std;
class TextWriter {
	private:
	ofstream out;
public:
	TextWriter(const string& filename);
	void write(const int &i);
	void write(const double &d);
	void writeln(const int &i);
	void writeln(const double &d);
	void write(const string &s);
	void writeln(const string &s);
	void writeln();
	void close();
	void flush();
	virtual ~TextWriter();
};

#endif /* TEXTWRITER_H_ */
