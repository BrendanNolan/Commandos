#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

#include "blotto.h"

template <class It>
void iter_print(It a, It b)
{
    for (It i = a; i != b; ++i)
        std::cout << *i << " ";

    std::cout << std::endl;

    return;
}

int main(int argc, char* argv[])
{

    if (argc != 3) 
    {
        throw std::domain_error("Usage ./<file name>"
            " number-of-bots" 
            " number of round-robin rounds");              
    }    

    typedef std::vector<Player>::iterator iter;
    typedef std::vector<Player>::const_iterator const_iter;
    typedef std::vector<Player>::size_type sz_tp;

    sz_tp num_bots = atoi(argv[1]);
    int num_rounds = atoi(argv[2]);

    srand(42);

    std::vector<Player> Player_vec(num_bots);

    std::vector<Player> elite_Player_vec = play_recursive_round_robin(
                                               Player_vec, num_rounds);                                                           

    Player chosen_one = elite_Player_vec[0];
    
    std::cout << "Chosen 100-troop strategy: ";
    iter_print((chosen_one.get_troops()).begin(), 
             (chosen_one.get_troops()).end()); 

    // create a vector which will hold our chosen Players for the 90- and 100-
    // troop scenarios. Initialise them both to hold no troops (they will be 
    // oberwritten anyway). 
    std::vector<Player> unfair_Players(2, Player({ 0, 0, 0, 0, 0, 
                                                   0, 0, 0, 0, 0 }));

    // for the 90- and 110-troop scenarios, test 
    std::vector<int> troop_counts = { 100, 100 };

    for (int i = 0; i < 2; ++i)
    {
        int max_score = 0;
        for (int j = 0; j < 1000; ++j)
        {
            Player plyr(troop_counts[i]);
            play_all(plyr, elite_Player_vec);    

            if (plyr.get_score() > max_score)
            {
                max_score = plyr.get_score();
                unfair_Players[i] = plyr;
            }
        }
    }         

    std::cout << std::endl << "Chosen 90-troop  strategy: ";
    iter_print((unfair_Players[0].get_troops()).begin(),
               (unfair_Players[0].get_troops()).end());
    std::cout << std::endl << "Chosen 110-troop strategy: ";               
    iter_print((unfair_Players[1].get_troops()).begin(),
               (unfair_Players[1].get_troops()).end());

    return 0;
}



