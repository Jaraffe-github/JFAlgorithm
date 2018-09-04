#include "JFSort.h"

#include <iostream> 
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <random>

#include <string>

class SimpleTimer
{
public:
    using Clock = std::chrono::system_clock;
    using Tick = std::chrono::time_point<Clock>;

    void Start()
    {
        startTime = Clock::now();
    }

    double ElapsedTime()
    {
        Tick endTime = Clock::now();
        return std::chrono::duration<double>(endTime - startTime).count();
    }

private:
    Tick startTime;
};

using namespace JFFoundation;
using namespace JFAlgorithm;

const size_t TestDataSetCount = 10000000ull;

int main()
{
    SimpleTimer timer;
    double mySortUsageTime = 0.0;
    double stlSortUsageTime = 0.0;

    // string test
    //std::vector<std::string> testDataSet1;
    //std::vector<std::string> testDataSet2;
    //testDataSet1.reserve(TestDataSetCount);
    //testDataSet2.reserve(TestDataSetCount);
    //
    //// Init
    //for (int i = 0; i < TestDataSetCount; ++i)
    //{
    //    std::string temp = "SortAlgorithm Speed Test Number : ";
    //    temp += std::to_string(i);
    //    testDataSet1.push_back(temp);
    //}

    // int test
    std::vector<int> testDataSet1;
    std::vector<int> testDataSet2;
    testDataSet1.reserve(TestDataSetCount);
    testDataSet2.reserve(TestDataSetCount);
    
    // Init
    for (int i = 0; i < TestDataSetCount; ++i)
    {
        testDataSet1.push_back(i);
        //testDataSet1.push_back(0);
    }

    while (true)
    {
        // random and copy
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(testDataSet1.begin(), testDataSet1.end(), g);
        testDataSet2 = testDataSet1;

        // mySort
        timer.Start();
        Sort(testDataSet1.begin(), testDataSet1.end());
        mySortUsageTime = timer.ElapsedTime();

        // stlSort
        timer.Start();
        std::sort(testDataSet2.begin(), testDataSet2.end());
        stlSortUsageTime = timer.ElapsedTime();

        // check
        for (int i = 0; i < TestDataSetCount; ++i)
        {
            if (testDataSet1[i] != testDataSet2[i])
            {
                std::cout << "SortFail" << std::endl;
                std::cout << "Index : " << i << std::endl;
                std::cout << "MySort : " << testDataSet1[i] << std::endl;
                std::cout << "STLSort : " << testDataSet2[i] << std::endl;
            }
        }

        // Print UsageTime
        std::cout << "MySort UsageTime : " << mySortUsageTime << std::endl;
        std::cout << "stlSort UsageTime : " << stlSortUsageTime << std::endl;

        std::cout << std::endl;

        // what is winner?
        if (mySortUsageTime > stlSortUsageTime)
            std::cout << "Winner : " << "STLSort" << std::endl;
        else
            std::cout << "Winner : " << "MySort" << std::endl;

        std::cout << std::endl;
    }

    return 0;
}