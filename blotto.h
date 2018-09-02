#ifndef GUARD_BLOTTO_H
#define GUARD_BLOTTO_H

#include <vector>
#include <ctime>

class Player {
    std::vector<int> troop_deployment;
    double total_score;

public:
    const std::vector<int>& get_troops() const {return troop_deployment;}
    double get_score() const {return total_score;}
    void change_score(int n) {total_score += n;}
    // void initialise();
    void zero() {total_score = 0;}

//    Player();
    Player(int n = 100);
    Player(std::vector<int> vec) : troop_deployment(vec), total_score(0)           
    {}
};

// make_war works but is no longer needed so is commented out
// void make_war(Player&, Player&);

void make_one_sided_war(Player&, const Player&);

bool compare(Player&, Player&);

std::vector<Player> play_recursive_round_robin(const std::vector<Player>&, int);


#endif

// Below here is code that I deleted but may want











/*
Player::Player(): total_score(0)
{
    int troops_added_so_far = 0;
    while (troops_added_so_far < 101 && troop_deployment.size() < 11)
        troop_deployment.push_back(rand() % 100);
    while (troop_deployment.size() < 11)
        troop_deployment.push_back(0);    
}
*/