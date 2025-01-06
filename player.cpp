#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "vectorio.cpp"

class Player {
public:
    Player(std::string name) : name(name) {
        std::cout << "Player " << name << " created" << std::endl;
        start();
    }
    ~Player() {
        std::cout << "Player " << name << " died" << std::endl;
    }
    std::string name;
    void start(){
        this->isDead = false;
        for(int i = 0; i < 6; i++) {
            this->magazine.push_back(0);
        }
        std::random_device rd1;
        std::mt19937 gen1(rd1());
        std::uniform_int_distribution<> dis1(0, 5);
        this->magazine[dis1(gen1)] = 1;
        this->bullets = {'?', '?', '?', '?', '?', '?'};
        this->it_M = this->magazine.begin();
        this->it_B = this->bullets.begin();
    }
    bool isDead;
    std::vector<char> cardOut;
    std::vector<char> cards;
    int justDoIt() {
        if(!this->isDead) {
            this->cardOut.clear();
            menu0();
            int choice;
            std::cin >> choice;
            if(choice == 1) {
                putCard();
                return 0;
            } else if(choice == 2) {
                return 1;
            } else {
                std::cout << "Invalid input" << std::endl;
                if(justDoIt() == 0) {
                    return 0;
                } else {
                    return 1;
                }
            }
        }
        return -1;
    }
    void fire() {
        if(!this->isDead) {
            if(isshoot()) {
                std::cout << "Player " << this->name << " is dead" << std::endl;
            }
            std::cout << "Bullets: " << this->bullets << std::endl;
            return;
        }
        std::cout << "Player " << this->name << " is dead" << ", pass" << std::endl;
    }
    void show() {
        std::cout << "Player " << this->name << std::endl;
        std::cout << "Bullets: " << this->bullets << std::endl;
    }
private:
    std::vector<char> bullets;
    std::vector<int> magazine;
    bool isshoot() {
        std::cout << "Player " << this->name << " shoots" << std::endl;
        if(*it_M == 1) {
            *it_B = 'X';
            this->isDead = true;
            return this->isDead;
        }
        *it_B = 'O';
        it_B++;
        it_M++;
        return this->isDead;
    }
    std::vector<int> giveCard() {
        std::vector<int> temp;
        std::cout << "Enter numbers of cards: ";
        std::cin >> temp;
        if(temp.size() == 0 || temp.size() > 3) {
            std::cout << "Invalid input" << std::endl;
            return giveCard();
        }
        return temp;
    }
    void putCard() {
        menu1();
        std::vector<int> temp = giveCard();
        for(int i = 0; i < temp.size(); i++) {
            this->cardOut.push_back(this->cards[temp[i]]);
        }
        for(int i = 0; i < temp.size(); i++) {
            this->cards.erase(this->cards.begin() + temp[i]);
        }
        std::cout << this->name << " puts cards: " << cardOut << std::endl;
    }
    std::vector<char>::iterator it_B;
    std::vector<int>::iterator it_M;
    void menu0() {
        std::cout << this->name << std::endl;
        std::cout << "1. Put cards" << std::endl;
        std::cout << "2. Liar" << std::endl;
    }
    void menu1() {
        std::cout << this->cards << std::endl;
        std::cout << " ";
        for(int i = 0; i < cards.size(); i++) {
            std::cout << "^  ";
        }
        std::cout << " " << std::endl;
        std::cout << " ";
        for(int i = 0; i < cards.size(); i++) {
            std::cout << i << "  ";
        }
        std::cout << " " << std::endl;
    }

};
