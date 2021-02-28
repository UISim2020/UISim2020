/*
 * TextWriter.cpp
 *
 *  Created on: 2019Äê3ÔÂ13ÈÕ
 *      Author: yichen_shen
 */

#include "TextWriter.h"
#include <cassert>

TextWriter::TextWriter(const string& filename) {
	out.open(filename.c_str(), ios::out);
	assert(out.is_open());
}

void TextWriter::write(const int& i) {
	out<<i;

}

void TextWriter::write(const double& d) {
	out<<d;
}

void TextWriter::writeln(const int& i) {
	out<<i<<endl;
}

void TextWriter::writeln(const double& d) {
	out<<d<<endl;
}

void TextWriter::write(const string& s) {
	out<<s;
}

void TextWriter::writeln(const string& s) {
	out<<s<<endl;
}

void TextWriter::writeln() {
	out<<endl;
}

void TextWriter::close() {
	out.close();
}

void TextWriter::flush() {
out.flush();
}

TextWriter::~TextWriter() {
	out.close();
}

