#include <iostream>

#define ALTERNATIVE 0

/* Factors class, composed of std::pair */
class factors
{
    private:
        std::pair<int, int> p;
    public:
        factors() { p = std::make_pair(0, 0); }
        factors(int i, int j) {
            p.first = i;
            p.second = j;
        }
        void print(void) { std::cout <<  p.first << " " << p.second << std::endl; }
        bool operator==(const factors &b) {
            if (((p.first == b.p.first) && (p.second == b.p.second)) ||
                ((p.second == b.p.first) && (p.first == b.p.second))
                )
                return true;
            return false;
        }
};

std::pair<int, int>& swap_pair_members(std::pair<int, int> &p)
{
    int t = p.first;
    p.first = p.second;
    p.second = t;
    return p;
}

/* Factors clas (Inherited from std::pair) */
class factors_ih : public std::pair<int, int>
{
    public:
        void print(void)
        {
            std::cout << this->first << " " << this->second << std::endl;
        }

        void swap_elements(void)
        {
            int t = this->first;
            this->first = this->second;
            this->second = t;
        }

        factors_ih &swap_elements(factors_ih &in)
        {
            int t = in.first;
            in.first = in.second;
            in.second = t;
            return in;
        }

        #ifndef ALTERNATIVE
        bool operator==(factors_ih &b)
        {
            std::pair<int, int> A = static_cast<std::pair<int, int>>(*this);
            std::pair<int, int> B = static_cast<std::pair<int, int>>(b);

            if (A == B)
                return true;

            A = swap_pair_members(A);

            if (A == B)
                return true;

            return false;
        }
        #endif
};

#ifdef ALTERNATIVE
/*
*   Casting to base class and then invoking the compare
*   operator sort of works, but my expectation here was
*   refer to the base class's operator in the derived class
*   like std::pair::==, which gets caught up in C++isms. 
*
*/
bool operator==(factors_ih &a, factors_ih &b)
{
    std::pair<int, int> A = static_cast<std::pair<int, int>>(a);
    std::pair<int, int> B = static_cast<std::pair<int, int>>(b);

    if (A == B)
        return true;

    A = swap_pair_members(A);

    if (A == B)
        return true;

    return false;
}
#endif

int main()
{
    class factors f;
    f.print();

    class factors f1(10, 20);
    class factors f2(20, 10);

    f1.print();
    f2.print();

    if (f1 == f2)
        std::cout << "Same" << std::endl;
    else
        std::cout << "Not equal" << std::endl;

    class factors_ih fih, fih_o;
    fih.first = 100; fih.second = 200;

    class factors_ih fih2;
    fih2.first = 200; fih2.second = 100;

    fih.print();

    if (fih == fih2)
        std::cout << "Same" << std::endl;
    else
        std::cout << "Not same" << std::endl;

    std::cout << "Swap test" << std::endl;
    fih.print();
    fih2.print();
    fih.swap_elements();
    fih.print();
    fih2.swap_elements();
    fih2.print();

    if (fih == fih2)
        std::cout << "Same" << std::endl;
    else
        std::cout << "Not same" << std::endl;

    return 0;
}