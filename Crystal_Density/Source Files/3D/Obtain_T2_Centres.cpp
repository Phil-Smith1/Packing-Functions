#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;

void Obtain_T2_Centres ( vector<P3>const& atom_cloud, string const& type_of_experiment, vector<P3>& T2_centres )
{
    int num_molecules = atom_cloud.size() / (double)46;
    
    T2_centres.reserve( num_molecules );
    
    for (int counter = 0; counter < num_molecules; ++counter)
    {
        P3 atom_1 = atom_cloud[9 + counter * 32], atom_2 = atom_cloud[22 + counter * 32];
        
        P3 oxygen_1 = atom_cloud[0 + counter * 32];
        P3 oxygen_2 = atom_cloud[1 + counter * 32];
        P3 oxygen_3 = atom_cloud[2 + counter * 32];
        
        P3 centre = P3( 0.5 * (atom_1.x() + atom_2.x()), 0.5 * (atom_1.y() + atom_2.y()), 0.5 * (atom_1.z() + atom_2.z()) );
        
        if (type_of_experiment == "Molecule_Centres") T2_centres.push_back( centre );
        
        else if (type_of_experiment == "Molecule_Centres_with_Oxygens")
        {
            T2_centres.push_back( oxygen_1 );
            T2_centres.push_back( oxygen_2 );
            T2_centres.push_back( oxygen_3 );
            T2_centres.push_back( centre );
        }
        
        else
        {
            T2_centres.push_back( oxygen_1 );
            T2_centres.push_back( oxygen_2 );
            T2_centres.push_back( oxygen_3 );
        }
    }
}
