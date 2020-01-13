/*double r = 1.225;
int c = 0;

 //cout << Second_Order_Total_Volume( cells[c], r - 0.001, false ) / (double)cells[c].vol << endl;
 //cout << Second_Order_Total_Volume( cells[c], r, false ) / (double)cells[c].vol << endl;
 //cout << Second_Order_Total_Volume( cells[c], r + 0.001, false ) / (double)cells[c].vol << endl;
 //cout << Second_Order_Total_Volume( cells[c], r + 0.002, false ) / (double)cells[c].vol << endl;
 
 //cout << Third_Order_Total_Volume( cells[c], r - 0.001 ) / (double)cells[c].vol << endl;
 //cout << Third_Order_Total_Volume( cells[c], r ) / (double)cells[c].vol << endl;
 //cout << Third_Order_Total_Volume( cells[c], r + 0.001 ) / (double)cells[c].vol << endl;
 //cout << Third_Order_Total_Volume( cells[c], r + 0.002 ) / (double)cells[c].vol << endl;

 vector<Sphere> spheres;
 spheres.push_back( Sphere( cells[c].pts[30], r ) ); // 15 35
 spheres.push_back( Sphere( cells[c].pts[34], r ) );
 spheres.push_back( Sphere( cells[c].pts[39], r ) );
 spheres.push_back( Sphere( cells[c].pts[30], r + 0.001 ) );
 spheres.push_back( Sphere( cells[c].pts[34], r + 0.001 ) );
 spheres.push_back( Sphere( cells[c].pts[39], r + 0.001 ) );

 //cout << Two_Sphere_Intersection_Volume_Within_Cell( cells[c], spheres[0], spheres[1] ) << endl;
 //cout << Two_Sphere_Intersection_Volume_Within_Cell( cells[c], spheres[3], spheres[4] ) << endl;
 
 //cout << Three_Sphere_Intersection_Volume_Within_Cell( cells[c], spheres[3], spheres[4], spheres[5] ) / (double)cells[c].vol << endl;
 //cout << Three_Sphere_Intersection_Volume_Within_Cell( cells[c], spheres[0], spheres[1], spheres[2] ) / (double)cells[c].vol << endl;

double d1 = Norm( spheres[1].c, spheres[2].c ), d2 = Norm( spheres[0].c, spheres[2].c ), d3 = Norm( spheres[0].c, spheres[1].c );

V3 v = spheres[0].c - spheres[1].c;
v = v / (double)Norm( v );

double k = (spheres[1].r * spheres[1].r + d3 * d3 - spheres[0].r * spheres[0].r) / (double)(2 * d3);

P3 pt = spheres[1].c + k * v;

Pl3 p3( pt, v );

v = spheres[0].c - spheres[2].c;
v = v / (double)Norm( v );

k = (spheres[2].r * spheres[2].r + d2 * d2 - spheres[0].r * spheres[0].r) / (double)(2 * d2);

pt = spheres[2].c + k * v;

Pl3 p2( pt, v );

v = spheres[1].c - spheres[2].c;
v = v / (double)Norm( v );

k = (spheres[2].r * spheres[2].r + d1 * d1 - spheres[1].r * spheres[1].r) / (double)(2 * d1);

pt = spheres[2].c + k * v;

Pl3 p1( pt, v );

//cout << Spherical_Wedge_Volume_Within_Cell( cells[c], spheres[2], p3.opposite(), p2 ) << endl;

//cout << Sphere_Five_Plane_Intersection_Volume( spheres[0], p3.opposite(), p2.opposite(), cells[c].planes[0].opposite(), cells[c].planes[3].opposite(), cells[c].planes[5].opposite(), 0 ) << endl;

//cout << Sphere_Four_Plane_Intersection_Volume( spheres[2], p3.opposite(), p2, cells[c].planes[0].opposite(), cells[c].planes[5].opposite() ) << endl;

//cout << General_Spherical_Cone( spheres[2], p3, cells[c].planes[0], cells[c].planes[5] ) << endl;

/*L3 l3 = Line_Of_Intersection_Of_Two_Planes( p3, p2 );
 L3 l2 = Line_Of_Intersection_Of_Two_Planes( p3, cells[c].planes[5].opposite() );
 
 P3 vertex = Intersection_Of_Two_Lines3D( l2, l3 );
 
 Circle3D ci = Circular_Intersection_Of_Sphere_And_Plane( spheres[0], p3 );
 
 P3 pt1, pt2, pt3, i1, i2;
 
 Intersection_Pts_Of_Plane_And_Circle( p2, ci, i1, i2 );
 
 if (cells[c].planes[5].opposite().oriented_side( i1 ) == ON_POSITIVE_SIDE) pt3 = i1;
 else pt3 = i2;
 
 Intersection_Pts_Of_Plane_And_Circle( cells[c].planes[5].opposite(), ci, i1, i2 );
 
 if (p2.oriented_side( i1 ) == ON_POSITIVE_SIDE) pt2 = i1;
 else pt2 = i2;
 
 ci = Circular_Intersection_Of_Sphere_And_Plane( spheres[0], p2 );
 
 Intersection_Pts_Of_Plane_And_Circle( cells[c].planes[5].opposite(), ci, i1, i2 );
 
 if (p3.oriented_side( i1 ) == ON_POSITIVE_SIDE) pt1 = i1;
 else pt1 = i2;
 
 Pl3 p4( pt1, pt2, pt3 );
 
 if (p4.oriented_side( vertex ) == ON_POSITIVE_SIDE) p4 = p4.opposite();*/

