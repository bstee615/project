
#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>

#include "object.h"
#include "item.h"
#include "collectible.h"
#include "coin.h"
#include "movingplatform.h"
#include "player.h"
#include "platform.h"
#include "enemy.h"
#include "playingscreen.h"
#include "endgameobject.h"

using namespace std;

class World {
	vector<Object*> objects;
	Player* player;
    EndGameObject* endGame;
	vector<Enemy*> enemies;
    PlayingScreen* screen;

	// singleton instance
	static World world;

	// singleton: private ctors
	World() {}
	World(const World& that) = delete;  // don't allow copying

	int score;
        int seconds;

public:
	Object *createObject(const string& type);

	// adds <obj> to objects in world
	void add(Object *obj) {
		auto it = objects.begin();
        for (; it != objects.end(); ++it) {
			if (obj->getId() < (*it)->getId()) {
				objects.insert(it, obj);
				break;
			}
		}
		if (it == objects.end()) {
			objects.push_back(obj);
		}
	}
    void addEnemy(Enemy* en)
    {
        auto it = enemies.begin();
        for (; it != enemies.end(); ++it) {
            if (en->getId() < (*it)->getId()) {
                enemies.insert(it, en);
                break;
            }
        }
        if (it == enemies.end()) {
            enemies.push_back(en);
        }
    }

	// returns object with <id>, or NULL if none
	Object *getById(int id);

	vector<Object*>& getObjects() { return objects; }
	vector<Enemy*>& getEnemies() { return enemies; }
	Player* getPlayer() { return player; }
        EndGameObject * getEndGame() { return endGame; }
	void setPlayer(Player* initPlayer) { player = initPlayer;}
        void setEndGame(EndGameObject* newEndGameObject) { endGame = newEndGameObject; }
       void setSeconds(int initSeconds) { seconds = initSeconds; }
       int getSeconds() { return seconds; }


	// Removes object with <id> from objects and returns it, or returns NULL if not found
	Object *destroy(int id);

	// Resets world
	void reset();

	// Destroy objects
	~World();

	// Get singleton
	static World& instance() { return world; }

	PlayingScreen* getScreen() {return screen;}
	void setScreen(PlayingScreen* scr) {screen = scr;}

	int getScore() {return score;}
	void incScore(int addAmount) {score += addAmount; }
	void setScore(int newAmount) {score = newAmount; }
};

#endif // WORLD_H
