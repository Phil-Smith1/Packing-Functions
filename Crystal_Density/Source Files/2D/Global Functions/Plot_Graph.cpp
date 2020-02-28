#include "gnuplot-iostream.h"

#include "Input.h"

void Asymptote ( string const& directory, int fn, Gnuplot& gp )
{
    gp << "unset arrow\n";
    
    ifstream ifs( directory + "Data/Derivative_Critical_Pts.txt" );
    
    string line_data;
    
    while(getline( ifs, line_data ))
    {
        double a, b, c;
        stringstream stream;
        
        stream << line_data;
        stream >> a >> b >> c;
        
        if (c == fn)
        {
            gp << "set arrow from " << a << ", graph 0 to " << a << ", graph 1 dashtype 2 lw 2 lc rgb '#000000' nohead\n";
        }
    }
}

void Plot_At_Least ( string const& directory, double max_radius )
{
    Gnuplot gp;
    
    gp << "cd \"" << directory << "\"\n";
    
    gp << "set terminal pdfcairo size 4.5, 3.5\n";
    
    gp << "set border 3\n";
    gp << "set grid\n";
    gp << "set bmargin 4.5\n";
    gp << "set lmargin 8.5\n";
    gp << "set tmargin 2\n";
    gp << "set rmargin 2\n";
    
    gp << "set ylabel 'f_n(r)' font ', 20' offset -0.5, 0\n";
    gp << "set xlabel 'Radius of Disks' font ', 20' offset 0, -0.3\n";
    
    gp << "set xrange [0: " << max_radius << "]\n";
    gp << "set yrange [0: 1.01]\n";
    gp << "set xtics font ', 18'\n";
    gp << "set ytics font ', 18'\n";
    
    gp << "set key horizontal tmargin c font ', 18'\n";
    
    gp << "set style line 1 lc rgb '#0d61ec' lw 2\n";
    gp << "set style line 2 lc rgb '#24ae1d' lw 2\n";
    gp << "set style line 3 lc rgb '#ffae00' lw 2\n";
    gp << "set style line 4 lc rgb '#e70000' lw 2\n";
    gp << "set style line 5 lc rgb '#000000' pt 7 ps 0.5\n";
    
    gp << "set output \"Graphs/Packing Functions At Least.pdf\"\n";
    
    gp << "plot 'Data/Results_At_Least.txt' using 1:2 smooth csplines ls 1 title '1', 'Data/Results_At_Least.txt' using 1:3 smooth csplines ls 2 title '2', 'Data/Results_At_Least.txt' using 1:4 smooth csplines ls 3 title '3', 'Data/Results_At_Least.txt' using 1:5 smooth csplines ls 4 title '4', 'Data/Derivative_Critical_Pts.txt' using 1:2 notitle ls 5\n";
}

void Plot_PDF ( string const& directory, double max_radius )
{
    Gnuplot gp;
    
    gp << "cd \"" << directory << "\"\n";
    
    gp << "set terminal pdfcairo size 4.6, 3\n";
    
    gp << "set border 3\n";
    gp << "set grid\n";
    gp << "set bmargin 4\n";
    gp << "set lmargin 7.5\n";
    gp << "set tmargin 5\n";
    gp << "set rmargin 3\n";
    
    gp << "set title 'Covering functions {/Symbol p}_i(C; r) for the Square Lattice' font ', 16' offset 0, 2\n";
    gp << "set ylabel '{/Symbol p}_i(C; r)' font ', 16' offset 0.8, 0\n";
    gp << "set xlabel 'Radius of Disks' font ', 16' offset 0, -0.3\n";
    
    gp << "set xrange [0: " << max_radius << "]\n";
    gp << "set yrange [0: 1.01]\n";
    gp << "set xtics font ', 14'\n";
    gp << "set ytics font ', 14'\n";
    
    gp << "set key horizontal at graph 0.5, graph 1.04 center bottom font ', 14'\n";
    
    gp << "set style line 1 lc rgb '#0d61ec' lw 3\n";
    gp << "set style line 2 lc rgb '#24ae1d' lw 3\n";
    gp << "set style line 3 lc rgb '#ffae00' lw 3\n";
    gp << "set style line 4 lc rgb '#e70000' lw 3\n";
    gp << "set style line 6 lc rgb '#d500ff' lw 3\n";
    gp << "set style line 5 lc rgb '#000000' pt 7 ps 0.5\n";
    gp << "set style line 7 dt 2 lc rgb '#0d61ec' lw 3\n";
    gp << "set style line 8 dt 2 lc rgb '#24ae1d' lw 3\n";
    gp << "set style line 9 dt 2 lc rgb '#ffae00' lw 3\n";
    gp << "set style line 10 dt 2 lc rgb '#e70000' lw 3\n";
    
    gp << "set output \"Graphs/Packing Functions Exact.pdf\"\n";
    
    //gp << "plot 'Data/2D_Cloud2.txt' using 1:2 smooth csplines ls 1 title '{/Symbol p}_1(C; r)', 'Data/2D_Cloud2.txt' using 1:3 smooth csplines ls 2 title '{/Symbol p}_2(C; r)', 'Data/2D_Cloud2.txt' using 1:4 smooth csplines ls 3 title '{/Symbol p}_3(C; r)', 'Data/2D_Cloud2.txt' using 1:5 smooth csplines ls 4 title '{/Symbol p}_4(C; r)', 'Data/2D_Cloud2.txt' using 1:6 smooth csplines ls 7 notitle, 'Data/2D_Cloud2.txt' using 1:7 smooth csplines ls 8 notitle, 'Data/2D_Cloud2.txt' using 1:8 smooth csplines ls 9 notitle, 'Data/2D_Cloud2.txt' using 1:9 smooth csplines ls 10 notitle'\n";
    
    gp << "plot 'Data/Results_Exact.txt' using 1:2 smooth csplines ls 1 title '{/Symbol p}_1(C; r)', 'Data/Results_Exact.txt' using 1:3 smooth csplines ls 2 title '{/Symbol p}_2(C; r)', 'Data/Results_Exact.txt' using 1:4 smooth csplines ls 3 title '{/Symbol p}_3(C; r)', 'Data/Results_Exact.txt' using 1:5 smooth csplines ls 4 title '{/Symbol p}_4(C; r)'\n";
}

