class SnakeGame;
class Command
{
    public:
        Command(SnakeGame *game): game(game) {}
        virtual bool execute() = 0;
        virtual void undo() = 0;
        virtual ~Command() = default;
    protected:
        SnakeGame *game;
};

class ChangeDirCommand : public Command
{
    public:
        ChangeDirCommand(SnakeGame *game, Coord2D dir);
        bool execute();
        void undo();
        ~ChangeDirCommand();
    private:
        Coord2D dir;
        Coord2D originDir;
};

class MoveCommand : public Command
{
    public:
        MoveCommand(SnakeGame *game);
        bool execute();
        void undo();
        ~MoveCommand();
    private:
        std::stack< std::pair<Coord2D, int> > undo_queue;
};

class CreateFoodCommand: public Command
{
    public:
        CreateFoodCommand(SnakeGame * game);
        bool execute();
        void undo();
        ~CreateFoodCommand();
    private:
        Coord2D foodPos;
};