/*
    std::cout << "Player_vec.size(): " << Player_vec.size() << std::endl 
              << "elite_Player_vec.size(): " << elite_Player_vec.size() << std::endl;

    Player winner_of_fair_battles = elite_Player_vec[0];          
    Player runner_up_in_fair_battles = elite_Player_vec[1];

    iter_print((winner_of_fair_battles.get_troops()).begin(), 
             (winner_of_fair_battles.get_troops()).end());
    std::cout << winner_of_fair_battles.get_score() << std::endl;         
    iter_print((runner_up_in_fair_battles.get_troops()).begin(), 
             (runner_up_in_fair_battles.get_troops()).end());
    std::cout << runner_up_in_fair_battles.get_score() << std::endl;        
*/
                    /*
int main(int argc, char* argv[])
{
    if (argc != 6)
    {
        throw std::domain_error("Usage ./<file name>"
        " number-of-bots" 
        " desired-score-vs-bots-when-you-have-100-troops"
        " desired-score-vs-bots-when-you-have-90-troops"
        " desired-score-vs-botswhen-you-have-110-troops" 
        " max-number-of-good-Players");
    }

    srand(time(NULL));

    typedef std::vector<Player>::iterator iter;
    typedef std::vector<Player>::const_iterator const_iter;
    typedef std::vector<Player>::size_type svP_sz_tp;

    svP_sz_tp num_bots = atoi(argv[1]);
    double desired_score = atof(argv[2]);
    double desired_score_90 = atof(argv[3]);
    double desired_score_110 = atof(argv[4]);
    svP_sz_tp max_num_good_Players = atoi(argv[5]);


    std::vector<Player> Player_vec(num_bots);

    std::vector<Player> elite_Player_vec = 
        play_recursive_round_robin(PLayer_vec, 2);
                    
    std::vector<Player> good_Player_vec;
    copy(play_recursive_round_robin_robin(Player_vec).begin(), 
        play_recursive_round_robin_robin(Player_vec).begin() + num_bots / 4,
        back_inserter(good_Player_vec));



    std::vector<Player> best_good_Player_vec = 
    play_recursive_round_robin_robin(good_Player_vec, 2);                     

    sort(best_good_Player_vec.begin(), best_good_Player_vec.end(), compare); 

                                             
    Player chosen_Player = best_good_Player_vec[0];  

    std::cout << "The chosen strategy for 100 troops: " << std::endl;
    iter_print((chosen_Player.get_troops()).begin(), 
             (chosen_Player.get_troops()).end());
    std::cout << "had an average score of "
              << chosen_Player.get_score() / (good_Player_vec.size() - 1) 
              // The minus 1 above is for the fact that chosen_Player played one  
              // game against himself
              << " against a selection of " 
              << good_Player_vec.size()
              << " high-perfoming strategies chosen from the "
              << num_bots 
              << " randm bot strategies."
              << std::endl
              << std::endl;


// ----------------------------------------------
    std::vector<int> new_troop_nums = { 90, 110 };
    std::vector<double> new_desired_scores = 
        { desired_score_90, desired_score_110 };
    for (int i = 0; i < 2; ++i)
    {
        while (true)
        {
            Player random_Player(new_troop_nums[i]);
            
            for (iter i = good_Player_vec.begin(); 
                 i != good_Player_vec.end(); ++i)
                make_one_sided_war(random_Player, *i);
        
            if (random_Player.get_score() / 
                max_num_good_Players >= new_desired_scores[i])
            {
                std::cout << "Using similar methods to those above, the "
                             "strategy chosen for when we have "
                          << new_troop_nums[i] << " troops is: " << std::endl;   
                
                iter_print(random_Player.get_troops().begin(), 
                random_Player.get_troops().end());
                
                std::cout << "which scored on average: " 
                        << random_Player.get_score() / 
                            max_num_good_Players
                        << " points."    
                        << std::endl
                        << std::endl;

                break;
            }
        }          
    }
// -----------------------------------------------

                    
    return 0; 
}
                    */

/*
std::cout << Player_vec.size() << std::endl
              << good_Player_vec.size() << std::endl
              << best_good_Player_vec.size() << std::endl;  
*/



/*
The thing to do seems to be:
creata a Player class with two (private) data members (an vector<int> and a 
int to track how successful the Player was) and
an accessor function to give read-only access to that data member. We should 
give the Player class an initialiser function that initialises the vector<int> 
to contain ten random numbers (constrained to sum to exactly 100) and 
initialises the int to 0 (I should note 
in my write-up that there can be no possible advantage to sending fewer than 100 
troops into battle). There should also be a member function called play that 
takes a vector of Players and returns the sum of its own Player's scores of its 
own Player's scores against the other Players. 

We should then create a vector<Player> (or some other container<Player>) that 
contains and initialise it to contain, say, a million, Player objects (which 
will hopefully be initialised immediately in the random fashion stipulated). It 
should then be possible (see the end of the Cherno's function pointer video) to 
pit all the Players against eachother and store each Player's final score in the 
int data member.  
*/

   //    double desired_score_vs_good_Players = atof(argv[4]);


//    std::vector<Player> good_Player_vec;
//    std::vector<Player>::size_type max_num_good_Players = atoi(argv[2]);

