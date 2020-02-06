#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;

void Obtain_T2_Centres ( vector<P3>const& atom_cloud, string const& type_of_experiment, vector<P3>& T2_centres );
