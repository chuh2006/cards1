#include "game.cpp"

int main() {
    std::vector<std::string> names(4);
    int i = 0;
    for(std::string &name : names) {
        std::cout << "Enter a name of players" << "[" << i + 1 << "/4]" << ": ";
        std::cin >> name;
        i++;
    }
    std::cout << "Players: " << names << std::endl;
    Game *game = new Game(names);
    game->start();
    delete game;
    return 0;
}