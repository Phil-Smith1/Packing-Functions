#include <gemmi/cif.hpp>

#include <string>
#include <vector>

#include "Frac_To_Cart_Coords.h"

using namespace std;
namespace cif = gemmi::cif;

void Read_Atom_Coords ( cif::Block * block, double ** matrix, vector<P3>& cloud );
