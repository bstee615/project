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

	// loads a save state and configures objects
	void load(string filename);

	// reads object data and saves a save state file
	void save(string filename);

	static void teardown();
};

#endif // LOADSAVE_H
