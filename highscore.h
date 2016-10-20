#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

class HighScore {
private:
    vector<int> scores;
    vector <string> names;
public: 
	void LoadScore();
	void NewHighScore(string name, int score);
	void SaveScores();
	int getScore(int i) { return scores.at(i); };
	string getName(int i) {return names.at(i); };
        void UnitTests();
};

#endif // HIGHSCORE_H