void Plot_PNG ( string const& directory, double max_radius, int iter )
{
    Gnuplot gp;
    
    gp << "cd \"" << directory << "\"\n";
    
    gp << "set terminal pngcairo size 600,350\n";
    
    gp << "set border 3\n";
    gp << "set grid\n";
    gp << "set bmargin 4.5\n";
    gp << "set lmargin 8.5\n";
    gp << "set tmargin 2\n";
    gp << "set rmargin 2\n";
    
    gp << "set ylabel 'f_n(r)' font ', 20' offset -0.5, 0\n";
    gp << "set xlabel 'Radius of Disks' font ', 20' offset 0, -0.3\n";
    
    gp << "set xrange [0: " << max_radius << "]\n";
    gp << "set yrange [0: 1.01]\n";
    gp << "set xtics font ', 18'\n";
    gp << "set ytics font ', 18'\n";
    
    gp << "set key horizontal tmargin c font ', 18'\n";
    
    gp << "set style line 1 lc rgb '#0d61ec' lw 2\n";
    gp << "set style line 2 lc rgb '#24ae1d' lw 2\n";
    gp << "set style line 3 lc rgb '#ffae00' lw 2\n";
    gp << "set style line 4 lc rgb '#e70000' lw 2\n";
    gp << "set style line 6 lc rgb '#d500ff' lw 3\n";
    gp << "set style line 5 lc rgb '#000000' pt 7 ps 0.5\n";
    
    gp << "set output \"Graphs/Deformation/Deform" << iter << ".png\"\n";
    
    gp << "plot 'Data/Results_Exact.txt' using 1:2 smooth csplines ls 1 title '1', 'Data/Results_Exact.txt' using 1:3 smooth csplines ls 2 title '2', 'Data/Results_Exact.txt' using 1:4 smooth csplines ls 3 title '3', NaN ls 4 title '4', 'Data/Results_Exact.txt' using 1:5 smooth csplines ls 6 title '5', 'Data/Derivative_Critical_Pts.txt' using 1:2 notitle ls 5\n";
}

