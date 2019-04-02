#pragma once

double Circle_Area_Within_Cell ( Cell& cell, Circle const& circle )
{
    bool intersection = Cell_Circle_Intersections( cell, circle );
    
    int num_vertices_within_circle = Num_Vertices_Within_Circle( cell, circle );
    
    bool centre_within_cell = Pt_Within_Convex_Hull( cell, circle.c );
    
    if (!intersection)
    {
        if (num_vertices_within_circle == 4) return cell.area;
        
        else if (centre_within_cell) return circle.area;
        
        else return 0;
    }
    
    else
    {
        if (num_vertices_within_circle == 0)
        {
            double area = circle.area;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                area -= Area_Excluded_By_Exterior_Edge( circle, cell.edges[counter], cell );
            }
            
            if (area == circle.area)
            {
                if (Pt_Within_Convex_Hull( cell, circle.c )) return area;
                
                else return 0;
            }
            
            else return area;
        }
        
        else if (num_vertices_within_circle == 1)
        {
            vector<Edge> key_edges;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if (cell.edges[counter].intersection_type == 2 || cell.edges[counter].intersection_type == 5)
                {
                    key_edges.push_back( cell.edges[counter] );
                }
            }
            
            double area = Irregular_Sector_Area( circle, key_edges[0], key_edges[1] );
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                area -= Area_Excluded_By_Exterior_Edge( circle, cell.edges[counter], cell );
            }
            
            return area;
        }
        
        else if (num_vertices_within_circle == 2)
        {
            bool type_1_edge = false;
            Edge key_edge;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if (cell.edges[counter].intersection_type == 1)
                {
                    key_edge = cell.edges[counter];
                    type_1_edge = true;
                }
            }
            
            if (type_1_edge)
            {
                int index_1 = (key_edge.index + 3) % 4;
                int index_2 = (key_edge.index + 1) % 4;
                
                double area = Interior_Edge_Area( circle, cell.edges[index_1], key_edge, cell.edges[index_2] );
                
                for (int counter = 0; counter < cell.edges.size(); ++counter)
                {
                    area -= Area_Excluded_By_Exterior_Edge( circle, cell.edges[counter], cell );
                }
                
                return area;
            }
            
            else
            {
                double area_1, area_2;
                
                if (Norm( cell.edges[0].startpt, circle.c ) < circle.r - tiny_num)
                {
                    area_1 = Irregular_Sector_Area( circle, cell.edges[0], cell.edges[3] );
                    area_2 = Irregular_Sector_Area( circle, cell.edges[1], cell.edges[2] );
                }
                
                else
                {
                    area_1 = Irregular_Sector_Area( circle, cell.edges[0], cell.edges[1] );
                    area_2 = Irregular_Sector_Area( circle, cell.edges[2], cell.edges[3] );
                }
                
                return area_1 + area_2 - circle.area;
            }
        }
        
        else
        {
            vector<Edge> key_edges;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if (cell.edges[counter].intersection_type == 2) key_edges.push_back( cell.edges[counter] );
            }
            
            if (key_edges.size() == 0) return cell.area;
            
            else return cell.area - Concave_Cone_Area( circle, key_edges[0], key_edges[1] );
        }
    }
}

double Two_Circle_Intersection_Concave_Cone_Area ( Circle const& c1, Circle const& c2, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4 )
{
    P2 v, i1, i2;
    
    if (Norm( e1.startpt, c1.c ) > c1.r + tiny_num || Norm( e1.startpt, c2.c ) > c2.r + tiny_num)
    {
        v = e1.startpt;
    }
    
    else v = e1.endpt;
    
    int t1, t2;
    
    if (e1.intersection_type != 1 && Norm( e1.i1, c2.c ) < c2.r - tiny_num)
    {
        i1 = e1.i1;
        t1 = 1;
    }
    
    else if (e2.intersection_type != 1 && Norm( e2.i1, c1.c ) < c1.r - tiny_num)
    {
        i1 = e2.i1;
        t1 = 2;
    }
    
    else
    {
        i1 = e1.i1;
        t1 = 3;
    }
    
    if (e3.intersection_type != 1 && Norm( e3.i1, c2.c ) < c2.r - tiny_num)
    {
        i2 = e3.i1;
        t2 = 1;
    }
    
    else if (e4.intersection_type != 1 && Norm( e4.i1, c1.c ) < c1.r - tiny_num)
    {
        i2 = e4.i1;
        t2 = 2;
    }
    
    else
    {
        i2 = e3.i1;
        t2 = 3;
    }
    
    if (t1 == 3)
    {
        if (t2 == 1)
        {
            return Concave_Cone_Area( c1, e1, e3 );
        }
        
        else return Concave_Cone_Area( c2, e2, e4 );
    }
    
    else if (t2 == 3)
    {
        if (t1 == 1)
        {
            return Concave_Cone_Area( c1, e1, e3 );
        }
        
        else return Concave_Cone_Area( c2, e2, e4 );
    }
    
    else if (t1 == t2)
    {
        if (t1 == 1)
        {
            return Concave_Cone_Area( c1, e1, e3 );
        }
        
        else return Concave_Cone_Area( c2, e2, e4 );
    }
    
    else
    {
        P2 i3, j1, j2;
        
        Intersection_Of_Two_Circles( c1, c2, j1, j2 );
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 1) return Concave_Cone_Area( c1, e1, e ) + Concave_Cone_Area( c2, e4, e );
        
        else return Concave_Cone_Area( c1, e3, e ) + Concave_Cone_Area( c2, e2, e );
    }
}

double Two_Circle_Intersection_Interior_Edge_Area ( Circle const& c1, Circle const& c2, Edge const& e, Cell const& cell_1, Cell const& cell_2 )
{
    int index_1 = (e.index + 3) % 4;
    int index_2 = (e.index + 1) % 4;
    
    P2 p1, p2, p3, p4;
    
    p2 = e.startpt;
    p3 = e.endpt;
    
    if (cell_1.edges[index_1].intersection_type != 1 && Norm( cell_1.edges[index_1].i1, c2.c ) < c2.r)
    {
        p1 = cell_1.edges[index_1].i1;
    }
    
    else p1 = cell_2.edges[index_1].i1;
    
    if (cell_1.edges[index_2].intersection_type != 1 && Norm( cell_1.edges[index_2].i1, c2.c ) < c2.r)
    {
        p4 = cell_1.edges[index_2].i1;
    }
    
    else p4 = cell_2.edges[index_2].i1;
    
    double triangle_area_1 = Triangle_Area( p1, p2, p3 );
    double triangle_area_2 = Triangle_Area( p1, p3, p4 );
    
    Cell cell_3;
    
    if (e.index == 0) Make_Cell( p1, p4, cell_1.vertices[2], cell_1.vertices[3], cell_3 );
    
    else if (e.index == 1) Make_Cell( cell_1.vertices[0], p1, p4, cell_1.vertices[3], cell_3 );
    
    else if (e.index == 2) Make_Cell( cell_1.vertices[0], cell_1.vertices[1], p1, p4, cell_3 );
    
    else if (e.index == 3) Make_Cell( p4, cell_1.vertices[1], cell_1.vertices[2], p1, cell_3 );
    
    return triangle_area_1 + triangle_area_2 + Two_Circle_Intersection_Area_Within_Cell( cell_3, c1, c2 );
}

