#include "Frac_To_Cart_Coords.h"

#include <string>
#include <vector>

using namespace std;

void Assign_Experimental_Cell_Shape ( vector<pair<string, double>>& cell_shape, string const& label )
{
    cell_shape.clear();
    
    if (label == "a")
    {
        cell_shape.push_back( pair<string, double>( "_cell_length_a", 22.5124 ) );
        cell_shape.push_back( pair<string, double>( "_cell_length_b", 22.5124 ) );
        cell_shape.push_back( pair<string, double>( "_cell_length_c", 7.3367 ) );
        cell_shape.push_back( pair<string, double>( "_cell_angle_alpha", 90 ) );
        cell_shape.push_back( pair<string, double>( "_cell_angle_beta", 90 ) );
        cell_shape.push_back( pair<string, double>( "_cell_angle_gamma", 90 ) );
    }
    
    else if (label == "b")
    {
        cell_shape.push_back( pair<string, double>( "_cell_length_a", 7.246 ) );
        cell_shape.push_back( pair<string, double>( "_cell_length_b", 13.0328 ) );
        cell_shape.push_back( pair<string, double>( "_cell_length_c", 20.66 ) );
        cell_shape.push_back( pair<string, double>( "_cell_angle_alpha", 72.464 ) );
        cell_shape.push_back( pair<string, double>( "_cell_angle_beta", 86.349 ) );
        cell_shape.push_back( pair<string, double>( "_cell_angle_gamma", 74.035 ) );
    }
    
    else if (label == "c")
    {
        cell_shape.push_back( pair<string, double>( "_cell_length_a", 23.2209 ) );
        cell_shape.push_back( pair<string, double>( "_cell_length_b", 23.2209 ) );
        cell_shape.push_back( pair<string, double>( "_cell_length_c", 7.2864 ) );
        cell_shape.push_back( pair<string, double>( "_cell_angle_alpha", 90 ) );
        cell_shape.push_back( pair<string, double>( "_cell_angle_beta", 90 ) );
        cell_shape.push_back( pair<string, double>( "_cell_angle_gamma", 120 ) );
    }
    
    else if (label == "d")
    {
        cell_shape.push_back( pair<string, double>( "_cell_length_a", 7.2523 ) );
        cell_shape.push_back( pair<string, double>( "_cell_length_b", 13.033 ) );
        cell_shape.push_back( pair<string, double>( "_cell_length_c", 20.693 ) );
        cell_shape.push_back( pair<string, double>( "_cell_angle_alpha", 72.701 ) );
        cell_shape.push_back( pair<string, double>( "_cell_angle_beta", 86.552 ) );
        cell_shape.push_back( pair<string, double>( "_cell_angle_gamma", 73.915 ) );
    }
}

void Assign_Experimental_Centres ( vector<P3>& T2_centres, double ** matrix, string const& label )
{
    T2_centres.clear();
    
    if (label == "a")
    {
        /*P3 p = P3( 0.76646, 0.18656, 0 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
        
        p = P3( 0.18656, 0.23354, 0.5 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
        
        p = P3( 0.81344, 0.76646, 0.5 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
        
        p = P3( 0.23354, 0.81344, 0 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );*/
        
        P3 p = P3( 0.764, 0.187, 0 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
        
        p = P3( 0.187, 0.236, 0.5 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
        
        p = P3( 0.813, 0.764, 0.5 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
        
        p = P3( 0.236, 0.813, 0 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
    }
    
    else if (label == "b")
    {
        /*P3 p = P3( 0.7349, 0.66898, 0.158815 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
        
        p = P3( 0.2651, 0.33102, 0.841185 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );*/
        
        P3 p = P3( 0.736, 0.663, 0.172 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
        
        p = P3( 0.264, 0.337, 0.828 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
    }
    
    else if (label == "c")
    {
        /*P3 p = P3( 0.33333, 0.66667, 0.75 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
        
        p = P3( 0.66667, 0.33333, 0.25 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );*/
        
        P3 p = P3( 0.333, 0.667, 0.75 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
        
        p = P3( 0.667, 0.333, 0.25 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
    }
    
    else if (label == "d")
    {
        /*P3 p = P3( 0.7707, 0.33245, 0.34045 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
        
        p = P3( 0.2293, 0.66755, 0.65955 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );*/
        
        P3 p = P3( 0.769, 0.338, 0.328 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
        
        p = P3( 0.231, 0.662, 0.672 );
        Frac_To_Cart_Coords( matrix, p );
        T2_centres.push_back( p );
    }
}
