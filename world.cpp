#include "world.h"


World World::world;

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