double Two_Circle_Intersection_Irregular_Sector_Area ( Circle const& c1, Circle const& c2, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4 )
{
    P2 v, i1, i2, j1, j2;
    
    if (Norm( e1.startpt, c1.c ) < c1.r - tiny_num && Norm( e1.startpt, c2.c ) < c2.r - tiny_num)
    {
        v = e1.startpt;
    }
    
    else v = e1.endpt;
    
    int t1, t2;
    
    if (e1.intersection_type != 1 && Norm( e1.i1, c2.c ) < c2.r - tiny_num)
    {
        i1 = e1.i1;
        t1 = 1;
    }
    
    else if (e2.intersection_type != 1 && Norm( e2.i1, c1.c ) < c1.r - tiny_num)
    {
        i1 = e2.i1;
        t1 = 2;
    }
    
    else
    {
        i1 = e1.i1;
        t1 = 3;
    }
    
    if (e3.intersection_type != 1 && Norm( e3.i1, c2.c ) < c2.r - tiny_num)
    {
        i2 = e3.i1;
        t2 = 1;
    }
    
    else if (e4.intersection_type != 1 && Norm( e4.i1, c1.c ) < c1.r - tiny_num)
    {
        i2 = e4.i1;
        t2 = 2;
    }
    
    else
    {
        i2 = e3.i1;
        t2 = 3;
    }
    
    Intersection_Of_Two_Circles( c1, c2, j1, j2 );
    
    double intersection_area = Two_Circle_Intersection_Area( c1, c2 );
    
    L2 l( i1, i2 );
    
    if (t1 == 3)
    {
        if (t2 == 3)
        {
            double area_1, area_2;
            
            area_1 = Irregular_Sector_Area( c1, e1, e3 );
            area_2 = Irregular_Sector_Area( c2, e2, e4 );
            
            return (area_1 < area_2) ? area_1 : area_2;
        }
        
        else if (t2 == 1)
        {
            double area = Irregular_Sector_Area( c1, e1, e3 );
            
            int t3;
            
            if (Norm( e1.i1, j1 ) < tiny_num) t3 = 1;
            else t3 = 2;
            
            if (t3 == 1)
            {
                if (Same_Side( l, j2, v )) return area;
                
                else return intersection_area - c1.area + area;
            }
            
            else
            {
                if (Same_Side( l, j1, v )) return area;
                
                else return intersection_area - c1.area + area;
            }
        }
        
        else
        {
            double area = Irregular_Sector_Area( c2, e2, e4 );
            
            int t3;
            
            if (Norm( e2.i1, j1 ) < tiny_num) t3 = 1;
            else t3 = 2;
            
            if (t3 == 1)
            {
                if (Same_Side( l, j2, v )) return area;
                
                else return intersection_area - c2.area + area;
            }
            
            else
            {
                if (Same_Side( l, j1, v )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
    }
    
    else if (t2 == 3)
    {
        if (t1 == 1)
        {
            double area = Irregular_Sector_Area( c1, e1, e3 );
            
            int t3;
            
            if (Norm( e3.i1, j1 ) < tiny_num) t3 = 1;
            else t3 = 2;
            
            if (t3 == 1)
            {
                if (Same_Side( l, j2, v )) return area;
                
                else return intersection_area - c1.area + area;
            }
            
            else
            {
                if (Same_Side( l, j1, v )) return area;
                
                else return intersection_area - c1.area + area;
            }
        }
        
        else
        {
            double area = Irregular_Sector_Area( c2, e2, e4 );
            
            int t3;
            
            if (Norm( e4.i1, j1 ) < tiny_num) t3 = 1;
            else t3 = 2;
            
            if (t3 == 1)
            {
                if (Same_Side( l, j2, v )) return area;
                
                else return intersection_area - c2.area + area;
            }
            
            else
            {
                if (Same_Side( l, j1, v )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
    }
    
    else if (t1 == t2)
    {
        if (t1 == 1)
        {
            double area = Irregular_Sector_Area( c1, e1, e3 );
            
            if (Same_Side( l, j1, v )) return area;
            
            else return intersection_area - c1.area + area;
        }
        
        else
        {
            double area = Irregular_Sector_Area( c2, e2, e4 );
            
            if (Same_Side( l, j1, v )) return area;
            
            else return intersection_area - c2.area + area;
        }
    }
    
    else
    {
        if (t1 == 2)
        {
            P2 p = i1;
            i1 = i2;
            i2 = p;
        }
        
        double triangle_area_1 = Triangle_Area( v, i1, i2 );
        
        P2 i3;
        
        if (!Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        double triangle_area_2 = Triangle_Area( i1, i2, i3 );
        double segment_area_1 = Segment_Area( c1, i1, i3 );
        
        L2 l1( i1, i3 );
        
        if (!Same_Side( l1, c1.c, v )) segment_area_1 = c1.area - segment_area_1;
        
        double segment_area_2 = Segment_Area( c2, i2, i3 );
        
        L2 l2( i2, i3 );
        
        if (!Same_Side( l2, c2.c, v )) segment_area_2 = c2.area - segment_area_2;
        
        return triangle_area_1 + triangle_area_2 + segment_area_1 + segment_area_2;
    }
}

double Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge ( Circle const& c1, Circle const& c2, Edge const& e1, Edge const& e2, Cell const& cell )
{
    P2 i1, i2;
    
    Intersection_Of_Two_Circles( c1, c2, i1, i2 );
    
    if (squared_distance( e1.line, i1 ) < tiny_num && squared_distance( e1.line, i2 ) < tiny_num)
    {
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            double area_1 = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
            double area_2 = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
            
            return (area_1 < area_2) ? area_1 : area_2;
        }
    }
    
    else if (squared_distance( e1.line, i1 ) < tiny_num)
    {
        double intersection_area = Two_Circle_Intersection_Area( c1, c2 );
        
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            if (Norm( e1.i1, c2.c ) < c2.r - tiny_num || Norm( e1.i2, c2.c ) < c2.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c1.area + area;
            }
        }
        
        if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
        {
            if (Norm( e2.i1, c1.c ) < c1.r - tiny_num || Norm( e2.i2, c1.c ) < c1.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
                
                if (Correct_Side_Of_Cell( cell, e2, i2 )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i2 ) < tiny_num)
    {
        double intersection_area = Two_Circle_Intersection_Area( c1, c2 );
        
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            if (Norm( e1.i1, c2.c ) < c2.r - tiny_num || Norm( e1.i2, c2.c ) < c2.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c1.area + area;
            }
        }
        
        if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
        {
            if (Norm( e2.i1, c1.c ) < c1.r - tiny_num || Norm( e2.i2, c1.c ) < c1.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
                
                if (Correct_Side_Of_Cell( cell, e2, i1 )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
    }
    
    else
    {
        if (e1.line.oriented_side( i1 ) != e1.line.oriented_side( i2 ))
        {
            if ((e1.intersection_type == 2 || e1.intersection_type == 3 || e1.intersection_type == 4 || e1.intersection_type == 5 || e1.intersection_type == 6 || e1.intersection_type == 7) && (e2.intersection_type == 2 || e2.intersection_type == 3 || e2.intersection_type == 4 || e2.intersection_type == 5 || e2.intersection_type == 6 || e2.intersection_type == 7))
            {
                P2 i3, i4, i5;
                
                if (Norm( e1.i1, c2.c ) < c2.r) i3 = e1.i1;
                else i3 = e1.i2;
                
                if (Norm( e2.i1, c1.c ) < c1.r) i4 = e2.i1;
                else i4 = e2.i2;
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) i5 = i2;
                else i5 = i1;
                
                double triangle_area = Triangle_Area( i3, i4, i5 );
                double segment_area_1 = Segment_Area( c1, i3, i5 );
                
                L2 l1( i3, i5 );
                
                if (!Same_Side( l1, i4, c1.c )) segment_area_1 = c1.area - segment_area_1;
                
                double segment_area_2 = Segment_Area( c2, i4, i5 );
                
                L2 l2( i4, i5 );
                
                if (!Same_Side( l2, i3, c2.c )) segment_area_2 = c2.area - segment_area_2;
                
                return triangle_area + segment_area_1 + segment_area_2;
            }
        }
        
        else
        {
            double intersection_area = Two_Circle_Intersection_Area( c1, c2 );
            
            if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
            {
                if (Norm( e1.i1, c2.c ) < c2.r - tiny_num && Norm( e1.i2, c2.c ) < c2.r - tiny_num)
                {
                    double area = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
                    
                    if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                    
                    else return intersection_area - c1.area + area;
                }
            }
            
            if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
            {
                if (Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i2, c1.c ) < c1.r - tiny_num)
                {
                    double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
                    
                    if (Correct_Side_Of_Cell( cell, e2, i1 )) return area;
                    
                    else return intersection_area - c2.area + area;
                }
            }
        }
    }
    
    return 0;
}

double Two_Circle_Intersection_Area_Within_Cell ( Cell& cell, Circle const& c1, Circle const& c2 )
{
    double intersection_area = Two_Circle_Intersection_Area( c1, c2 );
    
    if (intersection_area < 0 + tiny_num) return 0;
    
    P2 i1, i2;
    
    bool non_trivial_intersection = Intersection_Of_Two_Circles( c1, c2, i1, i2 );
    
    if (!non_trivial_intersection)
    {
        Circle min_circle = (c1.r < c2.r) ? c1 : c2;
        
        return Circle_Area_Within_Cell( cell, min_circle );
    }
    
    Cell cell_1 = cell, cell_2 = cell;
    
    bool cell_c1_intersection = Cell_Circle_Intersections( cell_1, c1 );
    bool cell_c2_intersection = Cell_Circle_Intersections( cell_2, c2 );
    
    int num_vertices_within_c1 = Num_Vertices_Within_Circle( cell, c1 );
    int num_vertices_within_c2 = Num_Vertices_Within_Circle( cell, c2 );
    
    bool c1_centre_within_cell = Pt_Within_Convex_Hull( cell, c1.c );
    bool c2_centre_within_cell = Pt_Within_Convex_Hull( cell, c2.c );
    
    if (!cell_c1_intersection && !cell_c2_intersection)
    {
        if (num_vertices_within_c1 == 4 && num_vertices_within_c2 == 4) return cell.area;
        
        else if (num_vertices_within_c1 == 4 || num_vertices_within_c2 == 4) return 0;
        
        else if (c1_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!cell_c1_intersection && cell_c2_intersection)
    {
        if (num_vertices_within_c1 == 4) return Circle_Area_Within_Cell( cell, c2 );
        
        else if (c1_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (cell_c1_intersection && !cell_c2_intersection)
    {
        if (num_vertices_within_c2 == 4) return Circle_Area_Within_Cell( cell, c1 );
        
        else if (c2_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else
    {
        int num_vertices_within_both_circles = 0;
        
        for (int counter = 0; counter < cell.vertices.size(); ++counter)
        {
            if (Norm( c1.c, cell.vertices[counter] ) < c1.r - tiny_num && Norm( c2.c, cell.vertices[counter] ) < c2.r - tiny_num) ++num_vertices_within_both_circles;
        }
        
        if (num_vertices_within_both_circles == 0)
        {
            double area = intersection_area;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                area -= Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, cell_1.edges[counter], cell_2.edges[counter], cell );
            }
            
            if (area == intersection_area)
            {
                V2 v1 = i1 - ORIGIN, v2 = i2 - ORIGIN;
                
                P2 p = ORIGIN + 0.5 * v1 + 0.5 * v2;
                
                if (Pt_Within_Convex_Hull( cell, p )) return area;
                
                else return 0;
            }
            
            else return area;
        }
        
        else if (num_vertices_within_both_circles == 1)
        {
            vector<int> key_edges;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if ((cell_1.edges[counter].intersection_type == 1 || cell_1.edges[counter].intersection_type == 2 || cell_1.edges[counter].intersection_type == 5) && (cell_2.edges[counter].intersection_type == 1 || cell_2.edges[counter].intersection_type == 2 || cell_2.edges[counter].intersection_type == 5))
                {
                    key_edges.push_back( counter );
                }
            }
            
            double area = Two_Circle_Intersection_Irregular_Sector_Area( c1, c2, cell_1.edges[key_edges[0]], cell_2.edges[key_edges[0]], cell_1.edges[key_edges[1]], cell_2.edges[key_edges[1]] );
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                area -= Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, cell_1.edges[counter], cell_2.edges[counter], cell );
            }
            
            return area;
        }
        
        else if (num_vertices_within_both_circles == 2)
        {
            bool type_1_edge = false;
            Edge key_edge;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if (cell_1.edges[counter].intersection_type == 1 && cell_2.edges[counter].intersection_type == 1)
                {
                    key_edge = cell.edges[counter];
                    type_1_edge = true;
                }
            }
            
            if (type_1_edge)
            {
                return Two_Circle_Intersection_Interior_Edge_Area( c1, c2, key_edge, cell_1, cell_2 );
            }
            
            else
            {
                double area_1, area_2;
                
                if (Norm( cell.edges[0].startpt, c1.c ) < c1.r - tiny_num && Norm( cell.edges[0].startpt, c2.c ) < c2.r - tiny_num)
                {
                    area_1 = Two_Circle_Intersection_Irregular_Sector_Area( c1, c2, cell_1.edges[0], cell_2.edges[0], cell_1.edges[3], cell_2.edges[3] );
                    
                    area_2 = Two_Circle_Intersection_Irregular_Sector_Area( c1, c2, cell_1.edges[1], cell_2.edges[1], cell_1.edges[2], cell_2.edges[2] );
                }
                
                else
                {
                    area_1 = Two_Circle_Intersection_Irregular_Sector_Area( c1, c2, cell_1.edges[0], cell_2.edges[0], cell_1.edges[1], cell_2.edges[1] );
                    
                    area_2 = Two_Circle_Intersection_Irregular_Sector_Area( c1, c2, cell_1.edges[2], cell_2.edges[2], cell_1.edges[3], cell_2.edges[3] );
                }
                
                return area_1 + area_2 - intersection_area;
            }
        }
        
        else
        {
            vector<int> key_edges;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if ((cell_1.edges[counter].intersection_type == 2 && (cell_2.edges[counter].intersection_type == 1 || cell_2.edges[counter].intersection_type == 2 || cell_2.edges[counter].intersection_type == 5)) || (cell_2.edges[counter].intersection_type == 2 && (cell_1.edges[counter].intersection_type == 1 || cell_1.edges[counter].intersection_type == 2 || cell_1.edges[counter].intersection_type == 5)))
                {
                    key_edges.push_back( counter );
                }
            }
            
            if (key_edges.size() == 0) return cell.area;
            
            else
            {
                return cell.area - Two_Circle_Intersection_Concave_Cone_Area( c1, c2, cell_1.edges[key_edges[0]], cell_2.edges[key_edges[0]], cell_1.edges[key_edges[1]], cell_2.edges[key_edges[1]] );
            }
        }
    }
}

double Three_Circle_Intersection_Concave_Cone_Area ( Circle const& c1, Circle const& c2, Circle const& c3, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4, Edge const& e5, Edge const& e6 )
{
    P2 v, i1, i2;
    
    if (Norm( e1.startpt, c1.c ) > c1.r + tiny_num || Norm( e1.startpt, c2.c ) > c2.r + tiny_num || Norm( e1.startpt, c3.c ) > c3.r + tiny_num )
    {
        v = e1.startpt;
    }
    
    else v = e1.endpt;
    
    int t1, t2;
    
    if (e1.intersection_type != 1 && Norm( e1.i1, c2.c ) < c2.r - tiny_num && Norm( e1.i1, c3.c ) < c3.r - tiny_num)
    {
        i1 = e1.i1;
        t1 = 1;
    }
    
    else if (e2.intersection_type != 1 && Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i1, c3.c ) < c3.r - tiny_num)
    {
        i1 = e2.i1;
        t1 = 2;
    }
    
    else if (e3.intersection_type != 1 && Norm( e3.i1, c1.c ) < c1.r - tiny_num && Norm( e3.i1, c2.c ) < c2.r - tiny_num)
    {
        i1 = e3.i1;
        t1 = 3;
    }
    
    else if (e2.intersection_type != 1 && Norm( e2.i1, c1.c ) < c1.r - tiny_num)
    {
        i1 = e2.i1;
        t1 = 4;
    }
    
    else if (e1.intersection_type != 1 && Norm( e1.i1, c2.c ) < c2.r - tiny_num)
    {
        i1 = e1.i1;
        t1 = 5;
    }
    
    else
    {
        i1 = e1.i1;
        t1 = 6;
    }
    
    if (e4.intersection_type != 1 && Norm( e4.i1, c2.c ) < c2.r - tiny_num && Norm( e4.i1, c3.c ) < c3.r - tiny_num)
    {
        i2 = e4.i1;
        t2 = 1;
    }
    
    else if (e5.intersection_type != 1 && Norm( e5.i1, c1.c ) < c1.r - tiny_num && Norm( e5.i1, c3.c ) < c3.r - tiny_num)
    {
        i2 = e5.i1;
        t2 = 2;
    }
    
    else if (e6.intersection_type != 1 && Norm( e6.i1, c1.c ) < c1.r - tiny_num && Norm( e6.i1, c2.c ) < c2.r - tiny_num)
    {
        i2 = e6.i1;
        t2 = 3;
    }
    
    else if (e5.intersection_type != 1 && Norm( e5.i1, c1.c ) < c1.r - tiny_num)
    {
        i2 = e5.i1;
        t2 = 4;
    }
    
    else if (e4.intersection_type != 1 && Norm( e4.i1, c2.c ) < c2.r - tiny_num)
    {
        i2 = e4.i1;
        t2 = 5;
    }
    
    else
    {
        i2 = e4.i1;
        t2 = 6;
    }
    
    if ((t1 == 4 && t2 == 5) || (t1 == 5 && t2 == 4)) return Concave_Cone_Area( c3, e3, e6 );
    
    else if ((t1 == 4 && t2 == 6) || (t1 == 6 && t2 == 4)) return Concave_Cone_Area( c2, e2, e5 );
    
    else if ((t1 == 5 && t2 == 6) || (t1 == 6 && t2 == 5)) return Concave_Cone_Area( c1, e1, e4 );
    
    else if ((t1 == 4 && t2 == 2) || (t1 == 2 && t2 == 4)) return Concave_Cone_Area( c2, e2, e5 );
    
    else if ((t1 == 4 && t2 == 3) || (t1 == 3 && t2 == 4)) return Concave_Cone_Area( c3, e3, e6 );
    
    else if ((t1 == 4 && t2 == 1) || (t1 == 1 && t2 == 4))
    {
        P2 i3, j1, j2;
        
        Intersection_Of_Two_Circles( c1, c2, j1, j2 );
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 1) return Concave_Cone_Area( c1, e1, e ) + Concave_Cone_Area( c2, e5, e );
        
        else return Concave_Cone_Area( c1, e4, e ) + Concave_Cone_Area( c2, e2, e );
    }
    
    else if ((t1 == 5 && t2 == 1) || (t1 == 1 && t2 == 5)) return Concave_Cone_Area( c1, e1, e4 );
    
    else if ((t1 == 5 && t2 == 3) || (t1 == 3 && t2 == 5)) return Concave_Cone_Area( c3, e3, e6 );
    
    else if ((t1 == 5 && t2 == 2) || (t1 == 2 && t2 == 5))
    {
        P2 i3, j1, j2;
        
        Intersection_Of_Two_Circles( c1, c2, j1, j2 );
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 2) return Concave_Cone_Area( c2, e2, e ) + Concave_Cone_Area( c1, e4, e );
        
        else return Concave_Cone_Area( c2, e5, e ) + Concave_Cone_Area( c1, e1, e );
    }
    
    else if ((t1 == 6 && t2 == 1) || (t1 == 1 && t2 == 6)) return Concave_Cone_Area( c1, e1, e4 );
    
    else if ((t1 == 6 && t2 == 2) || (t1 == 2 && t2 == 6)) return Concave_Cone_Area( c2, e2, e5 );
    
    else if ((t1 == 6 && t2 == 3) || (t1 == 3 && t2 == 6))
    {
        P2 i3, j1, j2;
        
        Intersection_Of_Two_Circles( c1, c3, j1, j2 );
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 3) return Concave_Cone_Area( c3, e3, e ) + Concave_Cone_Area( c1, e4, e );
        
        else return Concave_Cone_Area( c3, e6, e ) + Concave_Cone_Area( c1, e1, e );
    }
    
    else if (t1 == t2)
    {
        if (t1 == 1) return Concave_Cone_Area( c1, e1, e4 );
        
        else if (t1 == 2) return Concave_Cone_Area( c2, e2, e5 );
        
        else return Concave_Cone_Area( c3, e3, e6 );
    }
    
    else if ((t1 == 1 && t2 == 2) || (t1 == 2 && t2 == 1))
    {
        P2 i3, j1, j2;
        
        Intersection_Of_Two_Circles( c1, c2, j1, j2 );
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 1) return Concave_Cone_Area( c1, e1, e ) + Concave_Cone_Area( c2, e5, e );
        
        else return Concave_Cone_Area( c1, e4, e ) + Concave_Cone_Area( c2, e2, e );
    }
    
    else if ((t1 == 1 && t2 == 3) || (t1 == 3 && t2 == 1))
    {
        P2 i3, j1, j2;
        
        Intersection_Of_Two_Circles( c1, c3, j1, j2 );
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 1) return Concave_Cone_Area( c1, e1, e ) + Concave_Cone_Area( c3, e6, e );
        
        else return Concave_Cone_Area( c1, e4, e ) + Concave_Cone_Area( c3, e3, e );
    }
    
    else
    {
        P2 i3, j1, j2;
        
        Intersection_Of_Two_Circles( c2, c3, j1, j2 );
        
        L2 l( i1, i2 );
        
        if (Same_Side( l, j1, v )) i3 = j1;
        else i3 = j2;
        
        Edge e( L2( v, i3 ), v, i3, 0 );
        
        if (t1 == 2) return Concave_Cone_Area( c2, e2, e ) + Concave_Cone_Area( c3, e6, e );
        
        else return Concave_Cone_Area( c2, e5, e ) + Concave_Cone_Area( c3, e3, e );
    }
}

