#include "word_and_tile.h"

// -- the game board --
class board{
public:
	board(){}
	board(int n_rows, int n_cols);
	bool set_word(std::string n_word, sf::Vector2i start, sf::Vector2i end, sf::Image* &n_img);
	void print_words(sf::RenderWindow* &screen);

private:
	int rows, cols;
	//contains references to all of the words on the board
	std::vector <word*> words;
	//contains all of the across words
	std::vector<word> across[20];
	//contains all of the down words
	std::vector <word> down[20];
};

// -- prints all of the words on the board --
void board::print_words(sf::RenderWindow* &screen){
	for(unsigned int i=0; i<words.size(); i++){
		words[i]->print_word(screen);
	}
}

// -- board constructor --
board::board(int n_rows, int n_cols){
	rows = n_rows;
	cols = n_cols;
}

// -- places a word on the board --
bool board::set_word(std::string n_word, sf::Vector2i start, sf::Vector2i end, sf::Image* &n_img){
	//we're setting a word that spans across the board
	if(start.x == end.x){
		//check for same-row collisions
		for(unsigned int i=0; i<across[start.x].size(); i++){
			if(across[start.x][i].get_start().y < start.y-1 && across[start.x][i].get_end().y >= start.y-1)
				return false;
			if(across[start.x][i].get_start().y < end.y+1 && across[start.x][i].get_end().y >= end.y+1)
				return false;
		}
		//check to see that the intersections are alright
		int counter=0;
		for(unsigned int i=start.y; i<=end.y; i++){
			for(unsigned int k=0; k<down[i].size(); k++){
				char temp = down[i][k].get_tile(sf::Vector2f(start.x, i));
				if(temp!='0'&&temp!=n_word[counter])
					return false;
			}
			counter++;
		}
		//we're free to set this word
		word new_word(start, end, n_word, n_img);
		across[start.x].push_back(new_word);
		words.push_back(&across[start.x][across[start.x].size()-1]);
	}
	//we're setting a word that goes down
	else{
		//check for same-column collisions
		for(unsigned int i=0; i<down[start.y].size(); i++){
			if(down[start.y][i].get_start().x < start.y-1 && down[start.y][i].get_end().y >= start.y-1)
				return false;
			if(down[start.y][i].get_start().x < end.x+1 && down[start.y][i].get_end().x >= end.x+1)
				return false;
		}
		//check to see that the intersections are alright
		int counter=0;
		for(unsigned int i=start.x; i<=end.x; i++){
			for(unsigned int k=0; k<across[i].size(); k++){
				char temp = across[i][k].get_tile(sf::Vector2f(i, start.y));
				if(temp!='0'&&temp!=n_word[counter])
					return false;
			}
			counter++;
		}
		//we're free to set this word
		word new_word(start, end, n_word, n_img);
		down[start.y].push_back(new_word);
		words.push_back(&down[start.y][down[start.y].size()-1]);
	}
	return true;
}
