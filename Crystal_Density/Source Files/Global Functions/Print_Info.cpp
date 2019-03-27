#include <iostream>

using namespace std;

void Print_Info ( clock_t const& start_time, chrono::time_point<chrono::steady_clock>const& start )
{
    clock_t end_time = clock();
    
    double runtime = (end_time - start_time) / (double)CLOCKS_PER_SEC;
    auto elapsed = chrono::duration_cast<chrono::milliseconds>( chrono::steady_clock::now() - start );
    
    cout << "Code runtime: " << runtime << "s." << endl;
    cout << "Elapsed time: " << elapsed.count() / (double)1000 << "s." << endl << endl;
}
