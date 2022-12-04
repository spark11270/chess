#include "move.h"
#include "piece.h"

using namespace std;

Move::Move(shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic) : 
    captured{nullptr}, moving{moving}, from{from}, to{to}, tactic{tactic} {}

Move::Move(std::shared_ptr<Piece> captured, std::shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic) :
    captured{captured}, moving{moving}, from{from}, to{to}, tactic{tactic} {}

string Move::getMoves() {
    if (captured != nullptr) {
        PieceName name = captured->getType();
        switch(name) {
            case PieceName::Bishop :
                return "Bishop";
                break;
            case PieceName::Queen :
                return "Queen";
                break;
            case PieceName::Pawn :
                return "Pawn";
                break;
            case PieceName::Rook :
                return "Rook";
                break;
            case PieceName::Knight :
                return "Knight";
                break;
            case PieceName::King :
                return "King";
                break;
        }
    } else {
        return "None";
    }
}
