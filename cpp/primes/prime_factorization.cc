#include <iostream>
#include <vector>

#define LIMIT   0x100

class Pair : public std::pair<int, int>
{
    public:
        Pair(int a, int b) { first = a; second = b; };
        Pair() { first = 0; second = 0; };
};

bool operator==(const Pair &A, const Pair &B)
{
    if (((A.first == B.first) && (A.second == B.second)) ||
         ((A.first == B.second) && (A.second == B.first)))
        return true;
    return false;
}

bool is_prime(const int i)
{
    if (i == 0)
        return false;
    if (i == 1)
        return false;
    if (i == 2)
        return true;

    for (int n = 2; n <= i/2; n++) {
        if (i%n == 0) {
            return false;
        }
    }
    return true;
}

bool check_for_duplicate(std::vector<class Pair>&P, class Pair &p)
{
    for (auto &it : P) {
        if (it == p)
            return true;
    }
    return false;
}

void find_factors(std::vector<class Pair>&PLT, int num)
{
    for (int i = 0; i <= num/2; i++) {
        for (int j = 0; j <= num/2; j++) {
            if ((i * j) == num) {
                Pair p(i, j);
                if (!check_for_duplicate(PLT, p))
                    PLT.push_back(p);
            }
        }
    }
}

void print_prime_factors(int i)
{
    std::vector<class Pair> PLT;

    for (int n = 4; n < i; n++) {
        find_factors(PLT, n);

       for (auto &it : PLT) {
            if (is_prime(it.first) && is_prime(it.second)) {
                std::cout << n << ":" << std::endl;
                std::cout << " " << it.first << " " << it.second << std::endl;
            }
        }
        PLT.clear();
    }
}

int main()
{
    print_prime_factors(LIMIT);
    return 0;
}
