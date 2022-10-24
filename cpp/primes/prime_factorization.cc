#include <iostream>
#include <vector>

#define LIMIT   0x100

struct factors {
    int a;
    int b;
};

class Pair {
    private:
        int m_a;
        int m_b;
    public:
        Pair(int a, int b) { m_a = a; m_b = b; }
        Pair() { m_a = 0; m_b = 0; };
        int get_a(void) { return m_a; }
        int get_b(void) { return m_b; }
        bool is_same(class Pair &P) {
            if ((P.get_a() == this->m_a && P.get_b() == this->m_b) ||
                (P.get_b() == this->m_a && P.get_a() == this->m_b))
                return true;
            return false;
        }
};

bool is_prime(const int i)
{
    if (i == 0)
        return false;
    if (i == 1)
        return false;
    if (i == 2)
        return true;

    for(int n = 2; n <= i/2; n++) {
        if (i%n == 0) {
            return false;
        }
    }
    return true;
}

bool check_for_duplicate(std::vector<class Pair>&P, class Pair &p)
{
    for(auto &it : P) {
        if (p.is_same(it))
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
            if (is_prime(it.get_a()) && is_prime(it.get_b())) {
                std::cout << n << ":" << std::endl;
                std::cout << "  " << it.get_a() << " " << it.get_b() << std::endl;
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
