#ifndef Game_H
#define Game_H


class Game
{
private:
	sf::RenderWindow window_;
	void play_story_();
	void play_coop_();
	void play_versus_();
	void move_player_();
public:
	void play();
};


#endif // !Game_H