double Three_Circle_Intersection_Interior_Edge_Area ( Circle const& c1, Circle const& c2, Circle const& c3, Edge const& e, Cell const& cell_1, Cell const& cell_2, Cell const& cell_3 )
{
    int index_1 = (e.index + 3) % 4;
    int index_2 = (e.index + 1) % 4;
    
    P2 p1, p2, p3, p4;
    
    p2 = e.startpt;
    p3 = e.endpt;
    
    if (cell_1.edges[index_1].intersection_type != 1 && Norm( cell_1.edges[index_1].i1, c2.c ) < c2.r && Norm( cell_1.edges[index_1].i1, c3.c ) < c3.r) p1 = cell_1.edges[index_1].i1;
    
    else if (cell_2.edges[index_1].intersection_type != 1 && Norm( cell_2.edges[index_1].i1, c1.c ) < c1.r && Norm( cell_2.edges[index_1].i1, c3.c ) < c3.r) p1 = cell_2.edges[index_1].i1;
    
    else if (cell_3.edges[index_1].intersection_type != 1 && Norm( cell_3.edges[index_1].i1, c1.c ) < c1.r && Norm( cell_3.edges[index_1].i1, c2.c ) < c2.r) p1 = cell_3.edges[index_1].i1;
    
    else if (cell_1.edges[index_1].intersection_type != 1 && Norm( cell_1.edges[index_1].i1, c3.c ) < c3.r) p1 = cell_1.edges[index_1].i1;
    
    else p1 = cell_3.edges[index_1].i1;
    
    if (cell_1.edges[index_2].intersection_type != 1 && Norm( cell_1.edges[index_2].i1, c2.c ) < c2.r && Norm( cell_1.edges[index_2].i1, c3.c ) < c3.r) p4 = cell_1.edges[index_2].i1;
    
    else if (cell_2.edges[index_2].intersection_type != 1 && Norm( cell_2.edges[index_2].i1, c1.c ) < c1.r && Norm( cell_2.edges[index_2].i1, c3.c ) < c3.r) p4 = cell_2.edges[index_2].i1;
    
    else if (cell_3.edges[index_2].intersection_type != 1 && Norm( cell_3.edges[index_2].i1, c1.c ) < c1.r && Norm( cell_3.edges[index_2].i1, c2.c ) < c2.r) p4 = cell_3.edges[index_2].i1;
    
    else if (cell_1.edges[index_2].intersection_type != 1 && Norm( cell_1.edges[index_2].i1, c3.c ) < c3.r) p4 = cell_1.edges[index_2].i1;
    
    else p4 = cell_3.edges[index_2].i1;
    
    double triangle_area_1 = Triangle_Area( p1, p2, p3 );
    double triangle_area_2 = Triangle_Area( p1, p3, p4 );
    
    Cell cell_4;
    
    if (e.index == 0) Make_Cell( p1, p4, cell_1.vertices[2], cell_1.vertices[3], cell_4 );
    
    else if (e.index == 1) Make_Cell( cell_1.vertices[0], p1, p4, cell_1.vertices[3], cell_4 );
    
    else if (e.index == 2) Make_Cell( cell_1.vertices[0], cell_1.vertices[1], p1, p4, cell_4 );
    
    else if (e.index == 3) Make_Cell( p4, cell_1.vertices[1], cell_1.vertices[2], p1, cell_4 );
    
    return triangle_area_1 + triangle_area_2 + Three_Circle_Intersection_Area_Within_Cell( cell_4, c1, c2, c3 );
}

