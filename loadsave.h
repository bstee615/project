/*
 * loadsave.h
 */

#ifndef LOADSAVE_H
#define LOADSAVE_H

#include <string>
#include <vector>

using namespace std;

class LoadSave
{
	static LoadSave* loadsave;
	LoadSave() {}

public:
	static LoadSave& instance();

	void load(string filename);

	void save(string filename);
};

#endif // LOADSAVE_H
