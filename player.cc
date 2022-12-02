#include "player.h"
#include <string>

using namespace std;

Player::Player(Colour colour, int score) : colour{colour}, score{score} {}
    
Colour Player::getColour() {
    return colour;
}

int Player::getScore() {
    return score;
}

void Player::updateScore() {
    ++score;
}

void Player::resetScore() {
    score = 0;
}
Player::~Player() {}