double Three_Circle_Intersection_Irregular_Sector_Area ( Circle const& c1, Circle const& c2, Circle const& c3, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4, Edge const& e5, Edge const& e6 )
{
    P2 v, i1, i2;
    
    if (Norm( e1.startpt, c1.c ) < c1.r - tiny_num && Norm( e1.startpt, c2.c ) < c2.r - tiny_num && Norm( e1.startpt, c3.c ) < c3.r - tiny_num)
    {
        v = e1.startpt;
    }
    
    else v = e1.endpt;
    
    int t1, t2;
    
    if (e1.intersection_type != 1 && Norm( e1.i1, c2.c ) < c2.r - tiny_num && Norm( e1.i1, c3.c ) < c3.r - tiny_num)
    {
        i1 = e1.i1;
        t1 = 1;
    }
    
    else if (e2.intersection_type != 1 && Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i1, c3.c ) < c3.r - tiny_num)
    {
        i1 = e2.i1;
        t1 = 2;
    }
    
    else if (e3.intersection_type != 1 && Norm( e3.i1, c1.c ) < c1.r - tiny_num && Norm( e3.i1, c2.c ) < c2.r - tiny_num)
    {
        i1 = e3.i1;
        t1 = 3;
    }
    
    else if (e2.intersection_type != 1 && Norm( e2.i1, c1.c ) < c1.r - tiny_num)
    {
        i1 = e2.i1;
        t1 = 4;
    }
    
    else if (e1.intersection_type != 1 && Norm( e1.i1, c2.c ) < c2.r - tiny_num)
    {
        i1 = e1.i1;
        t1 = 5;
    }
    
    else
    {
        i1 = e1.i1;
        t1 = 6;
    }
    
    if (e4.intersection_type != 1 && Norm( e4.i1, c2.c ) < c2.r - tiny_num && Norm( e4.i1, c3.c ) < c3.r - tiny_num)
    {
        i2 = e4.i1;
        t2 = 1;
    }
    
    else if (e5.intersection_type != 1 && Norm( e5.i1, c1.c ) < c1.r - tiny_num && Norm( e5.i1, c3.c ) < c3.r - tiny_num)
    {
        i2 = e5.i1;
        t2 = 2;
    }
    
    else if (e6.intersection_type != 1 && Norm( e6.i1, c1.c ) < c1.r - tiny_num && Norm( e6.i1, c2.c ) < c2.r - tiny_num)
    {
        i2 = e6.i1;
        t2 = 3;
    }
    
    else if (e5.intersection_type != 1 && Norm( e5.i1, c1.c ) < c1.r - tiny_num)
    {
        i2 = e5.i1;
        t2 = 4;
    }
    
    else if (e4.intersection_type != 1 && Norm( e4.i1, c2.c ) < c2.r - tiny_num)
    {
        i2 = e4.i1;
        t2 = 5;
    }
    
    else
    {
        i2 = e4.i1;
        t2 = 6;
    }
    
    P2 j1, j2, j3;
    
    Non_Trivial_Three_Circle_Intersection_Pts( c1, c2, c3, j1, j2, j3 );
    
    double intersection_area = Non_Trivial_Three_Circle_Intersection_Area( c1, c2, c3 );
    
    L2 l( i1, i2 );
    
    if ((t1 == 4 && t2 == 5) || (t1 == 5 && t2 == 4))
    {
        double area = Irregular_Sector_Area( c3, e3, e6 );
        
        if (Same_Side( l, j3, v )) return area;
        
        else return intersection_area - c3.area + area;
    }
    
    else if ((t1 == 4 && t2 == 6) || (t1 == 6 && t2 == 4))
    {
        double area = Irregular_Sector_Area( c2, e2, e5 );
        
        if (Same_Side( l, j2, v )) return area;
        
        else return intersection_area - c2.area + area;
    }
    
    else if ((t1 == 5 && t2 == 6) || (t1 == 6 && t2 == 5))
    {
        double area = Irregular_Sector_Area( c1, e1, e4 );
        
        if (Same_Side( l, j1, v )) return area;
        
        else return intersection_area - c1.area + area;
    }
    
    else if ((t1 == 4 && t2 == 2) || (t1 == 2 && t2 == 4))
    {
        double area = Irregular_Sector_Area( c2, e2, e5 );
        
        if (Same_Side( l, j2, v )) return area;
        
        else return intersection_area - c2.area + area;
    }
    
    else if ((t1 == 4 && t2 == 3) || (t1 == 3 && t2 == 4))
    {
        double area = Irregular_Sector_Area( c3, e3, e6 );
        
        if (Same_Side( l, j3, v )) return area;
        
        else return intersection_area - c3.area + area;
    }
    
    else if ((t1 == 4 && t2 == 1) || (t1 == 1 && t2 == 4))
    {
        double area = Two_Circle_Intersection_Irregular_Sector_Area( c1, c2, e1, e2, e4, e5 );
        
        if (!Same_Side( l, j3, v )) return area;
        
        else return intersection_area - Two_Circle_Intersection_Area( c1, c2 ) + area;
    }
    
    else if ((t1 == 5 && t2 == 1) || (t1 == 1 && t2 == 5))
    {
        double area = Irregular_Sector_Area( c1, e1, e4 );
        
        if (Same_Side( l, j1, v )) return area;
        
        else return intersection_area - c1.area + area;
    }
    
    else if ((t1 == 5 && t2 == 3) || (t1 == 3 && t2 == 5))
    {
        double area = Irregular_Sector_Area( c3, e3, e6 );
        
        if (Same_Side( l, j3, v )) return area;
        
        else return intersection_area - c3.area + area;
    }
    
    else if ((t1 == 5 && t2 == 2) || (t1 == 2 && t2 == 5))
    {
        double area = Two_Circle_Intersection_Irregular_Sector_Area( c2, c3, e1, e2, e4, e5 );
        
        if (!Same_Side( l, j1, v )) return area;
        
        else return intersection_area - Two_Circle_Intersection_Area( c1, c2 ) + area;
    }
    
    else if ((t1 == 6 && t2 == 1) || (t1 == 1 && t2 == 6))
    {
        double area = Irregular_Sector_Area( c1, e1, e4 );
        
        if (Same_Side( l, j1, v )) return area;
        
        else return intersection_area - c1.area + area;
    }
    
    else if ((t1 == 6 && t2 == 2) || (t1 == 2 && t2 == 6))
    {
        double area = Irregular_Sector_Area( c2, e2, e5 );
        
        if (Same_Side( l, j2, v )) return area;
        
        else return intersection_area - c2.area + area;
    }
    
    else if ((t1 == 6 && t2 == 3) || (t1 == 3 && t2 == 6))
    {
        double area = Two_Circle_Intersection_Irregular_Sector_Area( c1, c3, e1, e3, e4, e6 );
        
        if (!Same_Side( l, j2, v )) return area;
        
        else return intersection_area - Two_Circle_Intersection_Area( c1, c3 ) + area;
    }
    
    else if (t1 == t2)
    {
        if (t1 == 1)
        {
            double area = Irregular_Sector_Area( c1, e1, e4 );
            
            if (Same_Side( l, j1, v )) return area;
            
            else return intersection_area - c1.area + area;
        }
        
        else if (t1 == 2)
        {
            double area = Irregular_Sector_Area( c2, e2, e5 );
            
            if (Same_Side( l, j2, v )) return area;
            
            else return intersection_area - c2.area + area;
        }
        
        else
        {
            double area = Irregular_Sector_Area( c3, e3, e6 );
            
            if (Same_Side( l, j3, v )) return area;
            
            else return intersection_area - c3.area + area;
        }
    }
    
    else if ((t1 == 1 && t2 == 2) || (t1 == 2 && t2 == 1))
    {
        double area = Two_Circle_Intersection_Irregular_Sector_Area( c1, c2, e1, e2, e4, e5 );
        
        if (!Same_Side( l, j3, v )) return area;
        
        else return intersection_area - Two_Circle_Intersection_Area( c1, c2 ) + area;
    }
    
    else if ((t1 == 1 && t2 == 3) || (t1 == 3 && t2 == 1))
    {
        double area = Two_Circle_Intersection_Irregular_Sector_Area( c1, c3, e1, e3, e4, e6 );
        
        if (!Same_Side( l, j2, v )) return area;
        
        else return intersection_area - Two_Circle_Intersection_Area( c1, c3 ) + area;
    }
    
    else
    {
        double area = Two_Circle_Intersection_Irregular_Sector_Area( c2, c3, e2, e3, e5, e6 );
        
        if (!Same_Side( l, j1, v )) return area;
        
        else return intersection_area - Two_Circle_Intersection_Area( c2, c3 ) + area;
    }
}

double Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( Circle const& c1, Circle const& c2, Circle const& c3, Edge const& e1, Edge const& e2, Edge const& e3, Cell const& cell )
{
    double intersection_area = Non_Trivial_Three_Circle_Intersection_Area( c1, c2, c3 );
    
    P2 i1, i2, i3;
    
    Non_Trivial_Three_Circle_Intersection_Pts( c1, c2, c3, i1, i2, i3 );
    
    if (squared_distance( e1.line, i1 ) < tiny_num && squared_distance( e1.line, i2 ) < tiny_num)
    {
        if (e3.intersection_type == 3 || e3.intersection_type == 6 || e3.intersection_type == 7)
        {
            double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
            
            if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
            
            else return intersection_area - c3.area + area;
        }
    }
    
    else if (squared_distance( e1.line, i1 ) < tiny_num && squared_distance( e1.line, i3 ) < tiny_num)
    {
        if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
        {
            double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
            
            if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
            
            else return intersection_area - c2.area + area;
        }
    }
    
    else if (squared_distance( e1.line, i2 ) < tiny_num && squared_distance( e1.line, i3 ) < tiny_num)
    {
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            double area = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
            
            if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
            
            else return intersection_area - c1.area + area;
        }
    }
    
    else if (squared_distance( e1.line, i1 ) < tiny_num)
    {
        if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
        {
            if (Norm( e2.i1, c3.c ) < c3.r - tiny_num || Norm( e2.i2, c3.c ) < c3.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
        
        if (e3.intersection_type == 3 || e3.intersection_type == 6 || e3.intersection_type == 7)
        {
            if (Norm( e3.i1, c2.c ) < c2.r - tiny_num || Norm( e3.i2, c2.c ) < c2.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - c3.area + area;
            }
        }
        
        if (e1.intersection_type == 2 || e1.intersection_type == 3 || e1.intersection_type == 5 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            if ((Norm( e1.i1, c2.c ) < c2.r - tiny_num && Norm( e1.i1, c3.c ) < c3.r - tiny_num) || (Norm( e1.i2, c2.c ) < c2.r - tiny_num && Norm( e1.i2, c3.c ) < c3.r - tiny_num))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, e1, e2, cell );
                
                if (!Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - Two_Circle_Intersection_Area( c1, c2 ) + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i2 ) < tiny_num)
    {
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            if (Norm( e1.i1, c3.c ) < c3.r - tiny_num || Norm( e1.i2, c3.c ) < c3.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c1.area + area;
            }
        }
        
        if (e3.intersection_type == 3 || e3.intersection_type == 6 || e3.intersection_type == 7)
        {
            if (Norm( e3.i1, c1.c ) < c1.r - tiny_num || Norm( e3.i2, c1.c ) < c1.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - c3.area + area;
            }
        }
        
        if (e2.intersection_type == 2 || e2.intersection_type == 3 || e2.intersection_type == 5 || e2.intersection_type == 6 || e2.intersection_type == 7)
        {
            if ((Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i1, c3.c ) < c3.r - tiny_num) || (Norm( e2.i2, c1.c ) < c1.r - tiny_num && Norm( e2.i2, c3.c ) < c3.r - tiny_num))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c2, c3, e2, e3, cell );
                
                if (!Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - Two_Circle_Intersection_Area( c1, c2 ) + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i3 ) < tiny_num)
    {
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            if (Norm( e1.i1, c2.c ) < c2.r - tiny_num || Norm( e1.i2, c2.c ) < c2.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c1.area + area;
            }
        }
        
        if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
        {
            if (Norm( e2.i1, c1.c ) < c1.r - tiny_num || Norm( e2.i2, c1.c ) < c1.r - tiny_num)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
        
        if (e3.intersection_type == 2 || e3.intersection_type == 3 || e3.intersection_type == 5 || e3.intersection_type == 6 || e3.intersection_type == 7)
        {
            if ((Norm( e3.i1, c1.c ) < c1.r - tiny_num && Norm( e3.i1, c2.c ) < c2.r - tiny_num) || (Norm( e3.i2, c1.c ) < c1.r - tiny_num && Norm( e3.i2, c2.c ) < c2.r - tiny_num))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c3, e1, e3, cell );
                
                if (!Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - Two_Circle_Intersection_Area( c1, c3 ) + area;
            }
        }
    }
    
    else
    {
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            if (Norm( e1.i1, c2.c ) < c2.r && Norm( e1.i1, c3.c ) < c3.r && Norm( e1.i2, c2.c ) < c2.r && Norm( e1.i2, c3.c ) < c3.r)
            {
                double area = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c1.area + area;
            }
        }
        
        if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
        {
            if (Norm( e2.i1, c1.c ) < c1.r && Norm( e2.i1, c3.c ) < c3.r && Norm( e2.i2, c1.c ) < c1.r && Norm( e2.i2, c3.c ) < c3.r)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
                
                if (Correct_Side_Of_Cell( cell, e2, i2 )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
        
        if (e3.intersection_type == 3 || e3.intersection_type == 6 || e3.intersection_type == 7)
        {
            if (Norm( e3.i1, c1.c ) < c1.r && Norm( e3.i1, c2.c ) < c2.r && Norm( e3.i2, c1.c ) < c1.r && Norm( e3.i2, c2.c ) < c2.r)
            {
                double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e3, i3 )) return area;
                
                else return intersection_area - c3.area + area;
            }
        }
        
        if ((e1.intersection_type == 2 || e1.intersection_type == 3 || e1.intersection_type == 5 || e1.intersection_type == 6 || e1.intersection_type == 7) && (e2.intersection_type == 2 || e2.intersection_type == 3 || e2.intersection_type == 5 || e2.intersection_type == 6 || e2.intersection_type == 7))
        {
            if (((Norm( e1.i1, c2.c ) < c2.r - tiny_num && Norm( e1.i1, c3.c ) < c3.r - tiny_num) || (Norm( e1.i2, c2.c ) < c2.r - tiny_num && Norm( e1.i2, c3.c ) < c3.r - tiny_num)) && ((Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i1, c3.c ) < c3.r - tiny_num) || (Norm( e2.i2, c1.c ) < c1.r - tiny_num && Norm( e2.i2, c3.c ) < c3.r - tiny_num)))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, e1, e2, cell );
                
                if (!Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - Two_Circle_Intersection_Area( c1, c2 ) + area;
            }
        }
        
        if ((e1.intersection_type == 2 || e1.intersection_type == 3 || e1.intersection_type == 5 || e1.intersection_type == 6 || e1.intersection_type == 7) && (e3.intersection_type == 2 || e3.intersection_type == 3 || e3.intersection_type == 5 || e3.intersection_type == 6 || e3.intersection_type == 7))
        {
            if (((Norm( e1.i1, c2.c ) < c2.r - tiny_num && Norm( e1.i1, c3.c ) < c3.r - tiny_num) || (Norm( e1.i2, c2.c ) < c2.r - tiny_num && Norm( e1.i2, c3.c ) < c3.r - tiny_num)) && ((Norm( e3.i1, c1.c ) < c1.r - tiny_num && Norm( e3.i1, c2.c ) < c2.r - tiny_num) || (Norm( e3.i2, c1.c ) < c1.r - tiny_num && Norm( e3.i2, c2.c ) < c2.r - tiny_num)))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c3, e1, e3, cell );
                
                if (!Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - Two_Circle_Intersection_Area( c1, c3 ) + area;
            }
        }
        
        if ((e2.intersection_type == 2 || e2.intersection_type == 3 || e2.intersection_type == 5 || e2.intersection_type == 6 || e2.intersection_type == 7) && (e3.intersection_type == 2 || e3.intersection_type == 3 || e3.intersection_type == 5 || e3.intersection_type == 6 || e3.intersection_type == 7))
        {
            if (((Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i1, c3.c ) < c3.r - tiny_num) || (Norm( e2.i2, c1.c ) < c1.r - tiny_num && Norm( e2.i2, c3.c ) < c3.r - tiny_num)) && ((Norm( e3.i1, c1.c ) < c1.r - tiny_num && Norm( e3.i1, c2.c ) < c2.r - tiny_num) || (Norm( e3.i2, c1.c ) < c1.r - tiny_num && Norm( e3.i2, c2.c ) < c2.r - tiny_num)))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c2, c3, e2, e3, cell );
                
                if (!Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - Two_Circle_Intersection_Area( c2, c3 ) + area;
            }
        }
    }
    
    return 0;
}

