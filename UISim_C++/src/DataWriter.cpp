/*
 * DataWriter.cpp
 *
 *  Created on: 2019Äê3ÔÂ13ÈÕ
 *      Author: yichen_shen
 */

#include "DataWriter.h"

#include <cassert>

DataWriter::DataWriter(const string& filename) {
	out.open(filename.c_str(),ios::out|ios::binary);
	assert(out.is_open());
}

void DataWriter::close() {
	out.close();
}

void DataWriter::writeDouble(const double& v) {

	out.write((char*)&v,sizeof(v));
}

void DataWriter::writeFloat(const float& v) {
	out.write((char*)&v,sizeof(v));
}

void DataWriter::writeInteger(const int& v) {
	out.write((char*)&v,sizeof(v));
}

void DataWriter::writeShort(const short & v) {
	out.write((char*)&v,sizeof(v));
}

void DataWriter::writeBool(const bool& v) {
	out.write((char*)&v,sizeof(v));
}

void DataWriter::writeChar(const char& v) {
	out.write((char*)&v,sizeof(v));
}

void DataWriter::flush() {
	out.flush();
}

DataWriter::~DataWriter() {
	out.close();
}

