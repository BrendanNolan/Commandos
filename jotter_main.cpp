#include <iostream>
#include <vector>

#include "blotto.h"

template <class It>
void iter_print(It a, It b)
{
    std::cout << "( " << *a;
    for (It i = ++a; i != b; ++i)
        std::cout << ", " << *i;
    std::cout << " )" << std::endl;

    return;
}

int main()
{
    Player Alice({ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 });
    Player Carol({ 20, 0, 10, 5, 10, 5, 10, 20, 0, 20 });

    make_one_sided_war(Alice, Carol);
    make_one_sided_war(Carol, Alice);

    std::cout << "Alice had strat: ";
    iter_print(Alice.get_soldiers().begin(), Alice.get_soldiers().end());
    std::cout << "and score " << Alice.get_score() << std::endl;

    std::cout << "Carol had strat: ";
    iter_print(Carol.get_soldiers().begin(), Carol.get_soldiers().end());
    std::cout << " and score " << Carol.get_score() << std::endl;

    return 0;
}