//cout << squared_distance( vertex, p4 ) << endl;

//cout << General_Spherical_Wedge( spheres[0], p3.opposite(), p4 ) << endl;

//cout << Spherical_Cap_Volume_Within_Cell( cells[c], spheres[0], p3.opposite() ) << endl;

//cout << Spherical_Wedge_Volume_Within_Cell( cells[c], spheres[2], p3.opposite(), p2 ) << endl;

//cout << Sphere_Five_Plane_Intersection_Volume( spheres[2], p3.opposite(), p2, cells[c].planes[0].opposite(), cells[c].planes[1].opposite(), cells[c].planes[5].opposite(), 0 ) << endl;

//cout << Sphere_Five_Plane_Intersection_Volume( spheres[2], cells[c].planes[1].opposite(), p2, p3.opposite(), cells[c].planes[2].opposite(), cells[c].planes[4].opposite(), 11 ) << endl;

//cout << Non_Parallel_Lines_Case5B( spheres[2], cells[c].planes[4].opposite(), p3.opposite(), p2, cells[c].planes[2].opposite(), cells[c].planes[3].opposite(), 15 ) << endl;

//cout << Non_Parallel_Lines_Case5B( spheres[2], cells[c].planes[0].opposite(), p3.opposite(), cells[c].planes[1].opposite(), p2, cells[c].planes[5].opposite(), 15 ) << endl;

//cout << Sphere_Four_Plane_Intersection_Volume( spheres[2], cells[c].planes[5], p3, cells[c].planes[0], cells[c].planes[1] ) << endl;

//cout << General_Spherical_Cone( spheres[0], p3, cells[c].planes[2], cells[c].planes[4] ) << endl;

//cout << Parallel_Planes_Case5( spheres[1], p3, cells[c].planes[1].opposite(), p1.opposite(), cells[c].planes[0].opposite(), cells[c].planes[5].opposite() ) << endl;
//cout << Parallel_Planes_Case5( spheres[3], p3, cells[c].planes[1].opposite(), p1.opposite(), cells[c].planes[0].opposite(), cells[c].planes[5].opposite() ) << endl;

//cout << General_Spherical_Cone( spheres[0], p3.opposite(), cells[c].planes[0].opposite(), cells[c].planes[4].opposite() ) << endl;
//cout << Circumradius( spheres[0].c, spheres[1].c, spheres[2].c ) << endl;
//cout << General_Spherical_Wedge( spheres[2], p3.opposite(), p2 ) << endl;
//cout << General_Spherical_Wedge( spheres[2], p3, p1 ) << endl;
