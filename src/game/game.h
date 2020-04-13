#include <string>

class Game {
    public:
        Game(std::string name);
        void SayMyName();
        virtual ~Game();
    private:
        std::string name;
};