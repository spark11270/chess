#include "player.h"
#include <string>

using namespace std;

Player::Player(std::string name, Colour colour, int score) : name{name}, colour{colour}, score{score} {}
    
string Player::getName() {
    return name;
}

Colour Player::getColour() {
    return colour;
}

int Player::getScore() {
    return score;
}

Player::~Player() {}
