#ifndef __POSITION_H__
#define __POSITION_H__

// FINISHED & TESTED JUL. 20 -- MITCHELL M. GRESHAM

class Position {
    public:
        short _horizontial;
        short _vertical;

        Position(short, short);
        Position();
        bool operator== (const Position&);
};

#endif // __POSITION_H__