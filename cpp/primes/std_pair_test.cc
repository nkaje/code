#include <iostream>

std::pair<int, int>& swap_members(std::pair<int, int> &p)
{
    int t = p.first;
    p.first = p.second;
    p.second = t;
    return p;
}

bool operator==(const std::pair<int, int> &A, const std::pair<int, int> &B)
{
    if (((A.first == B.first) && (A.second == B.second)) ||
        ((A.second == B.first) && (A.first == B.second)))
        return true;
    return false;
}

int main()
{
    std::pair<int, int> A = {2, 1};
    std::pair<int, int> B = {1, 2};

    std::cout << A.first << " " << A.second << std::endl;
    std::cout << B.first << " " << B.second << std::endl;

    A = swap_members(A);
    std::cout << A.first << " " << A.second << std::endl;

    if (A== B)
        std::cout << "Equal" << std::endl;
    else
        std::cout << "Not Equal" << std::endl;    
    return 0;
}