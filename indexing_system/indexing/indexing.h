#ifndef INDEXING_H
#define INDEXING_H

#include <string>
#include <unordered_map>
#include <forward_list>
#include <vector>
#include "sha256.h"
using namespace std;


class Indexing
{
protected:
	int k; // number of hash functions
	vector<unordered_map<string, forward_list<string>>> hfs; // vector of hash functions

public:
	Indexing();
	Indexing(int);
	~Indexing();
	
	void add_record(int n, string record, string mh_val);
	vector<string> list_records(int n, string mh_val);
};

#endif
