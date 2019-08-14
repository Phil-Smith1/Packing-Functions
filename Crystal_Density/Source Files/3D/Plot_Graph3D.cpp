#include "gnuplot-iostream.h"

#include "Input3D.h"

void Asymptote3D ( string const& directory, int fn, Gnuplot& gp )
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

void Plot_Derivatives3D ( string const& directory, double max_radius )
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
    gp << "set xlabel 'Radius of Balls' font ', 20' offset 0, -0.3\n";
    
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
    
    gp << "set output \"Graphs/Second Derivatives/F1 Second Derivative.pdf\"\n";
    
    gp << "unset key\n";
    
    gp << "set title 'Second Derivative of f_1' font ', 20'\n";
    
    gp << "set ylabel 'f_1\u2032\u2032(r)' font ', 20' offset -1.5, 0\n";
    
    Asymptote3D( directory, 1, gp );
    
    gp << "plot 'Data/F_1_Second_Derivs.txt' using 1:2 notitle smooth csplines ls 1\n";
}

void Plot_PNG3D ( string const& directory, double max_radius, int iter )
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
    gp << "set xlabel 'Radius of Balls' font ', 20' offset 0, -0.3\n";
    
    gp << "set xrange [0: " << max_radius << "]\n";
    gp << "set yrange [0: 9.01]\n";
    gp << "set xtics font ', 18'\n";
    gp << "set ytics font ', 18'\n";
    
    gp << "set key horizontal tmargin c font ', 18'\n";
    
    gp << "set style line 1 lc rgb '#0d61ec' lw 2\n";
    gp << "set style line 2 lc rgb '#24ae1d' lw 2\n";
    gp << "set style line 3 lc rgb '#ffae00' lw 2\n";
    gp << "set style line 4 lc rgb '#e70000' lw 2\n";
    gp << "set style line 5 lc rgb '#000000' pt 7 ps 0.5\n";
    
    gp << "set output \"Graphs/Deformation/Deform" << iter << ".png\"\n";
    
    gp << "plot 'Data/Results.txt' using 1:2 smooth csplines ls 1 title '1', 'Data/Derivative_Critical_Pts.txt' using 1:2 notitle ls 5\n";
}

void Plot_PDF3D ( string const& directory, double max_radius )
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
    gp << "set xlabel 'Radius of Balls' font ', 20' offset 0, -0.3\n";
    
    gp << "set xrange [0: " << max_radius << "]\n";
    gp << "set yrange [0: 28.01]\n";
    gp << "set xtics font ', 18'\n";
    gp << "set ytics font ', 18'\n";
    
    gp << "set key horizontal tmargin c font ', 18'\n";
    
    gp << "set style line 1 lc rgb '#0d61ec' lw 3\n";
    gp << "set style line 2 lc rgb '#24ae1d' lw 3\n";
    gp << "set style line 3 lc rgb '#ffae00' lw 3\n";
    gp << "set style line 4 lc rgb '#e70000' lw 3\n";
    gp << "set style line 5 lc rgb '#000000' pt 7 ps 0.5\n";
    
    gp << "set output \"Graphs/Packing Functions.pdf\"\n";
    
    gp << "plot 'Data/Results.txt' using 1:2 smooth csplines ls 1 title '1','Data/Results.txt' using 1:3 smooth csplines ls 2 title '2', 'Data/Derivative_Critical_Pts.txt' using 1:2 notitle ls 5\n";
}

void Plot_Graph3D ( string const& directory, Input3D const& input, int iter )
{
    if (input.deformation_type != 0) Plot_PNG3D( directory, input.max_radius, iter );
    
    else
    {
        Plot_PDF3D( directory, input.max_radius );
        
        Plot_Derivatives3D( directory, input.max_radius );
    }
}