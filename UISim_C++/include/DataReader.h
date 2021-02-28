/*
 * DataReader.h
 *
 *  Created on: 2019Äê3ÔÂ13ÈÕ
 *      Author: yichen_shen
 */

#ifndef DATAREADER_H_
#define DATAREADER_H_
#include<fstream>
#include<string>
using namespace std;
class DataReader {
	private:
	ifstream in;
public:
	DataReader(const string &filename);
	virtual ~DataReader();
	void close();
	double readDouble();
	float readFloat();
	int readInteger();
	short readShort();
	bool readBool();
	char readChar();
};

#endif /* DATAREADER_H_ */
