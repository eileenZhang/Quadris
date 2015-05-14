#ifndef __SCORE_H__
#define __SCORE_H__

class Score{
	int highScore;
	int score;
	public:
	Score();
	void add(int n);
	void display();
	void reset();
	int getHighScore();
	int getScore();
};

#endif
