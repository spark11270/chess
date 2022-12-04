#ifndef MOVETYPE_H
#define MOVETYPE_H

enum class MoveType {
    Normal = 0,
    Capture,
    EnPassant,
    Castling,
    Promotion
};

#endif