double Non_Trivial_Three_Circle_Intersection_Area_Within_Cell ( Cell& cell, Circle const& c1, Circle const& c2, Circle const& c3 )
{
    double intersection_area = Non_Trivial_Three_Circle_Intersection_Area( c1, c2, c3 );
    
    P2 i1, i2, i3;
    
    Non_Trivial_Three_Circle_Intersection_Pts( c1, c2, c3, i1, i2, i3 );
    
    Cell cell_1 = cell, cell_2 = cell, cell_3 = cell;
    
    bool cell_c1_intersection = Cell_Circle_Intersections( cell_1, c1 );
    bool cell_c2_intersection = Cell_Circle_Intersections( cell_2, c2 );
    bool cell_c3_intersection = Cell_Circle_Intersections( cell_3, c3 );
    
    int num_vertices_within_c1 = Num_Vertices_Within_Circle( cell, c1 );
    int num_vertices_within_c2 = Num_Vertices_Within_Circle( cell, c2 );
    int num_vertices_within_c3 = Num_Vertices_Within_Circle( cell, c3 );
    
    bool c1_centre_within_cell = Pt_Within_Convex_Hull( cell, c1.c );
    bool c2_centre_within_cell = Pt_Within_Convex_Hull( cell, c2.c );
    bool c3_centre_within_cell = Pt_Within_Convex_Hull( cell, c3.c );
    
    if (!cell_c1_intersection && !cell_c2_intersection && !cell_c3_intersection)
    {
        if (num_vertices_within_c1 == 4 && num_vertices_within_c2 == 4 && num_vertices_within_c3 == 4) return cell.area;
        
        else if (num_vertices_within_c1 == 4 || num_vertices_within_c2 == 4 || num_vertices_within_c3 == 4) return 0;
        
        else if (c1_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!cell_c1_intersection)
    {
        if (num_vertices_within_c1 == 4) return Two_Circle_Intersection_Area_Within_Cell( cell, c2, c3 );
        
        else if (c1_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!cell_c2_intersection)
    {
        if (num_vertices_within_c2 == 4) return Two_Circle_Intersection_Area_Within_Cell( cell, c1, c3 );
        
        else if (c2_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!cell_c3_intersection)
    {
        if (num_vertices_within_c3 == 4) return Two_Circle_Intersection_Area_Within_Cell( cell, c1, c2 );
        
        else if (c3_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else
    {
        int num_vertices_within_all_circles = 0;
        
        for (int counter = 0; counter < cell.vertices.size(); ++counter)
        {
            if (Norm( c1.c, cell.vertices[counter] ) < c1.r - tiny_num && Norm( c2.c, cell.vertices[counter] ) < c2.r - tiny_num && Norm( c3.c, cell.vertices[counter] ) < c3.r - tiny_num) ++num_vertices_within_all_circles;
        }
        
        if (num_vertices_within_all_circles == 0)
        {
            double area = intersection_area;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                area -= Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, c3, cell_1.edges[counter], cell_2.edges[counter], cell_3.edges[counter], cell );
            }
            
            if (area == intersection_area)
            {
                V2 v1 = i1 - ORIGIN, v2 = i2 - ORIGIN;
                
                P2 p = ORIGIN + 0.5 * v1 + 0.5 * v2;
                
                if (Pt_Within_Convex_Hull( cell, p )) return area;
                
                else return 0;
            }
            
            else return area;
        }
        
        else if (num_vertices_within_all_circles == 1)
        {
            vector<int> key_edges;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if ((Norm( cell_1.edges[counter].startpt, c1.c) < c1.r - tiny_num && Norm( cell_1.edges[counter].startpt, c2.c) < c2.r - tiny_num && Norm( cell_1.edges[counter].startpt, c3.c) < c3.r - tiny_num) || (Norm( cell_1.edges[counter].endpt, c1.c) < c1.r - tiny_num && Norm( cell_1.edges[counter].endpt, c2.c) < c2.r - tiny_num && Norm( cell_1.edges[counter].endpt, c3.c) < c3.r - tiny_num))
                {
                    key_edges.push_back( counter );
                }
            }
            
            double area = Three_Circle_Intersection_Irregular_Sector_Area( c1, c2, c3, cell_1.edges[key_edges[0]], cell_2.edges[key_edges[0]], cell_3.edges[key_edges[0]], cell_1.edges[key_edges[1]], cell_2.edges[key_edges[1]], cell_3.edges[key_edges[1]] );
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                area -= Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, c3, cell_1.edges[counter], cell_2.edges[counter], cell_3.edges[counter], cell );
            }
            
            return area;
        }
        
        else if (num_vertices_within_all_circles == 2)
        {
            bool type_1_edge = false;
            Edge key_edge;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if (cell_1.edges[counter].intersection_type == 1 && cell_2.edges[counter].intersection_type == 1 && cell_3.edges[counter].intersection_type == 1)
                {
                    key_edge = cell.edges[counter];
                    type_1_edge = true;
                }
            }
            
            if (type_1_edge)
            {
                return Three_Circle_Intersection_Interior_Edge_Area( c1, c2, c3, key_edge, cell_1, cell_2, cell_3 );
            }
            
            else
            {
                double area_1, area_2;
                
                if (Norm( cell.edges[0].startpt, c1.c ) < c1.r - tiny_num && Norm( cell.edges[0].startpt, c2.c ) < c2.r - tiny_num && Norm( cell.edges[0].startpt, c3.c ) < c3.r - tiny_num)
                {
                    area_1 = Three_Circle_Intersection_Irregular_Sector_Area( c1, c2, c3, cell_1.edges[0], cell_2.edges[0], cell_3.edges[0], cell_1.edges[3], cell_2.edges[3], cell_3.edges[3] );
                    
                    area_2 = Three_Circle_Intersection_Irregular_Sector_Area( c1, c2, c3, cell_1.edges[1], cell_2.edges[1], cell_3.edges[1], cell_1.edges[2], cell_2.edges[2], cell_3.edges[2] );
                }
                
                else
                {
                    area_1 = Three_Circle_Intersection_Irregular_Sector_Area( c1, c2, c3, cell_1.edges[0], cell_2.edges[0], cell_3.edges[0], cell_1.edges[1], cell_2.edges[1], cell_3.edges[1] );
                    
                    area_2 = Three_Circle_Intersection_Irregular_Sector_Area( c1, c2, c3, cell_1.edges[2], cell_2.edges[2], cell_3.edges[2], cell_1.edges[3], cell_2.edges[3], cell_3.edges[3] );
                }
                
                return area_1 + area_2 - intersection_area;
            }
        }
        
        else
        {
            vector<int> key_edges;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                if (!(Norm( cell.edges[counter].startpt, c1.c ) < c1.r + tiny_num && Norm( cell.edges[counter].startpt, c2.c ) < c2.r + tiny_num && Norm( cell.edges[counter].startpt, c3.c ) < c3.r + tiny_num) || !(Norm( cell.edges[counter].endpt, c1.c ) < c1.r + tiny_num && Norm( cell.edges[counter].endpt, c2.c ) < c2.r + tiny_num && Norm( cell.edges[counter].endpt, c3.c ) < c3.r + tiny_num))
                {
                    key_edges.push_back( counter );
                }
            }
            
            if (key_edges.size() == 0) return cell.area;
            
            else
            {
                return cell.area - Three_Circle_Intersection_Concave_Cone_Area( c1, c2, c3, cell_1.edges[key_edges[0]], cell_2.edges[key_edges[0]], cell_3.edges[key_edges[0]], cell_1.edges[key_edges[1]], cell_2.edges[key_edges[1]], cell_3.edges[key_edges[1]] );
            }
        }
    }
}

double Non_Inclusion_Three_Circle_Intersection_Area_Within_Cell ( Cell& cell, Circle const& c1, Circle const& c2, Circle const& c3 )
{
    P2 p1, p2;
    
    Intersection_Of_Two_Circles( c1, c2, p1, p2 );
    
    int a = 0, b = 0, c = 0;
    
    if (Norm( c3.c, p1 ) < c3.r + tiny_num) ++a;
    if (Norm( c3.c, p2 ) < c3.r + tiny_num) ++a;
    
    Intersection_Of_Two_Circles( c1, c3, p1, p2 );
    
    if (Norm( c2.c, p1 ) < c2.r + tiny_num) ++b;
    if (Norm( c2.c, p2 ) < c2.r + tiny_num) ++b;
    
    Intersection_Of_Two_Circles( c2, c3, p1, p2 );
    
    if (Norm( c1.c, p1 ) < c1.r + tiny_num) ++c;
    if (Norm( c1.c, p2 ) < c1.r + tiny_num) ++c;
    
    if (a == 1 && b == 1 && c == 1) return Non_Trivial_Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c3 );
    
    else if (a == 0 && b == 0 && c == 0) return 0;
    
    else
    {
        int d = 0;
        
        if (a == 2) ++d;
        if (b == 2) ++d;
        if (c == 2) ++d;
        
        if (d == 1)
        {
            if (a == 2) return Two_Circle_Intersection_Area_Within_Cell( cell, c1, c2 );
            else if (b == 2) return Two_Circle_Intersection_Area_Within_Cell( cell, c1, c3 );
            else return Two_Circle_Intersection_Area_Within_Cell( cell, c2, c3 );
        }
        
        else
        {
            double a, b;
            
            a = Two_Circle_Intersection_Area_Within_Cell( cell, c1, c2 );
            b = Two_Circle_Intersection_Area_Within_Cell( cell, c1, c3 );
            
            return a + b - Circle_Area_Within_Cell( cell, c1 );
        }
    }
}

