/*
 * loadsave.cpp
 */

#include <QFile>
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
void LoadSave::load(QString filename)
{
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		// read lines and configure objects
		QTextStream in(&file);
		while (!in.atEnd())
		{
			QString line = in.readLine();
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
void LoadSave::save(QString filename)
{
	QFile file(filename);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream out(&file);
		// write lines from Object.save() method
//		for (Object* obj : [the world].objects())
//		{
//			out << obj.save() << "\n"; -- Object::save() method should return a string, a line for the file
//		}
		file.close();
	}
}

void LoadSave::teardown()
{
	delete loadsave;
}
