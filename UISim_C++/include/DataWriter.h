/*
 * DataWriter.h
 *
 *  Created on: 2019Äê3ÔÂ13ÈÕ
 *      Author: yichen_shen
 */

#ifndef DATAWRITER_H_
#define DATAWRITER_H_
#include<fstream>
#include<string>
using namespace std;
class DataWriter {
private:
ofstream out;
public:
	DataWriter(const string &filename);
	void close();
	void writeDouble(const double &v);
	void writeFloat(const float &v);
	void writeInteger(const int &v);
	void writeShort(const short &v);
	void writeBool(const bool &v);
	void writeChar(const char &v);
	void flush();
	virtual ~DataWriter();
};

#endif /* DATAWRITER_H_ */
