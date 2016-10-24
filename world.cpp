
#include <fstream>
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
			items.push_back(toSplit.substr(oldPos));
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
    objects.clear();
    Object::resetNextId();
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
	else if (type.find("mo") == 0)
		return new MovingPlatform;
	else if (type.find("play") == 0)
		return new Player;
	else if (type.find("plat") == 0)
		return new Platform;
	else
		return NULL;
}

// Load level stored in <filename>
void World::loadLevel(string filename)
{
	ifstream file(filename);
	if (file.is_open())
	{
		// read lines and configure objects
		string line = "";
		size_t valid = 0;

		// not used yet -->
		getline(file, line);
		int time = stoi(line);
		getline(file, line);
		vector<string> levelDim = split(line, ",");
		int levelWidth = stoi(levelDim.at(0));
		int levelHeight = stoi(levelDim.at(1));
		getline(file, line);
		vector<string> screenCoord = split(line, ",");
		int screenX = stoi(screenCoord.at(0));
		int screenY = stoi(screenCoord.at(1));
		getline(file, line);
		// --> end not used yet

		// player
		vector<string> playerCoord = split(line, ",");
		int pX = stoi(playerCoord.at(0));
		int pY = stoi(playerCoord.at(1));
		Player* player = new Player(pX, pY, 25, 48, ":/images/maincharacter/maincharacterstand.png");
		World::instance().add(player);

		while (getline(file, line))
		{
			vector<string> params = split(line, ",");
			Object* obj = World::instance().createObject(params.at(0));
			Platform* plat = dynamic_cast<Platform*>(obj);
			if (plat != NULL)
			{
				// get object properties
				valid = 0;
				int x = stoi(params.at(1), &valid);
				if (valid != params.at(1).length())
				{
					file.close();
					throw invalid_argument(filename + " is not configured properly (contains illegal int value)");
				}
				valid = 0;
				int y = stoi(params.at(2), &valid);
				if (valid != params.at(2).length())
				{
					file.close();
					throw invalid_argument(filename + " is not configured properly (contains illegal int value)");
				}
				valid = 0;
				int width = stoi(params.at(3), &valid);
				if (valid != params.at(3).length())
				{
					file.close();
					throw invalid_argument(filename + " is not configured properly (contains illegal int value)");
				}
				valid = 0;
				int height = stoi(params.at(4), &valid);
				if (valid != params.at(4).length())
				{
					file.close();
					throw invalid_argument(filename + " is not configured properly (contains illegal int value)");
				}

				// set up platform
				plat->setX(x);
				plat->setY(y);
				plat->setWidth(width);
				plat->setHeight(height);
				World::instance().add(plat);

				continue;
			}
		}
		file.close();
	}
	else
	{
		throw runtime_error("Failure to open level file");
	}
}
