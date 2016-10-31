#include <QFile>
#include "world.h"

World World::world;

// takes a string <toSplit> and returns a vector of strings delimited by a sequence of characters <delim>
vector<string> split(string toSplit, string delim)
{
	size_t pos = 0;
	size_t oldPos = 0;
	pos = toSplit.find(delim, pos);
	vector<string> items;
	if (pos == string::npos)
	{
		// delimiter not found, return vector with toSplit as the only item
		items.push_back(toSplit);
		return items;
	}
	while (true)
	{
		items.push_back(toSplit.substr(oldPos, pos - oldPos));
		pos += delim.length();
		oldPos = pos;
		pos = toSplit.find(delim, pos);
		if (pos == string::npos)
		{
			items.push_back(toSplit.substr(oldPos, toSplit.find_last_not_of("\n") - oldPos));
			break;
		}
	}
	return items;
}

// returns object with <id>, or NULL if none
Object *World::getById(int id) {
    for (size_t i = 0; i < objects.size(); ++i) {
        Object *obj = objects.at(i);
        if (obj->getId() == id) {
            return obj;
        }
    }
    return NULL;
}

//erases the object with the specified <id> pointer from the world vector, and returns the
//pointer if it is found, or nullptr if not
Object *World::destroy(int id) {
    Object *obj = NULL;

    auto iter = objects.begin();
    while (iter != objects.end() && (*iter)->getId() != id) {
        ++iter;
    }

    if (iter != objects.end()) {
        // found it
        obj = *iter;
        objects.erase(iter);
    }
    return obj;
}

//Resets the world to, both by deleting memory and erasing the pointers
//to that memory
void World::reset() {
	
    for (size_t i = 0; i < objects.size(); ++i) {
        delete objects.at(i);
    }
    delete player;
    score = 0;
    seconds = 0;
    objects.clear();
    Object::resetNextId();
	delete screen;
}

//World destructor
World::~World() {
    reset();
}

// factory: creates and returns an Object or derived class, determined by
// <type>. Returns NULL if <type> is not recognized.
Object *World::createObject(const string& type) {
	if (type.find("ob") == 0)
		return new Object;
	else if (type.find("it") == 0)
		return new Item;
	else if (type.find("col") == 0)
		return new Collectible;
	else if (type.find("coi") == 0)
		return new Coin;
	else if (type.find("play") == 0)
		return new Player;
	else if (type.find("plat") == 0)
		return new Platform;
    else if (type.find("en") == 0)
        return new Enemy;
    else if (type.find("flyingen") == 0)
        return new FlyingEnemy;
    else if (type.find("ob") == 0)
        return new Object;
	else
		return NULL;
}
/* <<<<<<< HEAD

// Load level stored in <filename>
void World::loadLevel(QString filename)
{
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		// read lines and configure objects
		QString line = "";
		QTextStream in(&file);

		// not used yet -->
		line = in.readLine();
		int time = line.toInt();
		// --> end not used yet

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
		line = in.readLine();
		QList<QString> playerCoord = line.split(",");
        int pX = playerCoord.at(1).toInt();
        int pY = playerCoord.at(2).toInt();
		Player* player = new Player(pX, pY, 25, 48, ":/images/maincharacter/stand.png");
		World::instance().setPlayer(player);
        EndGameObject* endGame = new EndGameObject(2400, 220, 50, 50, ":/images/flag.png");
        World::instance().setEndGame(endGame);

        // loop to get platforms and other objects.
		loadObjects(in);
		file.close();
	}
	else
	{
		throw runtime_error("Failure to open level file");
	}
}

// loop to setup platforms, enemies, and coins
void World::loadObjects(QTextStream& in)
{
	QString line = "";
	Object* obj = NULL;
	while (!in.atEnd())
	{
		line = in.readLine();
		obj = World::instance().createObject(line.split(",").at(0).toStdString());
		if (obj != NULL)
		{
			obj->load(line);
			World::instance().add(obj);
			obj->setVisibility(true);
		}
    }
}
======= 
>>>>>>> de38cbec2d748ea2ce164e5f02f7136a922547e3 */
