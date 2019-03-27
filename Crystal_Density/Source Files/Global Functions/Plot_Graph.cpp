#include "gnuplot-iostream.h"

#include <string>

using namespace std;

void Plot_Graph ( string const& directory, string const& function_type, string const& lattice_type, double max_radius, int iter )
{
    Gnuplot gp;
    
    gp << "cd \"" << directory << "\"\n";
    
    gp << "set terminal pngcairo size 380,350\n";
    
    gp << "set border 3\n";
    gp << "set grid\n";
    gp << "set bmargin 6\n";
    gp << "set lmargin 12\n";
    gp << "set tmargin 4\n";
    
    //gp << "set title 'Packing Functions for the " << lattice_type << " Lattice' font ',22' offset 0, 0.5\n";
    gp << "set xlabel 'Radius' font ',22' offset 0, -0.5\n";
    
    gp << "set xrange [0:" << max_radius << "]\n";
    gp << "set yrange [0:1.01]\n";
    gp << "set xtics font ',20'\n";
    gp << "set ytics font ',20'\n";
    
    gp << "set key at graph 0.08, graph 0.95 left top font ',20'\n";
    
    gp << "set style line 1 lc rgb '#0d61ec' lw 2\n";
    gp << "set style line 2 lc rgb '#24ae1d' lw 2\n";
    gp << "set style line 3 lc rgb '#ffae00' lw 2\n";
    gp << "set style line 4 lc rgb '#e70000' lw 2\n";
    gp << "set style line 5 lc rgb '#000000' pt 7 ps 0.5\n";
    
    gp << "set output \"Graphs/Deformation/" << iter << ".png\"\n";
    
    gp << "plot 'Data/Results_Exact.txt' using 1:2 smooth csplines ls 1 title '1', 'Data/Results_Exact.txt' using 1:3 smooth csplines ls 2 title '2', 'Data/Results_Exact.txt' using 1:4 smooth csplines ls 3 title '3', 'Data/Results_Exact.txt' using 1:5 smooth csplines ls 4 title '4', 'Data/Derivative_Critical_Pts.txt' notitle ls 5\n";
    
    gp << "set terminal pdfcairo size 3.8,3.5\n";
    
    gp << "set border 3\n";
    gp << "set grid\n";
    gp << "set bmargin 6\n";
    gp << "set lmargin 12\n";
    gp << "set tmargin 4\n";
    
    gp << "set title 'Packing Functions for the " << lattice_type << " Lattice' font ',22' offset 0, 0.5\n";
    gp << "set xlabel 'Radius' font ',22' offset 0, -0.5\n";
    
    gp << "set xrange [0:" << max_radius << "]\n";
    gp << "set yrange [0:1.01]\n";
    gp << "set xtics font ',20'\n";
    gp << "set ytics font ',20'\n";
    
    gp << "set key at graph 0.08, graph 0.95 left top font ',20'\n";
    
    gp << "set style line 1 lc rgb '#0d61ec' lw 2\n";
    gp << "set style line 2 lc rgb '#24ae1d' lw 2\n";
    gp << "set style line 3 lc rgb '#ffae00' lw 2\n";
    gp << "set style line 4 lc rgb '#e70000' lw 2\n";
    gp << "set style line 5 lc rgb '#000000' pt 7 ps 0.5\n";
    
    if (function_type == "At_Least")
    {
        gp << "set output \"Graphs/Packing Functions At Least.pdf\"\n";
        
        gp << "plot 'Data/Results_At_Least.txt' using 1:2 smooth csplines ls 1 title '1', 'Data/Results_At_Least.txt' using 1:3 smooth csplines ls 2 title '2', 'Data/Results_At_Least.txt' using 1:4 smooth csplines ls 3 title '3', 'Data/Results_At_Least.txt' using 1:5 smooth csplines ls 4 title '4', 'Data/Derivative_Critical_Pts.txt' notitle ls 5\n";
    }
    
    else if (function_type == "Exact")
    {
        gp << "set output \"Graphs/Packing Functions Exact.pdf\"\n";
        
        gp << "plot 'Data/Results_Exact.txt' using 1:2 smooth csplines ls 1 title '1', 'Data/Results_Exact.txt' using 1:3 smooth csplines ls 2 title '2', 'Data/Results_Exact.txt' using 1:4 smooth csplines ls 3 title '3', 'Data/Results_Exact.txt' using 1:5 smooth csplines ls 4 title '4', 'Data/Derivative_Critical_Pts.txt' notitle ls 5\n";
    }
    
    gp << "unset yrange\n";
    
    gp << "set output \"Graphs/First Derivatives/F1 First Derivative.pdf\"\n";
    
    gp << "set title 'First Derivative of f_1' font ',22' offset 0,0.5\n";
    
    gp << "set key at graph -0.05, graph 0.97 left top font ',20'\n";
    
    gp << "plot 'Data/First_Derivs.txt' using 1:2 title 'First Derivative' smooth csplines ls 1\n";
    
    gp << "set output \"Graphs/First Derivatives/F2 First Derivative.pdf\"\n";
    
    gp << "set title 'First Derivative of f_2' font ',22' offset 0,0.5\n";
    
    gp << "plot 'Data/First_Derivs.txt' using 1:3 title 'First Derivative' smooth csplines ls 2\n";
    
    gp << "set output \"Graphs/First Derivatives/F3 First Derivative.pdf\"\n";
    
    gp << "set title 'First Derivative of f_3' font ',22' offset 0,0.5\n";
    
    gp << "plot 'Data/First_Derivs.txt' using 1:4 title 'First Derivative' smooth csplines ls 3\n";
    
    gp << "set output \"Graphs/First Derivatives/F4 First Derivative.pdf\"\n";
    
    gp << "set title 'First Derivative of f_4' font ',22' offset 0,0.5\n";
    
    gp << "plot 'Data/First_Derivs.txt' using 1:5 title 'First Derivative' smooth csplines ls 4\n";
    
    gp << "set output \"Graphs/First Derivatives/First Derivatives.pdf\"\n";
    
    gp << "set title 'First Derivatives' font ',22' offset 0,0.5\n";
    
    gp << "plot 'Data/First_Derivs.txt' using 1:2 title '1' smooth csplines ls 1, 'Data/First_Derivs.txt' using 1:3 title '2' smooth csplines ls 2, 'Data/First_Derivs.txt' using 1:4 title '3' smooth csplines ls 3, 'Data/First_Derivs.txt' using 1:5 title '4' smooth csplines ls 4\n";
    
    gp << "set output \"Graphs/Second Derivatives/F1 Second Derivative.pdf\"\n";
    
    gp << "set title 'Second Derivative of f_1' font ',22' offset 0,0.5\n";
    
    gp << "set key at graph 0.5, graph 0.2 center top font ',20'\n";
    
    gp << "plot 'Data/Second_Derivs.txt' using 1:2 title 'Second Derivative' smooth csplines ls 1\n";
    
    gp << "set output \"Graphs/Second Derivatives/F2 Second Derivative.pdf\"\n";
    
    gp << "set title 'Second Derivative of f_2' font ',22' offset 0,0.5\n";
    
    gp << "plot 'Data/Second_Derivs.txt' using 3:4 title 'Second Derivative' smooth csplines ls 2\n";
    
    gp << "set output \"Graphs/Second Derivatives/F3 Second Derivative.pdf\"\n";
    
    gp << "set title 'Second Derivative of f_3' font ',22' offset 0,0.5\n";
    
    gp << "plot 'Data/Second_Derivs.txt' using 5:6 title 'Second Derivative' smooth csplines ls 3\n";
    
    gp << "set output \"Graphs/Second Derivatives/F4 Second Derivative.pdf\"\n";
    
    gp << "set title 'Second Derivative of f_4' font ',22' offset 0,0.5\n";
    
    gp << "plot 'Data/Second_Derivs.txt' using 7:8 title 'Second Derivative' smooth csplines ls 4\n";
    
    gp << "set output \"Graphs/Second Derivatives/Second Derivatives.pdf\"\n";
    
    gp << "set title 'Second Derivatives' font ',22' offset 0,0.5\n";
    
    gp << "plot 'Data/Second_Derivs.txt' using 1:2 title '1' smooth csplines ls 1, 'Data/Second_Derivs.txt' using 3:4 title '2' smooth csplines ls 2, 'Data/Second_Derivs.txt' using 5:6 title '3' smooth csplines ls 3, 'Data/Second_Derivs.txt' using 7:8 title '4' smooth csplines ls 4\n";
}
