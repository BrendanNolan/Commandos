#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
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
    int troops_added_so_far = 0;

    while (troops_added_so_far <= n && troop_deployment.size() < 9)
    {
        int to_add = gen_unif_rv(n - troops_added_so_far);
        troop_deployment.push_back(to_add);
        troops_added_so_far += to_add;
    }

    troop_deployment.push_back(n - troops_added_so_far);

    std::sort(troop_deployment.begin(), troop_deployment.end());

    std::random_shuffle(troop_deployment.begin(), troop_deployment.begin() + 4);
    std::random_shuffle(troop_deployment.begin() + 4, troop_deployment.end());
}



bool compare(const Player& a, const Player& b)
{
    return a.get_score() > b.get_score();
}



void make_one_sided_war(Player& a, const Player& b)
{
    std::vector<int>::const_iterator iter_a = a.get_troops().begin();
    std::vector<int>::const_iterator iter_b = b.get_troops().begin();
    std::vector<int>::const_iterator iter_a_end = a.get_troops().end();

    int counter = 1;
    while (iter_a != iter_a_end)
    {
        if (*iter_a > *iter_b)
            a.change_score(counter);

        ++iter_a;
        ++iter_b;
        ++counter;
    }

    return;
}



void play_all(Player& contestant, const std::vector<Player>& field)
{
    for (const_iter i = field.begin(); i != field.end(); ++i)
                make_one_sided_war(contestant, *i);

    return;                
}



std::vector<Player> play_recursive_round_robin(const std::vector<Player>& vec, 
                                               int num_iterations)
{
    if (num_iterations == 0)
    {  
        return vec;
    }
    else
    {    
        if (vec.size() < 2)
            throw std::domain_error("need at least two Player"
                                    " objects for round robin");
        
        std::vector<Player> ret;
        ret.clear(); // for safety, not strictly necessary

        for (const_iter j = vec.begin(); j != vec.end(); ++j)
        {
            Player plyr = *j;
            plyr.zero();

            play_all(plyr, vec);

            ret.push_back(plyr);
        }    
        
        sort(ret.begin(), ret.end(), compare);

        // remove the latter (lowest-scoring) half of the Players in ret
        sz_tp ret_size = ret.size(); 
        for (sz_tp s = 0; s < ret_size / 2; ++s)
            ret.pop_back();

        return play_recursive_round_robin(ret, num_iterations - 1);
    }    
}