#include <algorithm>
#include <map>
#include "player.cpp"

class Game {
public:
    Game(std::vector<std::string> names) {
        std::cout << "Game started" << std::endl;
        for(auto name : names) {
            players.push_back(new Player(name));
        }
    }
    ~Game() {
        for(Player* player : players) {
            delete player;
        }
        std::cout << "Game ended" << std::endl;
    }
    void start() {
        while(!isEnd()) {
            for(Player* player : players) {
                if(player->isDead) {
                    delete player;
                    players.erase(std::remove(players.begin(), players.end(), player), players.end());
                }
            }
            set();
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 2);
            int random_number = dis(gen);
            this->targetCard = cardMap[random_number];
            std::cout << "Giving cards" << std::endl;
            for(Player* player : players) {
                player->cards = getCard(cards);
            }
            isFire = false;
            std::cout << "Start" << std::endl;
            std::cout << "Target card: " << targetCard << std::endl;
            while(!isFire) {
                showPlayers();
                if((*it_P)->isDead) {
                    delete *it_P;
                    players.erase(it_P);
                    it_P = players.begin();
                }
                if((*it_P)->justDoIt() == 1) {
                    last();
                    int count = 0;
                    for(char card : (*it_P)->cardOut) {
                        if(card != targetCard && card != 'J') {
                            (*it_P)->fire();
                            this->isFire = true;
                            break;
                        } else count++;
                    }
                    if(count == (*it_P)->cardOut.size() && !isFire) {
                        next();
                        (*it_P)->fire();
                        this->isFire = true;
                    }
                }
                next();
            }
        }
    }
private:
    bool isFire = false;
    char targetCard;
    std::vector<Player*> players;
    std::vector<Player*>::iterator it_P;
    std::vector<char>::iterator it_C;
    void set() {
        this->it_P = players.begin();
        this->it_C = cards.begin();
        makeCards();
    }
    void next() {
        if (it_P == players.end()) {
            it_P = players.begin();
        } else {
            ++it_P;
            if (it_P == players.end()) {
                it_P = players.begin();
            }
        }
    }
    void last() {
        if(it_P == players.begin()) {
            it_P = players.end();
            if (it_P != players.begin()) {
                --it_P;
            }
        } else {
            --it_P;
        }
    }
    void makeCards(){
        this->cards = {'A', 'A', 'A', 'A', 'A', 'A', 'Q', 'Q', 'Q', 'Q', 'Q', 'Q', 'K', 'K', 'K', 'K', 'K', 'K', 'J', 'J'};
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }
    std::vector<char> cards;
    std::vector<char> getCard(std::vector<char>& cards) {
        std::vector<char>::iterator temp = cards.begin();
        std::vector<char> card5; 
        for(int i = 0; i < 5; i++) {
            char card = *temp;
            card5.push_back(card);
            cards.erase(temp);
        }
        return card5;
    }
    bool isEnd(){
        if (players.size() == 1) {
            std::cout << "Winner: " << players[0]->name << std::endl;
            return true;
        }
        return false;
    }
    std::map<int, char> cardMap = {{0, 'A'},
                                   {1, 'Q'},
                                   {2, 'K'},
                                   {3, 'J'}};
    void showPlayers() {
        std::cout << "Target: " << targetCard << std::endl;
        for(Player* player : players) {
            player->show();
            std::cout << std::endl;
        }
    }
};