//   const_iter pv_beg = Player_vec.begin();
//   const_iter pv_end = Player_vec.end();
    /* Prints good_Player_vec
    for (iter i = good_Player_vec.begin(); i != good_Player_vec.end(); ++i)
    {
        iter_print((i->get_troops()).begin(), (i->get_troops()).end());
    }
    */

/*
    Player proportional_Player({ 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 });
    Player ten_Player({ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 });

    for (iter i = good_Player_vec.begin(); i != good_Player_vec.end(); ++i)
            make_war(proportional_Player, *i);
     
    for (iter i = good_Player_vec.begin(); i != good_Player_vec.end(); ++i)
            make_war(ten_Player, *i);

    std::cout << "(10, 10, 10, 10, 10, 10, 10, 10, 10, 10), " 
                 "when tested against the competent bots, scored on average: " 
              << ten_Player.get_score() /  max_num_good_Players
              << std::endl;

    std::cout << "(1, 3, 5, 7, 9, 11, 13, 15, 17, 19), " 
                 "when tested against the competent bots, scored on average: " 
              << proportional_Player.get_score() /  max_num_good_Players
              << std::endl;


    while (true)
    {
        Player random_Player;
        
        for (iter i = good_Player_vec.begin(); i != good_Player_vec.end(); ++i)
            make_war(random_Player, *i);
    
        if (random_Player.get_score() / 
            max_num_good_Players >= desired_score_vs_good_Players)
        {
            std::cout << "the algorithm's chosen strategy: ";
            
            iter_print(random_Player.get_troops().begin(), 
             random_Player.get_troops().end());
            
            std::cout << std::endl << "scored on average: " 
                      << random_Player.get_score() / 
                         max_num_good_Players
                      << std::endl;

            break;
        }
    }
*/

// Player Alice;
    // Player Carol({ 20, 0, 10, 5, 10, 5, 10, 20, 0, 20 });


//  Checking that the random creation worked.
/*
    std::cout << Player_vec[0].get_troops()[3] << std::endl
              << Player_vec[1].get_troops()[3] << std::endl
              << Player_vec[2].get_troops()[3] << std::endl;
*/

/* Checking that the make_war function works

    make_war(Player_vec[0], Player_vec[1]);
    make_war(Player_vec[0], Player_vec[2]);
    make_war(Player_vec[1], Player_vec[2]);


    std::cout << "Player_vec[0]'s score: " << Player_vec[0].get_score() 
              << std::endl
              << "Player_vec[1]'s score: " << Player_vec[1].get_score() 
              << std::endl
              << "Player_vec[2]'s score: " << Player_vec[2].get_score() 
              << std::endl;
*/
    // make_war(Alice, Carol);

    // std::cout << "Alice's score: " << Alice.get_score() << std::endl
    //          << "Carol's score: " << Carol.get_score() << std::endl;

    // Player proportional({ 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 });

    // Note to self: make a do-while loop that creates a random Player,
    // pits him against a million othe rrandom Players,
    // and goes again as long as his average score is less than 50. 
    // that should give you a good military strategy

    // Player proportional({ 1, 1, 1, 1, 6, 16, 17, 18, 19, 20 });
    // Player rando;

    // It does not matter how we initialise random_Player - it will be 
    // overwritten before anything else happens. I choose to initialise it 
    // this way because it requires less oevrhead than the random default 
    // constructer

    /*   
    for (iter i = Player_vec.begin(); i != Player_vec.end(); ++i)
        make_war(proportional, *i);

    for (iter i = Player_vec.begin(); i != Player_vec.end(); ++i)
        make_war(rando, *i);

    std::cout << "The Player called proportional has average score " 
              << ((double) proportional.get_score()) / 
                 (double) Player_vec.size() 
              << std::endl   
              << "The Player called rando has troop_edployment member: ";

    iter_print(rando.get_troops().begin(), rando.get_troops().end());

    std::cout << "and average score "
              << ((double) rando.get_score()) / 
                 (double) Player_vec.size()   
              << std::endl;
*/
