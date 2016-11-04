/*
 * loadsave.cpp
 */

#include "world.h"
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
    World::instance().reset();
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		// read lines and configure objects
		QString line = "";
		QTextStream in(&file);

		line = in.readLine();
		QList<QString> timeData = line.split(",");

		World::instance().setStartSeconds(timeData.at(0).toInt());
		World::instance().setSeconds(timeData.at(1).toInt());
		// set up screen object
		line = in.readLine();
		QList<QString> levelDim = line.split(",");
		line = in.readLine();
		QList<QString> screenCoord = line.split(",");
		World::instance().setScreen(new PlayingScreen(
										screenCoord.at(0).toInt(),
										screenCoord.at(1).toInt(),
										0, // don't know the dimensions of the screen here
										0, // will set that in mainwidget.cpp
										levelDim.at(0).toInt(),
										levelDim.at(1).toInt()));

		// player
		Player* player = new Player();
		player->load(in.readLine());
        World::instance().setPlayer(player);

		World::instance().setScore(0);

		// loop to get platforms and other objects
		size_t numObjs = 0;
		loadObjects(in, numObjs);

		if (World::instance().getObjects().size() != numObjs)
			throw runtime_error("The program did not load all of the objects!");

		file.close();
	}
	else
	{
		throw runtime_error("Failure to open level file");
	}
}

// configures objects from a file <in>
// called at beginning of series of objects in a save file
void LoadSave::loadObjects(QTextStream& in, size_t& num)
{
	num = 0;
	QString line = "";
	Object* obj = NULL;
	while (!in.atEnd())
	{
		line = in.readLine();
		obj = World::instance().createObject(line.split(",").at(0).toStdString());
		if (obj != NULL)
		{
			obj->load(line);
            obj->setVisibility(true);
            World::instance().add(obj);
			num++;
		}
	}
}

// reads object data and saves a save state file
void LoadSave::save(QString filename)
{
	QFile file(filename);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream out(&file);
		out << World::instance().getStartSeconds() << "," << World::instance().getSeconds() << "\n";
		PlayingScreen* scr = World::instance().getScreen();
		out << scr->getLevelWidth() << "," << scr->getLevelHeight() << "\n";
		out << scr->getX() << "," << scr->getY() << "\n";
		// write lines from Object.save() method
		size_t numObjects = 1;
		out << World::instance().getPlayer()->save() << "\n";
		for (Object* obj : World::instance().getObjects())
		{
			out << obj->save() << "\n";
			numObjects++;
		}
		if (numObjects != World::instance().getObjects().size())
			throw runtime_error("The program did not save all of the objects!");
		file.close();
	}
	if (!file.exists())
		throw runtime_error("The save file was not created successfully!");
}

void LoadSave::teardown()
{
	delete loadsave;
}