double Three_Circle_Intersection_Area_Within_Cell ( Cell& cell, Circle const& c1, Circle const& c2, Circle const& c3 )
{
    double area_1, area_2, area_3;
    
    area_1 = Two_Circle_Intersection_Area( c2, c3 );
    area_2 = Two_Circle_Intersection_Area( c1, c3 );
    area_3 = Two_Circle_Intersection_Area( c1, c2 );
    
    if (area_1 == 0 || area_2 == 0 || area_3 == 0) return 0;
    
    else
    {
        vector<Circle> circles;
        
        circles.push_back( c1 );
        circles.push_back( c2 );
        circles.push_back( c3 );
        
        Order_Circles( circles );
        
        bool inside0_1 = false, inside0_2 = false, inside1_2 = false;
        
        if (Norm( circles[0].c, circles[1].c ) < circles[1].r - circles[0].r ) inside0_1 = true;
        if (Norm( circles[0].c, circles[2].c ) < circles[2].r - circles[0].r ) inside0_2 = true;
        if (Norm( circles[1].c, circles[2].c ) < circles[2].r - circles[1].r ) inside1_2 = true;
        
        if (inside0_1 && inside0_2 && inside1_2) return circles[0].area;
        
        else if (!inside0_1 && inside0_2 && inside1_2) return Two_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[1] );
        
        else if (inside0_1 && inside0_2 && !inside1_2) return Circle_Area_Within_Cell( cell, circles[0] );
        
        else if (inside0_1 && !inside0_2 && !inside1_2) return Two_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[2] );
        
        else if (!inside0_1 && inside0_2 && !inside1_2) return Two_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[1] );
        
        else if (!inside0_1 && !inside0_2 && inside1_2) return Two_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[1] );
        
        else
        {
            return Non_Inclusion_Three_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[1], circles[2] );
        }
    }
}

double Four_Circle_Intersection_Area_Excluded_By_Exterior_Edge ( Circle const& c1, Circle const& c2, Circle const& c3, Circle const& c4, Edge const& e1, Edge const& e2, Edge const& e3, Edge const& e4, Cell const& cell )
{
    double intersection_area = Non_Trivial_Four_Circle_Intersection_Area( c1, c2, c3, c4 );
    
    P2 i1, i2, i3, i4;
    vector<int> arc_order;
    
    Non_Trivial_Four_Circle_Intersection_Pts( c1, c2, c3, c4, i1, i2, i3, i4, arc_order );
    
    if (squared_distance( e1.line, i1 ) < tiny_num && squared_distance( e1.line, i2 ) < tiny_num)
    {
        if (e1.intersection_type == 3 || e1.intersection_type == 6 || e1.intersection_type == 7)
        {
            double area = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
            
            if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
            
            else return intersection_area - c1.area + area;
        }
    }
    
    else if (squared_distance( e1.line, i1 ) < tiny_num && squared_distance( e1.line, i3 ) < tiny_num)
    {
        double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, c3, e1, e2, e3, cell );
        
        if (area > tiny_num)
        {
            if (arc_order[1] == 4)
            {
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c1, c2, c3 ) + area;
            }
            
            else
            {
                if (Correct_Side_Of_Cell( cell, e1, i4 )) return area;
                
                else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c1, c2, c3 ) + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i1 ) < tiny_num && squared_distance( e1.line, i4 ) < tiny_num)
    {
        if (arc_order[3] == 2)
        {
            if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
        
        else
        {
            if (e3.intersection_type == 3 || e3.intersection_type == 6 || e3.intersection_type == 7)
            {
                double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c3.area + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i2 ) < tiny_num && squared_distance( e1.line, i3 ) < tiny_num)
    {
        if (arc_order[1] == 3)
        {
            if (e3.intersection_type == 3 || e3.intersection_type == 6 || e3.intersection_type == 7)
            {
                double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c3.area + area;
            }
        }
        
        else
        {
            if (e4.intersection_type == 3 || e4.intersection_type == 6 || e4.intersection_type == 7)
            {
                double area = Area_Excluded_By_Exterior_Edge( c4, e4, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c4.area + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i2 ) < tiny_num && squared_distance( e1.line, i4 ) < tiny_num)
    {
        double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, c3, e1, e2, e3, cell );
        
        if (area > tiny_num)
        {
            if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
            
            else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c1, c2, c3 ) + area;
        }
    }
    
    else if (squared_distance( e1.line, i3 ) < tiny_num && squared_distance( e1.line, i4 ) < tiny_num)
    {
        if (arc_order[2] == 2)
        {
            if (e2.intersection_type == 3 || e2.intersection_type == 6 || e2.intersection_type == 7)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c2.area + area;
            }
        }
        
        else if (arc_order[2] == 3)
        {
            if (e3.intersection_type == 3 || e3.intersection_type == 6 || e3.intersection_type == 7)
            {
                double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c3.area + area;
            }
        }
        
        else
        {
            if (e4.intersection_type == 3 || e4.intersection_type == 6 || e4.intersection_type == 7)
            {
                double area = Area_Excluded_By_Exterior_Edge( c4, e4, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                
                else return intersection_area - c4.area + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i1 ) < tiny_num)
    {
        if (e4.intersection_type > 1)
        {
            if ((Norm( e4.i1, c1.c ) < c1.r - tiny_num && Norm( e4.i1, c2.c ) < c2.r - tiny_num && Norm( e4.i1, c3.c ) < c3.r - tiny_num) || (Norm( e4.i2, c1.c ) < c1.r - tiny_num && Norm( e4.i2, c2.c ) < c2.r - tiny_num && Norm( e4.i2, c3.c ) < c3.r - tiny_num))
            {
                if (arc_order[3] == 2)
                {
                    double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, c4, e1, e2, e4, cell );
                    
                    if (area > tiny_num)
                    {
                        if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                        
                        else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c1, c2, c4 ) + area;
                    }
                }
                
                else
                {
                    double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c3, c4, e1, e3, e4, cell );
                    
                    if (area > tiny_num)
                    {
                        if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                        
                        else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c1, c3, c4 ) + area;
                    }
                }
            }
        }
        
        else
        {
            double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, c3, e1, e2, e3, cell );
            
            if (area > tiny_num)
            {
                if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c1, c2, c3 ) + area;
            }
        }
    }
    
    else if (squared_distance( e1.line, i2 ) < tiny_num)
    {
        if (arc_order[1] == 4)
        {
            if (e2.intersection_type > 1)
            {
                if ((Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i1, c3.c ) < c3.r - tiny_num && Norm( e2.i1, c4.c ) < c4.r - tiny_num) || (Norm( e2.i2, c1.c ) < c1.r - tiny_num && Norm( e2.i2, c3.c ) < c3.r - tiny_num && Norm( e2.i2, c4.c ) < c4.r - tiny_num))
                {
                    double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, c4, e1, e2, e4, cell );
                    
                    if (area > tiny_num)
                    {
                        if (Correct_Side_Of_Cell( cell, e1, i4 )) return area;
                        
                        else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c1, c2, c4 ) + area;
                    }
                }
            }
            
            else
            {
                double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c3, c4, e1, e3, e4, cell );
                
                if (area > tiny_num)
                {
                    if (Correct_Side_Of_Cell( cell, e1, i4 )) return area;
                    
                    else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c1, c3, c4 ) + area;
                }
            }
        }
        
        else
        {
            if (e4.intersection_type > 1)
            {
                if ((Norm( e4.i1, c1.c ) < c1.r - tiny_num && Norm( e4.i1, c2.c ) < c2.r - tiny_num && Norm( e4.i1, c3.c ) < c3.r - tiny_num) || (Norm( e4.i2, c1.c ) < c1.r - tiny_num && Norm( e4.i2, c2.c ) < c2.r - tiny_num && Norm( e4.i2, c3.c ) < c3.r - tiny_num))
                {
                    double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c3, c4, e1, e3, e4, cell );
                    
                    if (area > tiny_num)
                    {
                        if (Correct_Side_Of_Cell( cell, e1, i4 )) return area;
                        
                        else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c1, c3, c4 ) + area;
                    }
                }
            }
            
            else
            {
                double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, c3, e1, e2, e3, cell );
                
                if (area > tiny_num)
                {
                    if (Correct_Side_Of_Cell( cell, e1, i4 )) return area;
                    
                    else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c1, c2, c3 ) + area;
                }
            }
        }
    }
    
    else if (squared_distance( e1.line, i3 ) < tiny_num)
    {
        if (arc_order[3] == 2)
        {
            if (e2.intersection_type > 1)
            {
                if ((Norm( e2.i1, c1.c ) < c1.r - tiny_num && Norm( e2.i1, c3.c ) < c3.r - tiny_num && Norm( e2.i1, c4.c ) < c4.r - tiny_num) || (Norm( e2.i2, c1.c ) < c1.r - tiny_num && Norm( e2.i2, c3.c ) < c3.r - tiny_num && Norm( e2.i2, c4.c ) < c4.r - tiny_num))
                {
                    double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c2, c3, c4, e2, e3, e4, cell );
                    
                    if (area > tiny_num)
                    {
                        if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                        
                        else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c2, c3, c4 ) + area;
                    }
                }
            }
            
            else
            {
                double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c3, c4, e1, e3, e4, cell );
                
                if (area > tiny_num)
                {
                    if (Correct_Side_Of_Cell( cell, e1, i4 )) return area;
                    
                    else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c1, c3, c4 ) + area;
                }
            }
        }
        
        else
        {
            if (e3.intersection_type > 1)
            {
                if ((Norm( e3.i1, c1.c ) < c1.r - tiny_num && Norm( e3.i1, c2.c ) < c2.r - tiny_num && Norm( e3.i1, c4.c ) < c4.r - tiny_num) || (Norm( e4.i2, c1.c ) < c1.r - tiny_num && Norm( e4.i2, c2.c ) < c2.r - tiny_num && Norm( e4.i2, c4.c ) < c4.r - tiny_num))
                {
                    double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c2, c3, c4, e2, e3, e4, cell );
                    
                    if (area > tiny_num)
                    {
                        if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                        
                        else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c2, c3, c4 ) + area;
                    }
                }
            }
            
            else
            {
                double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, c4, e1, e2, e4, cell );
                
                if (area > tiny_num)
                {
                    if (Correct_Side_Of_Cell( cell, e1, i4 )) return area;
                    
                    else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c1, c2, c4 ) + area;
                }
            }
        }
    }
    
    else if (squared_distance( e1.line, i4 ) < tiny_num)
    {
        if (arc_order[1] == 3)
        {
            if (e3.intersection_type > 1)
            {
                if ((Norm( e3.i1, c1.c ) < c1.r - tiny_num && Norm( e3.i1, c2.c ) < c2.r - tiny_num && Norm( e3.i1, c4.c ) < c4.r - tiny_num) || (Norm( e3.i2, c1.c ) < c1.r - tiny_num && Norm( e3.i2, c2.c ) < c2.r - tiny_num && Norm( e3.i2, c4.c ) < c4.r - tiny_num))
                {
                    double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c2, c3, c4, e2, e3, e4, cell );
                    
                    if (area > tiny_num)
                    {
                        if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                        
                        else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c2, c3, c4 ) + area;
                    }
                }
            }
            
            else
            {
                double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, c4, e1, e2, e4, cell );
                
                if (area > tiny_num)
                {
                    if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                    
                    else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c1, c2, c4 ) + area;
                }
            }
        }
        
        else
        {
            if ((Norm( e4.i1, c1.c ) < c1.r - tiny_num && Norm( e4.i1, c2.c ) < c2.r - tiny_num && Norm( e4.i1, c3.c ) < c3.r - tiny_num) || (Norm( e4.i2, c1.c ) < c1.r - tiny_num && Norm( e4.i2, c2.c ) < c2.r - tiny_num && Norm( e4.i2, c3.c ) < c3.r - tiny_num))
            {
                double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c2, c3, c4, e2, e3, e4, cell );
                
                if (area > tiny_num)
                {
                    if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                    
                    else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c2, c3, c4 ) + area;
                }
            }
            
            else
            {
                double area = Three_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, c3, e1, e2, e3, cell );
                
                if (area > tiny_num)
                {
                    if (Correct_Side_Of_Cell( cell, e1, i2 )) return area;
                    
                    else return intersection_area - Non_Trivial_Three_Circle_Intersection_Area( c1, c2, c3 ) + area;
                }
            }
        }
    }
    
    else
    {
        vector<int> ints;
        
        if (e1.intersection_type > 1 && ((Norm( e1.i1, c2.c ) < c2.r && Norm( e1.i1, c3.c ) < c3.r && Norm( e1.i1, c4.c ) < c4.r) || (Norm( e1.i2, c2.c ) < c2.r && Norm( e1.i2, c3.c ) < c3.r && Norm( e1.i2, c4.c ) < c4.r)))
        {
            ints.push_back( 1 );
        }
        
        if (e2.intersection_type > 1 && ((Norm( e2.i1, c1.c ) < c1.r && Norm( e2.i1, c3.c ) < c3.r && Norm( e2.i1, c4.c ) < c4.r) || (Norm( e2.i2, c1.c ) < c1.r && Norm( e2.i2, c3.c ) < c3.r && Norm( e2.i2, c4.c ) < c4.r)))
        {
            ints.push_back( 2 );
        }
        
        if (e3.intersection_type > 1 && ((Norm( e3.i1, c1.c ) < c1.r && Norm( e3.i1, c2.c ) < c2.r && Norm( e3.i1, c4.c ) < c4.r) || (Norm( e3.i2, c1.c ) < c1.r && Norm( e3.i2, c2.c ) < c2.r && Norm( e3.i2, c4.c ) < c4.r)))
        {
            ints.push_back( 3 );
        }
        
        if (e4.intersection_type > 1 && ((Norm( e4.i1, c1.c ) < c1.r && Norm( e4.i1, c2.c ) < c2.r && Norm( e4.i1, c3.c ) < c3.r) || (Norm( e4.i2, c1.c ) < c1.r && Norm( e4.i2, c2.c ) < c2.r && Norm( e4.i2, c3.c ) < c3.r)))
        {
            ints.push_back( 4 );
        }
        
        if (ints.size() == 0) return 0;
        
        else if (ints.size() == 1)
        {
            if (ints[0] == 1)
            {
                double area = Area_Excluded_By_Exterior_Edge( c1, e1, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c1.area + area;
            }
            
            if (ints[0] == 2)
            {
                double area = Area_Excluded_By_Exterior_Edge( c2, e2, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c2.area + area;
            }
            
            if (ints[0] == 3)
            {
                double area = Area_Excluded_By_Exterior_Edge( c3, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c3.area + area;
            }
            
            if (ints[0] == 4)
            {
                double area = Area_Excluded_By_Exterior_Edge( c4, e4, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - c4.area + area;
            }
        }
        
        else
        {
            bool adj1_2 = false, adj1_3 = false, adj1_4 = false, adj2_3 = false, adj2_4 = false, adj3_4 = false;
            
            if (arc_order[2] == 2)
            {
                adj1_3 = true;
                adj1_4 = true;
                adj2_3 = true;
                adj2_4 = true;
            }
            
            else if (arc_order[2] == 3)
            {
                adj1_2 = true;
                adj1_4 = true;
                adj2_3 = true;
                adj3_4 = true;
            }
            
            else
            {
                adj1_2 = true;
                adj1_3 = true;
                adj2_4 = true;
                adj3_4 = true;
            }
            
            if (adj1_2 && (ints[0] == 1 || ints[0] == 2) && (ints[1] == 1 || ints[1] == 2))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, e1, e2, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - Two_Circle_Intersection_Area( c1, c2 ) + area;
            }
            
            else if (adj1_3 && (ints[0] == 1 || ints[0] == 3) && (ints[1] == 1 || ints[1] == 3))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c3, e1, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - Two_Circle_Intersection_Area( c1, c3 ) + area;
            }
            
            else if (adj1_4 && (ints[0] == 1 || ints[0] == 4) && (ints[1] == 1 || ints[1] == 4))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c4, e1, e4, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i3 )) return area;
                
                else return intersection_area - Two_Circle_Intersection_Area( c1, c4 ) + area;
            }
            
            else if (adj2_3 && (ints[0] == 2 || ints[0] == 3) && (ints[1] == 2 || ints[1] == 3))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c2, c3, e2, e3, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - Two_Circle_Intersection_Area( c2, c3 ) + area;
            }
            
            else if (adj2_4 && (ints[0] == 2 || ints[0] == 4) && (ints[1] == 2 || ints[1] == 4))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c2, c4, e2, e4, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - Two_Circle_Intersection_Area( c2, c4 ) + area;
            }
            
            else if (adj3_4 && (ints[0] == 3 || ints[0] == 4) && (ints[1] == 3 || ints[1] == 4))
            {
                double area = Two_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c3, c4, e3, e4, cell );
                
                if (Correct_Side_Of_Cell( cell, e1, i1 )) return area;
                
                else return intersection_area - Two_Circle_Intersection_Area( c3, c4 ) + area;
            }
        }
    }
    
    return 0;
}

