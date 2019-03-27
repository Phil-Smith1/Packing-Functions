#pragma once

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
