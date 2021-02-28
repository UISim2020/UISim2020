/*
 * DataReader.cpp
 *
 *  Created on: 2019Äê3ÔÂ13ÈÕ
 *      Author: yichen_shen
 */

#include "DataReader.h"
#include <cassert>



DataReader::DataReader(const string& filename) {
	in.open(filename.c_str(),ios::in|ios::binary);
	assert(in.is_open());
}




DataReader::~DataReader() {
	in.close();
	// TODO Auto-generated destructor stub
}

void DataReader::close() {
	in.close();
}

double DataReader::readDouble() {
	double rs;
	in.read((char *) &rs,sizeof(rs));
	return rs;
}

float DataReader::readFloat() {
	float rs;
	in.read((char *) &rs,sizeof(rs));
	return rs;
}

int DataReader::readInteger() {
	int rs;
	in.read((char *) &rs,sizeof(rs));
	return rs;
}

short DataReader::readShort() {
	short rs;
	in.read((char *) &rs,sizeof(rs));
	return rs;
}

bool DataReader::readBool() {
	bool rs;
	in.read((char *) &rs,sizeof(rs));
	return rs;
}

char DataReader::readChar() {
	char rs;
	in.read((char *) &rs,sizeof(rs));
	return rs;
}
