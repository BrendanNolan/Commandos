#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "blotto.h"



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
    // Make soldier_deployment a random vector of 10 integers which sum to n
    int soldiers_added_so_far = 0;

    while (soldiers_added_so_far <= n && soldier_deployment.size() < 9)
    {
        int to_add = gen_unif_rv(n - soldiers_added_so_far);
        soldier_deployment.push_back(to_add);
        soldiers_added_so_far += to_add;
    }

    soldier_deployment.push_back(n - soldiers_added_so_far);


    // sort soldier_deployment so that its elements appear in increasing order
    std::sort(soldier_deployment.begin(), soldier_deployment.end());

    // shuffle the first four elements of soldier_deployment
    std::random_shuffle(soldier_deployment.begin(), 
                        soldier_deployment.begin() + 4);
    // shuffle the last six elements of soldier_deployment                    
    std::random_shuffle(soldier_deployment.begin() + 4, 
                        soldier_deployment.end());
}



bool compare(const Player& a, const Player& b)
{
    return a.get_score() > b.get_score();
}


void make_battle(Player& a, Player& b)
{
    std::vector<int>::const_iterator iter_a = a.get_soldiers().begin();
    std::vector<int>::const_iterator iter_b = b.get_soldiers().begin();
    std::vector<int>::const_iterator iter_a_end = a.get_soldiers().end();

    int castle_value = 1;
    while (iter_a != iter_a_end)
    {
        if (*iter_a > *iter_b)
            a.increase_score(castle_value);
        else if (*iter_a < *iter_b)
            b.increase_score(castle_value);    

        ++iter_a;
        ++iter_b;
        ++castle_value;
    }

    return;
}

void make_one_sided_battle(Player& a, const Player& b)
{
    std::vector<int>::const_iterator iter_a = a.get_soldiers().begin();
    std::vector<int>::const_iterator iter_b = b.get_soldiers().begin();
    std::vector<int>::const_iterator iter_a_end = a.get_soldiers().end();

    int castle_value = 1;
    while (iter_a != iter_a_end)
    {
        if (*iter_a > *iter_b)
            a.increase_score(castle_value);

        ++iter_a;
        ++iter_b;
        ++castle_value;
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
std::vector<Player>& recursive_improved_play_round_robin(
    std::vector<Player>& vec, int num_rounds)
{
    if (num_rounds == 0)
            return vec;
    else 
    {
        // zero the total_scores of the members of vec
        for (iter i = vec.begin(); i != vec.end(); ++i)
            i->zero();

        improved_play_round_robin(vec.begin(), vec.end(), make_battle);
        sort(vec.begin(), vec.end(), compare);
        // remove the latter (lowest-scoring) half of the Players in vec
        sz_tp vec_size = vec.size(); 
        for (sz_tp s = 0; s < vec_size / 2; ++s)
            vec.pop_back();

        return recursive_improved_play_round_robin(vec, num_rounds - 1);    
    }
}

// --------------- OBSOLETE FUNCTIONS ---------------------------------

std::vector<Player> play_recursive_round_robin(const std::vector<Player>& vec, 
                                               int num_rounds)
{
    if (num_rounds == 0)  
        return vec;
    else
    {    
        if (vec.size() < 2)
            throw std::domain_error("need at least two Player"
                                    " objects for round robin");
        
        std::vector<Player> ret;
        ret.clear(); // for safety, not strictly necessary

        for (const_iter j = vec.begin(); j != vec.end(); ++j)
        {
            // Declare a Player object called plyr and copy the pointee of j
            // into plyr
            Player plyr = *j;
            // disguard possible previously accumulated score
            plyr.zero();
            // let plyr battle every other Player object and keep track of 
            // the total_score of plyr
            battle_all(plyr, vec);

            ret.push_back(plyr);
        }    
        
        sort(ret.begin(), ret.end(), compare);

        // remove the latter (lowest-scoring) half of the Players in ret
        sz_tp ret_size = ret.size(); 
        for (sz_tp s = 0; s < ret_size / 2; ++s)
            ret.pop_back();

        return play_recursive_round_robin(ret, num_rounds - 1);
    }    
}