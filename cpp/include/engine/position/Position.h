class Position {
    public:
        short _horizontial;
        short _vertical;

        Position(short, short);
        bool operator== (const Position&);
};
