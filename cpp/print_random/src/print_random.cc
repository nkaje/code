#include <iostream>
#include <vector>
#include <time.h>
#include <cstring>
#include "logger.h"

#define DEBUG 0

class RandomNumbers
{
    private:
        std::vector<int> m_v;
        int m_sz;
        Logger m_logger;
        void swap(int i, int j);
        void dump(void);
    public:
        RandomNumbers(int N);
        ~RandomNumbers();
        void PrintRandom(void);
};

RandomNumbers::RandomNumbers(int N)
{
    m_sz = N;
    m_logger = Logger(LOG_INFO);

    for (int i = 0; i < N; i++)
        m_v.push_back(i);

    dump();
}

RandomNumbers::~RandomNumbers(void)
{
    dump();
    m_v.clear();
}

void RandomNumbers::PrintRandom(void)
{
    for (int l = m_sz; l > 0; l--) {
        int r = rand()%l;
        m_logger.Log(LOG_INFO, "%d\t", m_v[r]);
        swap(r, l-1);
    }
    m_logger.Log(LOG_INFO, "\n");
}

void RandomNumbers::swap(int i, int j)
{
    int t = m_v[i];
    m_v[i] = m_v[j];
    m_v[j] = t;
}

void RandomNumbers::dump(void)
{
    for (int i = 0; i < m_sz; i++)
        m_logger.Log(LOG_DEBUG, "%d\t", m_v[i]);
    m_logger.Log(LOG_DEBUG, "\n");
}

int main()
{
    srand((unsigned int)time(NULL));
    RandomNumbers RN(10);
    RN.PrintRandom();
    return 0;
}