double Non_Trivial_Four_Circle_Intersection_Area_Within_Cell ( Cell& cell, Circle const& c1, Circle const& c2, Circle const& c3, Circle const& c4 )
{
    double intersection_area = Non_Trivial_Four_Circle_Intersection_Area( c1, c2, c3, c4 );
    
    vector<int> arc_order;
    P2 i1, i2, i3, i4;
    
    Non_Trivial_Four_Circle_Intersection_Pts( c1, c2, c3, c4, i1, i2, i3, i4, arc_order );
    
    Cell cell_1 = cell, cell_2 = cell, cell_3 = cell, cell_4 = cell;
    
    bool cell_c1_intersection = Cell_Circle_Intersections( cell_1, c1 );
    bool cell_c2_intersection = Cell_Circle_Intersections( cell_2, c2 );
    bool cell_c3_intersection = Cell_Circle_Intersections( cell_3, c3 );
    bool cell_c4_intersection = Cell_Circle_Intersections( cell_4, c4 );
    
    int num_vertices_within_c1 = Num_Vertices_Within_Circle( cell, c1 );
    int num_vertices_within_c2 = Num_Vertices_Within_Circle( cell, c2 );
    int num_vertices_within_c3 = Num_Vertices_Within_Circle( cell, c3 );
    int num_vertices_within_c4 = Num_Vertices_Within_Circle( cell, c4 );
    
    bool c1_centre_within_cell = Pt_Within_Convex_Hull( cell, c1.c );
    bool c2_centre_within_cell = Pt_Within_Convex_Hull( cell, c2.c );
    bool c3_centre_within_cell = Pt_Within_Convex_Hull( cell, c3.c );
    bool c4_centre_within_cell = Pt_Within_Convex_Hull( cell, c4.c );
    
    if (!cell_c1_intersection && !cell_c2_intersection && !cell_c3_intersection && !cell_c4_intersection)
    {
        if (num_vertices_within_c1 == 4 && num_vertices_within_c2 == 4 && num_vertices_within_c3 == 4 && num_vertices_within_c4 == 4) return cell.area;
        
        else if (num_vertices_within_c1 == 4 || num_vertices_within_c2 == 4 || num_vertices_within_c3 == 4 || num_vertices_within_c4 == 4) return 0;
        
        else if (c1_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!cell_c1_intersection)
    {
        if (num_vertices_within_c1 == 4) return Three_Circle_Intersection_Area_Within_Cell( cell, c2, c3, c4 );
        
        else if (c1_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!cell_c2_intersection)
    {
        if (num_vertices_within_c2 == 4) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c3, c4 );
        
        else if (c2_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!cell_c3_intersection)
    {
        if (num_vertices_within_c3 == 4) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c4 );
        
        else if (c3_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else if (!cell_c4_intersection)
    {
        if (num_vertices_within_c4 == 4) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c3 );
        
        else if (c4_centre_within_cell) return intersection_area;
        
        else return 0;
    }
    
    else
    {
        int num_vertices_within_all_circles = 0;
        
        for (int counter = 0; counter < cell.vertices.size(); ++counter)
        {
            if (Norm( c1.c, cell.vertices[counter] ) < c1.r - tiny_num && Norm( c2.c, cell.vertices[counter] ) < c2.r - tiny_num && Norm( c3.c, cell.vertices[counter] ) < c3.r - tiny_num && Norm( c4.c, cell.vertices[counter] ) < c4.r) ++num_vertices_within_all_circles;
        }
        
        if (num_vertices_within_all_circles == 0)
        {
            double area = intersection_area;
            
            for (int counter = 0; counter < cell.edges.size(); ++counter)
            {
                area -= Four_Circle_Intersection_Area_Excluded_By_Exterior_Edge( c1, c2, c3, c4, cell_1.edges[counter], cell_2.edges[counter], cell_3.edges[counter], cell_4.edges[counter], cell );
            }
            
            if (area == intersection_area)
            {
                V2 v1 = i1 - ORIGIN, v2 = i2 - ORIGIN;
                
                P2 p = ORIGIN + 0.5 * v1 + 0.5 * v2;
                
                if (Pt_Within_Convex_Hull( cell, p )) return area;
                
                else return 0;
            }
            
            else return area;
        }
        
        else return intersection_area;
    }
}

double Non_Inclusion_Four_Circle_Intersection_Area_Within_Cell ( Cell& cell, Circle const& c1, Circle const& c2, Circle const& c3, Circle const& c4 )
{
    P2 p1, p2, p3;
    
    Intersection_Of_Two_Circles( c1, c2, p1, p2 );
    
    if (Norm( c3.c, p1 ) < c3.r + tiny_num && Norm( c3.c, p2 ) < c3.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c4 );
    
    else if (Norm( c4.c, p1 ) < c4.r + tiny_num && Norm( c4.c, p2 ) < c4.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c3 );
    
    Intersection_Of_Two_Circles( c1, c3, p1, p2 );
    
    if (Norm( c2.c, p1 ) < c2.r + tiny_num && Norm( c2.c, p2 ) < c2.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c3, c4 );
    
    else if (Norm( c4.c, p1 ) < c4.r + tiny_num && Norm( c4.c, p2 ) < c4.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c3 );
    
    Intersection_Of_Two_Circles( c1, c4, p1, p2 );
    
    if (Norm( c2.c, p1 ) < c2.r + tiny_num && Norm( c2.c, p2 ) < c2.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c3, c4 );
    
    else if (Norm( c3.c, p1 ) < c3.r + tiny_num && Norm( c3.c, p2 ) < c3.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c4 );
    
    Intersection_Of_Two_Circles( c2, c3, p1, p2 );
    
    if (Norm( c1.c, p1 ) < c1.r + tiny_num && Norm( c1.c, p2 ) < c1.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c2, c3, c4 );
    
    else if (Norm( c4.c, p1 ) < c4.r + tiny_num && Norm( c4.c, p2 ) < c4.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c3 );
    
    Intersection_Of_Two_Circles( c2, c4, p1, p2 );
    
    if (Norm( c1.c, p1 ) < c1.r + tiny_num && Norm( c1.c, p2 ) < c1.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c2, c3, c4 );
    
    else if (Norm( c3.c, p1 ) < c3.r + tiny_num && Norm( c3.c, p2 ) < c3.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c4 );
    
    Intersection_Of_Two_Circles( c3, c4, p1, p2 );
    
    if (Norm( c1.c, p1 ) < c1.r + tiny_num && Norm( c1.c, p2 ) < c1.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c2, c3, c4 );
    
    else if (Norm( c2.c, p1 ) < c2.r + tiny_num && Norm( c2.c, p2 ) < c2.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c3, c4 );
    
    Non_Trivial_Three_Circle_Intersection_Pts( c1, c2, c3, p1, p2, p3 );
    
    if (Norm( c4.c, p1 ) < c4.r + tiny_num && Norm( c4.c, p2 ) < c4.r + tiny_num && Norm( c4.c, p3 ) < c4.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c3 );
    
    if (Norm( c4.c, p1 ) > c4.r - tiny_num && Norm( c4.c, p2 ) > c4.r - tiny_num && Norm( c4.c, p3 ) > c4.r - tiny_num)
    {
        double area_1, area_2, area_3;
        
        area_1 = Two_Circle_Intersection_Area_Within_Cell( cell, c1, c4 );
        area_2 = Two_Circle_Intersection_Area_Within_Cell( cell, c2, c4 );
        area_3 = Two_Circle_Intersection_Area_Within_Cell( cell, c3, c4 );
        
        return area_1 + area_2 + area_3 - 2 * Circle_Area_Within_Cell( cell, c4 );
    }
    
    Non_Trivial_Three_Circle_Intersection_Pts( c1, c2, c4, p1, p2, p3 );
    
    if (Norm( c3.c, p1 ) < c3.r + tiny_num && Norm( c3.c, p2 ) < c3.r + tiny_num && Norm( c3.c, p3 ) < c3.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c4 );
    
    if (Norm( c3.c, p1 ) > c3.r - tiny_num && Norm( c3.c, p2 ) > c3.r - tiny_num && Norm( c3.c, p3 ) > c3.r - tiny_num)
    {
        double area_1, area_2, area_3;
        
        area_1 = Two_Circle_Intersection_Area_Within_Cell( cell, c1, c3 );
        area_2 = Two_Circle_Intersection_Area_Within_Cell( cell, c2, c3 );
        area_3 = Two_Circle_Intersection_Area_Within_Cell( cell, c3, c4 );
        
        return area_1 + area_2 + area_3 - 2 * Circle_Area_Within_Cell( cell, c3 );
    }
    
    Non_Trivial_Three_Circle_Intersection_Pts( c1, c3, c4, p1, p2, p3 );
    
    if (Norm( c2.c, p1 ) < c2.r + tiny_num && Norm( c2.c, p2 ) < c2.r + tiny_num && Norm( c2.c, p3 ) < c2.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c1, c3, c4 );
    
    if (Norm( c2.c, p1 ) > c2.r - tiny_num && Norm( c2.c, p2 ) > c2.r - tiny_num && Norm( c2.c, p3 ) > c2.r - tiny_num)
    {
        double area_1, area_2, area_3;
        
        area_1 = Two_Circle_Intersection_Area_Within_Cell( cell, c1, c2 );
        area_2 = Two_Circle_Intersection_Area_Within_Cell( cell, c2, c3 );
        area_3 = Two_Circle_Intersection_Area_Within_Cell( cell, c2, c4 );
        
        return area_1 + area_2 + area_3 - 2 * Circle_Area_Within_Cell( cell, c2 );
    }
    
    Non_Trivial_Three_Circle_Intersection_Pts( c2, c3, c4, p1, p2, p3 );
    
    if (Norm( c1.c, p1 ) < c1.r + tiny_num && Norm( c1.c, p2 ) < c1.r + tiny_num && Norm( c1.c, p3 ) < c1.r + tiny_num) return Three_Circle_Intersection_Area_Within_Cell( cell, c2, c3, c4 );
    
    if (Norm( c1.c, p1 ) > c1.r - tiny_num && Norm( c1.c, p2 ) > c1.r - tiny_num && Norm( c1.c, p3 ) > c1.r - tiny_num)
    {
        double area_1, area_2, area_3;
        
        area_1 = Two_Circle_Intersection_Area_Within_Cell( cell, c1, c2 );
        area_2 = Two_Circle_Intersection_Area_Within_Cell( cell, c1, c3 );
        area_3 = Two_Circle_Intersection_Area_Within_Cell( cell, c1, c4 );
        
        return area_1 + area_2 + area_3 - 2 * Circle_Area_Within_Cell( cell, c1 );
    }
    
    return Non_Trivial_Four_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c3, c4 );
}

double Four_Circle_Intersection_Area_Within_Cell ( Cell& cell, Circle const& c1, Circle const& c2, Circle const& c3, Circle const& c4)
{
    double area_1, area_2, area_3, area_4;
    
    area_1 = Three_Circle_Intersection_Area_Within_Cell( cell, c2, c3, c4 );
    area_2 = Three_Circle_Intersection_Area_Within_Cell( cell, c1, c3, c4 );
    area_3 = Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c4 );
    area_4 = Three_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c3 );
    
    if (area_1 < tiny_num || area_2 < tiny_num || area_3 < tiny_num || area_4 < tiny_num) return 0;
    
    else
    {
        vector<Circle> circles;
        
        circles.push_back( c1 );
        circles.push_back( c2 );
        circles.push_back( c3 );
        circles.push_back( c4 );
        
        Order_Circles( circles );
        
        bool inside0_1 = false, inside0_2 = false, inside0_3 = false, inside1_2 = false, inside1_3 = false, inside2_3 = false;
        
        if (Norm( circles[0].c, circles[1].c ) < circles[1].r - circles[0].r ) inside0_1 = true;
        if (Norm( circles[0].c, circles[2].c ) < circles[2].r - circles[0].r ) inside0_2 = true;
        if (Norm( circles[0].c, circles[3].c ) < circles[3].r - circles[0].r ) inside0_3 = true;
        if (Norm( circles[1].c, circles[2].c ) < circles[2].r - circles[1].r ) inside1_2 = true;
        if (Norm( circles[1].c, circles[3].c ) < circles[3].r - circles[1].r ) inside1_3 = true;
        if (Norm( circles[2].c, circles[3].c ) < circles[3].r - circles[2].r ) inside2_3 = true;
        
        if (inside0_1 && inside0_2 && inside0_3) return Circle_Area_Within_Cell( cell, circles[0] );
        
        else if (!inside0_1 && inside0_2 && inside0_3) return Two_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[1] );
        
        else if (inside0_1 && !inside0_2 && inside0_3) return Two_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[2] );
        
        else if (inside0_1 && inside0_2 && !inside0_3) return Two_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[3] );
        
        else if (!inside0_1 && !inside0_2 && inside0_3) return Three_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[1], circles[2] );
        
        else if (!inside0_1 && inside0_2 && !inside0_3) return Three_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[1], circles[3] );
        
        else if (inside0_1 && !inside0_2 && !inside0_3) return Three_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[2], circles[3] );
        
        else if (inside1_2 && inside1_3) return Two_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[1] );
        
        else if (!inside1_2 && inside1_3) return Three_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[1], circles[2] );
        
        else if (inside1_2 && !inside1_3) return Three_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[1], circles[3] );
        
        else if (inside2_3) return Three_Circle_Intersection_Area_Within_Cell( cell, circles[0], circles[1], circles[2] );
        
        else return Non_Inclusion_Four_Circle_Intersection_Area_Within_Cell( cell, c1, c2, c3, c4 );
    }
}

