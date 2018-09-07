#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "commando.h"



typedef std::vector<Player>::iterator iter;
typedef std::vector<Player>::const_iterator const_iter;
typedef std::vector<Player>::size_type sz_tp;



int gen_unif_rv(int n)
{
    const int bin_capacity = RAND_MAX / n;
    int rn;
    
    do rn = rand() / bin_capacity;
    while(rn > n);

    return rn;
}



Player::Player(int n): total_score(0)
{
    // Make commando_deployment a random vector of 10 integers which sum to n
    int commandos_added_so_far = 0;

    while (commandos_added_so_far <= n && commando_deployment.size() < 9)
    {
        int to_add = gen_unif_rv(n - commandos_added_so_far);
        commando_deployment.push_back(to_add);
        commandos_added_so_far += to_add;
    }

    commando_deployment.push_back(n - commandos_added_so_far);


    // sort commando_deployment so that its elements appear in increasing order
    std::sort(commando_deployment.begin(), commando_deployment.end());

    // shuffle the first four elements of commando_deployment
    std::random_shuffle(commando_deployment.begin(), 
                        commando_deployment.begin() + 4);
    // shuffle the last six elements of commando_deployment                    
    std::random_shuffle(commando_deployment.begin() + 4, 
                        commando_deployment.end());
}



bool compare(const Player& a, const Player& b)
{
    return a.get_score() > b.get_score();
}


void make_battle(Player& a, Player& b)
{
    std::vector<int>::const_iterator iter_a = a.get_commandos().begin();
    std::vector<int>::const_iterator iter_b = b.get_commandos().begin();
    std::vector<int>::const_iterator iter_a_end = a.get_commandos().end();

    int town_value = 1;
    while (iter_a != iter_a_end)
    {
        if (*iter_a > *iter_b)
            a.increase_score(town_value);
        else if (*iter_a < *iter_b)
            b.increase_score(town_value);    

        ++iter_a;
        ++iter_b;
        ++town_value;
    }

    return;
}

void make_one_sided_battle(Player& a, const Player& b)
{
    std::vector<int>::const_iterator iter_a = a.get_commandos().begin();
    std::vector<int>::const_iterator iter_b = b.get_commandos().begin();
    std::vector<int>::const_iterator iter_a_end = a.get_commandos().end();

    int town_value = 1;
    while (iter_a != iter_a_end)
    {
        if (*iter_a > *iter_b)
            a.increase_score(town_value);

        ++iter_a;
        ++iter_b;
        ++town_value;
    }

    return;
}

void battle_all(Player& contestant, const std::vector<Player>& field)
{
    for (const_iter i = field.begin(); i != field.end(); ++i)
        make_one_sided_battle(contestant, *i);

    return;                
}




// It might be best to have this function 
// return a std::vector<Player> instead of a std::vector<Player>&
std::vector<Player>& recursive_play_round_robin(
    std::vector<Player>& vec, int num_rounds)
{
    if (num_rounds == 0)
            return vec;
    else 
    {
        // zero the total_scores of the members of vec
        for (iter i = vec.begin(); i != vec.end(); ++i)
            i->zero();

        play_round_robin(vec.begin(), vec.end(), make_battle);
        sort(vec.begin(), vec.end(), compare);
        // remove the latter (lowest-scoring) half of the Players in vec
        sz_tp vec_size = vec.size(); 
        for (sz_tp s = 0; s < vec_size / 2; ++s)
            vec.pop_back();

        return recursive_play_round_robin(vec, num_rounds - 1);    
    }
}

