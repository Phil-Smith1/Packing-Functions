#include "gnuplot-iostream.h"

#include "Input3D.h"
#include "Graph_Parameters.h"

void Plot_Graph_Brillouin ( string const& directory3D, Input3D const& input, Graph_Parameters const& graph_params, int index )
{
    Gnuplot gp;
    
    gp << "cd \"" << directory3D << "\"\n";
    
    gp << "set terminal pdfcairo size 8.5, 3.5\n";
    
    gp << "set border 3\n";
    gp << "set grid\n";
    gp << "set bmargin 4.5\n";
    gp << "set lmargin 8.5\n";
    
    if (graph_params.title)
    {
        gp << "set tmargin 5\n";
        gp << "set title '" << graph_params.title_str << "' font ', 20' offset 0, 2\n";
    }
    
    else gp << "set tmargin 3\n";
    
    gp << "set rmargin 2\n";
    
    gp << "set ylabel '{/Symbol D}_i(r)' font ', 20' offset -0.5, 0\n";
    gp << "set xlabel 'Radius of Balls (Angstroms)' font ', 20' offset 0, -0.3\n";
    
    gp << "set xrange [0: " << input.max_radius << "]\n";
    gp << "set yrange [0: " << 1 << "]\n";
    gp << "set xtics font ', 18'\n";
    gp << "set ytics font ', 18'\n";
    
    gp << "set key horizontal at graph 0.5, graph 1.04 center bottom font ', 18'\n";
    
    gp << "set style line 1 lc rgb '#0d61ec' lw 3\n";
    gp << "set style line 2 lc rgb '#24ae1d' lw 3\n";
    gp << "set style line 3 lc rgb '#ffae00' lw 3\n";
    gp << "set style line 4 lc rgb '#e70000' lw 3\n";
    gp << "set style line 5 lc rgb '#db0dec' lw 3\n";
    gp << "set style line 6 lc rgb '#7B0985' lw 3\n";
    gp << "set style line 7 lc rgb '#87663E' lw 3\n";
    gp << "set style line 8 lc rgb '#000000' lw 3\n";
    gp << "set style line 9 lc rgb '#000000' pt 7 ps 0.5\n";
    gp << "set style line 11 dt 2 lc rgb '#0d61ec' lw 3\n";
    gp << "set style line 12 dt 2 lc rgb '#24ae1d' lw 3\n";
    gp << "set style line 13 dt 2 lc rgb '#ffae00' lw 3\n";
    gp << "set style line 14 dt 2 lc rgb '#e70000' lw 3\n";
    gp << "set style line 15 dt 2 lc rgb '#db0dec' lw 3\n";
    gp << "set style line 16 dt 2 lc rgb '#7B0985' lw 3\n";
    gp << "set style line 17 dt 2 lc rgb '#87663E' lw 3\n";
    gp << "set style line 18 dt 2 lc rgb '#000000' lw 3\n";
    
    gp << "set output \"Graphs/Brill/" + to_string( index ) + ".pdf\"\n";
    
    gp << "set samples 1000\n";
    
    string plot = "plot 'Data/Brill/" + to_string( index ) + ".txt' using 1:2 smooth csplines ls 1 title '{/Symbol D}_1(r)'";
    
    for (int counter = 1; counter < input.zone_limit - 1; ++counter)
    {
        plot += ", 'Data/Brill/" + to_string( index ) + ".txt' using 1:" + to_string( counter + 2 ) + "smooth csplines ls " + to_string( counter + 1 ) + " title '{/Symbol D}_" + to_string( counter + 1 ) + "(r)'";
    }
    
    plot += "\n";
    
    gp << plot;
}
