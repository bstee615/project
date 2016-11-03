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
    void HighScore::LoadScore () {
			string name;
			int score;
            fstream file;
            file.open("highscores.txt");
		
		if (file.is_open()) {
			while (file >> name >> score) {
				scores.push_back(score);
				names.push_back(name);
			}
           file.close();
           return;
		} else {
           fstream fs("highscores.txt",ios::out);
           for (int i = 0; i < 10; i++) {
               fs << "none 0" << endl;
           }
           fs.close();
           HighScore::instance().LoadScore();
           return;
		}
		

	}
	
	//saves the high score of the current user to the vectors using the
	//specified <string> and <score>
    int HighScore::NewHighScore(int score) {
		
        for (int i = 9; i >= 0; i--) {
            if (scores.at(i) > score) {
                scores.insert(scores.begin() + i, score);
				scores.pop_back();
                return i;
			}
				
		}
        return 0;
	}
	
    void HighScore::NewHighScoreName(string name, int placeInVector){
        names.insert(names.begin() + placeInVector, name);
        names.pop_back();
    }

	//writes the scores and names in the vector to the file
	void HighScore::SaveScores(string filename) {
		ofstream file;
        file.open (filename);
			if (file.is_open()) {
				for (int i = 0; i < 10; i++) {
					file << names.at(i)  <<" " << scores.at(i) << endl;
				}
		} else {
            cout << "The file couldn't be created!" << endl;
		}
		file.close();
	}
	

   /* void HighScore::UnitTests() {
		
			//unit tests
            HighScore::instance().LoadScore();
            assert(HighScore::instance().getScore(0) == 0);
            assert(HighScore::instance().getName(0) == "none");
				
            int i = HighScore::instance().NewHighScore("Joe", 1);
            assert(i == 5);
            assert(HighScore::instance().getScore(0) == 1);
            assert(HighScore::instance().getName(0) == "Joe");
			
            assert(HighScore::instance().getScore(9) == 0);
            assert(HighScore::instance().getName(9) == "none");
			
            HighScore::instance().SaveScores("createnewfile.txt");
            HighScore::instance().SaveScores("highscores.txt");
					
	}
    */
	void HighScore::teardown() {
		delete instance_;
	}
