#include <iostream>
#include <vector>
#include <ctime>

#define DEBUG 0

class RandomNumbers
{
    private:
        std::vector<int> m_v;
        int m_sz;
        void swap(int i, int j);
    public:
        RandomNumbers(int N);
        ~RandomNumbers();
        void PrintRandom(void);
};

RandomNumbers::RandomNumbers(int N)
{
    m_sz = N;

    for(int i = 0; i < N; i++)
        m_v.push_back(i);

#if DEBUG
    for(int i = 0; i < m_sz; i++)
        std::cout << m_v[i];
    std::cout << std::endl;
#endif
}

RandomNumbers::~RandomNumbers(void)
{
#if DEBUG
    std::cout << "destroyed" << std::endl;
#endif
}

void RandomNumbers::PrintRandom(void)
{
    for (int l = m_sz; l > 0; l--) {
        int r = rand()%l;
        std::cout << m_v[r] << "\t";
        swap(r, l-1);
    }
    std::cout << std::endl;
}

void RandomNumbers::swap(int i, int j)
{
    int t = m_v[i];
    m_v[i] = m_v[j];
    m_v[j] = t;
}

int main()
{
    srand(time(0));
    RandomNumbers RN(10);
    RN.PrintRandom();
    return 0;
}
