
class Carry {
    private:
        bool c0, a, b, c;
    public:
        Carry(bool c0, bool a, bool b);
        void executeCarry();
        bool readCarry();
};
