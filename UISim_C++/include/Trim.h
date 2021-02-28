/*
 * Trim.h
 *
 *  Created on: 2019Äê3ÔÂ13ÈÕ
 *      Author: yichen_shen
 */

#ifndef TRIM_H_
#define TRIM_H_

#include<string>
#include<vector>
using namespace std;

void inline Trim(string &s)
{
    size_t n = s.find_last_not_of(" \r\n\t");
	  if (n != string::npos){
		  s.erase(n + 1, s.size() - n);
	  }
	  n = s.find_first_not_of(" \r\n\t");
	  if (n != string::npos){
		  s.erase(0, n);
	  	  	  	  }
};
bool inline endswith(const string& str, const string& end)
{
    int srclen = str.size();
    int endlen = end.size();
    if(srclen >= endlen)
    {
        string temp = str.substr(srclen - endlen, endlen);
        if(temp == end)
            return true;
    }

    return false;
}
void inline split(const string& src, const string& separator, vector<string>& dest)
{
    string str = src;
    string substring;
    string::size_type start = 0, index;

    do
    {
        index = str.find_first_of(separator,start);
        if (index != string::npos)
        {
            substring = str.substr(start,index-start);
            dest.push_back(substring);
            start = str.find_first_not_of(separator,index);
            if (start == string::npos) return;
        }
    }while(index != string::npos);

    //the last token
    substring = str.substr(start);
    dest.push_back(substring);
}


#endif /* TRIM_H_ */
