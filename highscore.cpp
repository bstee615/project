	#include "highscore.h"

	HighScore* HighScore::instance_ =  nullptr;
	
	HighScore& HighScore::instance() {
		if (instance_== nullptr) {
			instance_ = new HighScore();
		}
		return *instance_;
		
	}
	//read in the high scores numbers and users from a file into two vectors
	//or exits if there is no file with the specified name
	void HighScore::LoadScore (string filename) {
			string name;
			int score;
			ifstream file;
			file.open (filename);
		
		if (file.is_open()) {
			while (file >> name >> score) {
				scores.push_back(score);
				names.push_back(name);
			}
		} else {
			throw string ("The file couldn't be opened");
		}
		
		file.close();
	}
	
	//saves the high score of the current user to the vectors using the
	//specified <string> and <score>
	void HighScore::NewHighScore(string name, int score) {
		
		for (int i = 0; i < 10; i++) {
			if (scores.at(i) < score) {
				scores.insert(scores.begin() + i, score);
				names.insert(names.begin() + i, name);
				names.pop_back();
				scores.pop_back();
				return;
			}
				
		}
		
	}
	
	//writes the scores and names in the vector to the file
	void HighScore::SaveScores(string filename) {
		ofstream file;
		file.open ("highscores.txt");
			if (file.is_open()) {
				for (int i = 0; i < 10; i++) {
					file << names.at(i)  <<" " << scores.at(i) << endl;
				}
		} else {
			throw string ("The file couldn't be opened");
		}
		file.close();
	}
	

	void HighScore::UnitTests() {
		
			//unit tests
			HighScore h;
			try {
			h.LoadScore("thiswon'twork.txt");
			} catch (string& str) {}
			h.LoadScore("highscores.txt");
			assert(h.getScore(0) == 1200);
			assert(h.getName(0) == "Jill");
		
			assert(h.getScore(9) == 50);
			assert(h.getName(9) == "Billy");
		
			h.NewHighScore("Joe", 500);
		
			assert(h.getScore(5) == 500);
			assert(h.getName(5) == "Joe");
			
			assert(h.getScore(9) == 100);
			assert(h.getName(9) == "Jake");
			
			h.SaveScores("thisalsowon'twork.txt");
			h.SaveScores("highscores.txt");
					
	}
	
	void HighScore::teardown() {
		delete instance_;
	}