void Plot_Derivatives ( string const& directory, double max_radius )
{
    Gnuplot gp;
    
    gp << "cd \"" << directory << "\"\n";
    
    gp << "set terminal pdfcairo size 4.5, 3.5\n";
    
    gp << "set border 3\n";
    gp << "set grid\n";
    gp << "set bmargin 4.5\n";
    gp << "set lmargin 9.5\n";
    gp << "set tmargin 4\n";
    gp << "set rmargin 2\n";
    
    gp << "set ylabel 'f_1\u2032(r)' font ', 20' offset -1.5, 0\n";
    gp << "set xlabel 'Radius of Disks' font ', 20' offset 0, -0.3\n";
    
    gp << "set xrange [0: " << max_radius << "]\n";
    gp << "set xtics font ', 18'\n";
    gp << "set ytics font ', 18'\n";
    
    gp << "set key horizontal tmargin c font ', 18'\n";
    
    gp << "set style line 1 lc rgb '#0d61ec' lw 2\n";
    gp << "set style line 2 lc rgb '#24ae1d' lw 2\n";
    gp << "set style line 3 lc rgb '#ffae00' lw 2\n";
    gp << "set style line 4 lc rgb '#e70000' lw 2\n";
    gp << "set style line 5 lc rgb '#000000' pt 7 ps 0.5\n";
    
    gp << "set output \"Graphs/First Derivatives/F1 First Derivative.pdf\"\n";
    
    gp << "set title 'First Derivative of f_1' font ', 20'\n";
    
    gp << "plot 'Data/First_Derivs.txt' using 1:2 notitle smooth csplines ls 1\n";
    
    gp << "set output \"Graphs/First Derivatives/F2 First Derivative.pdf\"\n";
    
    gp << "set title 'First Derivative of f_2' font ', 20'\n";
    
    gp << "set ylabel 'f_2\u2032(r)' font ', 20' offset -1.5, 0\n";
    
    gp << "plot 'Data/First_Derivs.txt' using 1:3 notitle smooth csplines ls 2\n";
    
    gp << "set output \"Graphs/First Derivatives/F3 First Derivative.pdf\"\n";
    
    gp << "set title 'First Derivative of f_3' font ', 20'\n";
    
    gp << "set ylabel 'f_3\u2032(r)' font ', 20' offset -1.5, 0\n";
    
    gp << "plot 'Data/First_Derivs.txt' using 1:4 notitle smooth csplines ls 3\n";
    
    gp << "set output \"Graphs/First Derivatives/F4 First Derivative.pdf\"\n";
    
    gp << "set title 'First Derivative of f_4' font ', 20'\n";
    
    gp << "set ylabel 'f_4\u2032(r)' font ', 20' offset -1.5, 0\n";
    
    gp << "plot 'Data/First_Derivs.txt' using 1:5 notitle smooth csplines ls 4\n";
    
    gp << "set output \"Graphs/First Derivatives/First Derivatives.pdf\"\n";
    
    gp << "set key at graph 0.5, graph 1.02 center bottom\n";
    
    gp << "set title 'First Derivatives' font ', 20' offset 0, 1\n";
    
    gp << "set ylabel 'f_n\u2032(r)' font ', 20' offset -1.5, 0\n";
    
    gp << "plot 'Data/First_Derivs.txt' using 1:2 title '1' smooth csplines ls 1, 'Data/First_Derivs.txt' using 1:3 title '2' smooth csplines ls 2, 'Data/First_Derivs.txt' using 1:4 title '3' smooth csplines ls 3, 'Data/First_Derivs.txt' using 1:5 title '4' smooth csplines ls 4\n";
    
    gp << "set output \"Graphs/Second Derivatives/F1 Second Derivative.pdf\"\n";
    
    gp << "unset key\n";
    
    gp << "set title 'Second Derivative of f_1' font ', 20'\n";
    
    gp << "set ylabel 'f_1\u2032\u2032(r)' font ', 20' offset -1.5, 0\n";
    
    Asymptote( directory, 1, gp );
    
    gp << "plot 'Data/F_1_Second_Derivs.txt' using 1:2 notitle smooth csplines ls 1\n";
    
    gp << "set output \"Graphs/Second Derivatives/F2 Second Derivative.pdf\"\n";
    
    gp << "set title 'Second Derivative of f_2' font ', 20'\n";
    
    gp << "set ylabel 'f_2\u2032\u2032(r)' font ', 20' offset -1.5, 0\n";
    
    Asymptote( directory, 2, gp );
    
    gp << "plot 'Data/F_2_Second_Derivs.txt' using 1:2 notitle smooth csplines ls 2\n";
    
    gp << "set output \"Graphs/Second Derivatives/F3 Second Derivative.pdf\"\n";
    
    gp << "set title 'Second Derivative of f_3' font ', 20'\n";
    
    gp << "set ylabel 'f_3\u2032\u2032(r)' font ', 20' offset -1.5, 0\n";
    
    Asymptote( directory, 3, gp );
    
    gp << "plot 'Data/F_3_Second_Derivs.txt' using 1:2 notitle smooth csplines ls 3\n";
    
    gp << "set output \"Graphs/Second Derivatives/F4 Second Derivative.pdf\"\n";
    
    gp << "set title 'Second Derivative of f_4' font ', 20'\n";
    
    gp << "set ylabel 'f_4\u2032\u2032(r)' font ', 20' offset -1.5, 0\n";
    
    Asymptote( directory, 4, gp );
    
    gp << "plot 'Data/F_4_Second_Derivs.txt' using 1:2 notitle smooth csplines ls 4\n";
    
    gp << "unset arrow\n";
    
    gp << "set output \"Graphs/Second Derivatives/Second Derivatives.pdf\"\n";
    
    gp << "set key at graph 0.5, graph 1.02 center bottom\n";
    
    gp << "set title 'Second Derivatives' font ', 20' offset 0, 1\n";
    
    gp << "set ylabel 'f_n\u2032\u2032(r)' font ', 20' offset -1.5, 0\n";
    
    gp << "plot 'Data/F_1_Second_Derivs.txt' using 1:2 title '1' smooth csplines ls 1, 'Data/F_2_Second_Derivs.txt' using 1:2 title '2' smooth csplines ls 2, 'Data/F_3_Second_Derivs.txt' using 1:2 title '3' smooth csplines ls 3, 'Data/F_4_Second_Derivs.txt' using 1:2 title '4' smooth csplines ls 4\n";
}

void Plot_Graph ( string const& directory, Input const& input, int iter )
{
    if (input.deformation_type != 0) Plot_PNG( directory, input.max_radius, iter );
    
    else if (input.function_type == "At_Least") Plot_At_Least( directory, input.max_radius );
    
    else if (input.function_type == "Exact") Plot_PDF( directory, input.max_radius );
    
    if (input.deformation_type == 0) Plot_Derivatives( directory, input.max_radius );
}