void Search_Then_Add_Critical_Pt ( vector<double>& critical_pts, double radius )
{
    bool found = false;
    
    for (int counter = 0; counter < critical_pts.size(); ++counter)
    {
        if (radius == critical_pts[counter]) found = true;
    }
    
    if (!found) critical_pts.push_back( radius );
}

void First_Order_Critical_Pts ( Cell& cell, vector<double>& critical_pts )
{
    Search_Then_Add_Critical_Pt( critical_pts, Norm( cell.vertices[0], cell.vertices[1] ) );
    Search_Then_Add_Critical_Pt( critical_pts, Norm( cell.vertices[0], cell.vertices[2] ) );
    Search_Then_Add_Critical_Pt( critical_pts, Norm( cell.vertices[0], cell.vertices[3] ) );
    Search_Then_Add_Critical_Pt( critical_pts, Norm( cell.vertices[1], cell.vertices[3] ) );
}

void Second_Order_Critical_Pts ( Cell& cell, vector<double>& critical_pts )
{
    Search_Then_Add_Critical_Pt( critical_pts, 0.5 * Norm( cell.vertices[0], cell.vertices[1] ) );
    Search_Then_Add_Critical_Pt( critical_pts, 0.5 * Norm( cell.vertices[0], cell.vertices[2] ) );
    Search_Then_Add_Critical_Pt( critical_pts, 0.5 * Norm( cell.vertices[0], cell.vertices[3] ) );
    Search_Then_Add_Critical_Pt( critical_pts, 0.5 * Norm( cell.vertices[1], cell.vertices[3] ) );
}

void Third_Order_Critical_Pts ( Cell& cell, vector<double>& critical_pts )
{
    P2 triangle_circumcentre = Triangle_Circumcentre( cell.vertices[0], cell.vertices[1], cell.vertices[2] );
    
    Search_Then_Add_Critical_Pt( critical_pts, Norm( cell.vertices[0], triangle_circumcentre ) );
    
    triangle_circumcentre = Triangle_Circumcentre( cell.vertices[0], cell.vertices[1], cell.vertices[3] );
    
    Search_Then_Add_Critical_Pt( critical_pts, Norm( cell.vertices[0], triangle_circumcentre ) );
}

void Fourth_Order_Critical_Pts ( Cell& cell, vector<double>& critical_pts )
{
    double max_dist = 0;
    
    if (Norm( cell.vertices[0], cell.vertices[1] ) > max_dist) max_dist = Norm( cell.vertices[0], cell.vertices[1] );
    if (Norm( cell.vertices[0], cell.vertices[2] ) > max_dist) max_dist = Norm( cell.vertices[0], cell.vertices[2] );
    if (Norm( cell.vertices[0], cell.vertices[3] ) > max_dist) max_dist = Norm( cell.vertices[0], cell.vertices[3] );
    if (Norm( cell.vertices[1], cell.vertices[3] ) > max_dist) max_dist = Norm( cell.vertices[1], cell.vertices[3] );
    
    Search_Then_Add_Critical_Pt( critical_pts, max_dist );
}

void Extract_Critical_Pts ( string const& directory, Cell& cell )
{
    vector<double> critical_pts;
    
    First_Order_Critical_Pts( cell, critical_pts );
    Second_Order_Critical_Pts( cell, critical_pts );
    Third_Order_Critical_Pts( cell, critical_pts );
    Fourth_Order_Critical_Pts( cell, critical_pts );
    
    ofstream ofs( directory + "Data/Critical_Pts.txt" );
    
    for (double counter = 0; counter < critical_pts.size(); ++counter)
    {
        double area = First_Order_Area( cell, critical_pts[counter] ) / (double)cell.area;
        
        ofs << critical_pts[counter] << " " << area << endl;
        
        area = Second_Order_Area( cell, critical_pts[counter] ) / (double)cell.area;
        
        if (critical_pts[counter] != 1) ofs << critical_pts[counter] << " " << area << endl;
        
        area = Third_Order_Area( cell, critical_pts[counter] ) / (double)cell.area;
        
        if (critical_pts[counter] != 1) ofs << critical_pts[counter] << " " << area << endl;
        
        area = Fourth_Order_Area( cell, critical_pts[counter] ) / (double)cell.area;
        
        if (critical_pts[counter] != 1) ofs << critical_pts[counter] << " " << area << endl;
    }
    
    ofs.close();
}
