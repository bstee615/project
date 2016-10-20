/*
 * loadsave.cpp
 */

#include <fstream>
#include "loadsave.h"
#include "object.h"

LoadSave* LoadSave::loadsave = NULL;

LoadSave& LoadSave::instance()
{
	if (loadsave == NULL)
		loadsave = new LoadSave();
	return *loadsave;
}

// loads a save state and configures objects
void LoadSave::load(string filename)
{
	ifstream file(filename);
	if (file.is_open())
	{
		// read lines and configure objects
		string line = "";
		while (getline(file, line))
		{
			// -- something like this --
//			 Object* obj(line); -- we should let objects have a constructor that takes a string,
//									so we can pass the string in and set up the object
//									should be a factory thing that returns the correct subclass
//			 [the world].objects().add(obj);
		}
		file.close();
	}
}

// reads object data and saves a save state file
void LoadSave::save(string filename)
{
	ofstream file(filename);
	if (file.is_open())
	{
		// write lines from Object.save() method
//		for (Object* obj : [the world].objects())
//		{
//			file << obj.save() << endl; -- Object::save() method should return a string, a line for the file
//		}
		file.close();
	}
}

void LoadSave::teardown()
{
	delete loadsave;
}
