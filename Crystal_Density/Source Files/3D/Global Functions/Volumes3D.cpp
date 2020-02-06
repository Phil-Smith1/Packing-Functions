#include <vector>

using namespace std;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

void Volumes3D ( double first_order_total_volume, double second_order_total_volume, double third_order_total_volume, vector<double>& volumes_at_least, vector<double>& volumes_exact )
{
    volumes_at_least.resize( 3 );
    volumes_exact.resize( 3 );
    
    volumes_at_least[0] = first_order_total_volume - second_order_total_volume + third_order_total_volume;
    volumes_at_least[1] = second_order_total_volume - 2 * third_order_total_volume;
    volumes_at_least[2] = third_order_total_volume;
    
    if (volumes_at_least[0] < tiny_num) volumes_at_least[0] = tiny_num;
    if (volumes_at_least[1] < tiny_num) volumes_at_least[1] = tiny_num;
    if (volumes_at_least[2] < tiny_num) volumes_at_least[2] = tiny_num;
    
    volumes_exact[0] = volumes_at_least[0] - volumes_at_least[1];
    volumes_exact[1] = volumes_at_least[1] - volumes_at_least[2];
    volumes_exact[2] = volumes_at_least[2];
    
    if (volumes_exact[0] < tiny_num) volumes_exact[0] = tiny_num;
    if (volumes_exact[1] < tiny_num) volumes_exact[1] = tiny_num;
    if (volumes_exact[2] < tiny_num) volumes_exact[2] = tiny_num;
}
