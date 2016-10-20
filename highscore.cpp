#include "highscore.h"

		

	//read in the high scores numbers and users from a file into two vectors
	//or exits if there is no file with the specified name
	void HighScore::LoadScore () {
			string name;
			int score;
			ifstream file;
			file.open ("highscores.txt");
		
		if (file.is_open()) {
			while (file >> name >> score) {
				scores.push_back(score);
				names.push_back(name);
			}
		} else {
			cout << "The file couldn't be opened" << endl;
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
	void HighScore::SaveScores() {
		ofstream file;
		file.open ("highscores.txt");
			if (file.is_open()) {
				for (int i = 0; i < 10; i++) {
					file << names.at(i)  <<" " << scores.at(i) << endl;
				}
		} else {
			cout << "The file couldn't be opened" << endl;
		}
		file.close();
	}
	

	void HighScore::UnitTests() {
			//unit tests
			HighScore h;
			h.LoadScore();
			assert(h.getScore(0) == 1200);
			assert(h.getName(0) == "Jill");
			h.NewHighScore("Joe", 500);
			assert(h.getScore(5) == 500);
			assert(h.getName(5) == "Joe");
			h.SaveScores();
			
	}