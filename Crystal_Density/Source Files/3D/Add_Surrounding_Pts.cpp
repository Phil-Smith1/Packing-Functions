#include "Input3D.h"
#include "Fourth_Order_Radius.h"
#include "Distance_To_Cell.h"

void Add_Surrounding_Pts( Input3D& input3D, Cell3D& cell )
{
    int num_molecules = (int)cell.pts.size();
    
    vector<P3> translations;
    translations.reserve( 26 );
    
    translations.push_back( P3( 1, 0, 0 ) );
    translations.push_back( P3( -1, 0, 0 ) );
    translations.push_back( P3( 0, 1, 0 ) );
    translations.push_back( P3( 0, -1, 0 ) );
    translations.push_back( P3( 0, 0, 1 ) );
    translations.push_back( P3( 0, 0, -1 ) );
    translations.push_back( P3( 1, 1, 0 ) );
    translations.push_back( P3( 1, -1, 0 ) );
    translations.push_back( P3( -1, 1, 0 ) );
    translations.push_back( P3( -1, -1, 0 ) );
    translations.push_back( P3( 1, 0, 1 ) );
    translations.push_back( P3( 1, 0, -1 ) );
    translations.push_back( P3( -1, 0, 1 ) );
    translations.push_back( P3( -1, 0, -1 ) );
    translations.push_back( P3( 0, 1, 1 ) );
    translations.push_back( P3( 0, 1, -1 ) );
    translations.push_back( P3( 0, -1, 1 ) );
    translations.push_back( P3( 0, -1, -1 ) );
    translations.push_back( P3( 1, 1, 1 ) );
    translations.push_back( P3( 1, 1, -1 ) );
    translations.push_back( P3( 1, -1, 1 ) );
    translations.push_back( P3( -1, 1, 1 ) );
    translations.push_back( P3( 1, -1, -1 ) );
    translations.push_back( P3( -1, 1, -1 ) );
    translations.push_back( P3( -1, -1, 1 ) );
    translations.push_back( P3( -1, -1, -1 ) );
    
    vector<P3> original_pts = cell.pts;
    
    for (int counter_1 = 0; counter_1 < 6; ++counter_1)
    {
        for (int counter_2 = 0; counter_2 < num_molecules; ++counter_2)
        {
            P3 pt = P3( cell.pts[counter_2].x() + translations[counter_1].x() * cell.vertices[1].x() + translations[counter_1].y() * cell.vertices[3].x() + translations[counter_1].z() * cell.vertices[4].x(), cell.pts[counter_2].y() + translations[counter_1].x() * cell.vertices[1].y() + translations[counter_1].y() * cell.vertices[3].y() + translations[counter_1].z() * cell.vertices[4].y(), cell.pts[counter_2].z() + translations[counter_1].x() * cell.vertices[1].z() + translations[counter_1].y() * cell.vertices[3].z() + translations[counter_1].z() * cell.vertices[4].z() );
            
            if (Distance_To_Cell( cell, pt ) > 7.2) continue;
            
            else cell.pts.push_back( pt );
        }
    }
    
    double radius = Fourth_Order_Radius( cell );
    
    cell.pts = original_pts;
    
    for (int counter_1 = 0; counter_1 < translations.size(); ++counter_1)
    {
        for (int counter_2 = 0; counter_2 < num_molecules; ++counter_2)
        {
            P3 pt = P3( cell.pts[counter_2].x() + translations[counter_1].x() * cell.vertices[1].x() + translations[counter_1].y() * cell.vertices[3].x() + translations[counter_1].z() * cell.vertices[4].x(), cell.pts[counter_2].y() + translations[counter_1].x() * cell.vertices[1].y() + translations[counter_1].y() * cell.vertices[3].y() + translations[counter_1].z() * cell.vertices[4].y(), cell.pts[counter_2].z() + translations[counter_1].x() * cell.vertices[1].z() + translations[counter_1].y() * cell.vertices[3].z() + translations[counter_1].z() * cell.vertices[4].z() );
            
            if (Distance_To_Cell( cell, pt ) > radius) continue;
            
            else cell.pts.push_back( pt );
        }
    }
    
    if (input3D.auto_max_radius) input3D.max_radius = Fourth_Order_Radius( cell ) * 0.999;
}
