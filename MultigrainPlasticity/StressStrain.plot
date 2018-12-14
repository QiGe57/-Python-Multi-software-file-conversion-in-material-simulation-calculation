set term post enh color eps size 8cm, 8cm #fontfile '~/.local/share/fonts/type1/linlibertiner.pfb' font 'LinLibertineO,20'

set style line 1 pt  4 lc rgb "#e41a1c" lw 4 lt 1
set style line 2 pt  8 lc rgb "#377eb8" lw 4 lt 1
set style line 3 pt  9 lc rgb "#4daf4a" lw 4 lt 1
set style line 4 pt 11 lc rgb "#984ea3" lw 2 lt 2
set style line 5 pt 13 lc rgb "#ff7f00" lw 2 lt 3
set style line 6 pt  5 lc rgb "#ffff33" lw 2
set style line 7 pt  6 lc rgb "#a65628" lw 2 lt 1
set style line 8 pt  6 lc rgb "#f781bf" lw 2 lt 1
set style line 9 pt  6 lc rgb "#999999" lw 2 lt 1
set style line 10 pt  7 lc rgb "black" lw 1 lt 1
set style line 11 pt  6 lc rgb "black" lw 1 lt 1
set style line 12 pt  8 lc rgb "black" lw 1 lt 1
set style line 13 pt  4 lc rgb "#e41a1c" lw 4 lt 3
set style line 14 pt  8 lc rgb "#377eb8" lw 4 lt 3
set style line 15 pt  9 lc rgb "#4daf4a" lw 4 lt 3
set style line 16 pt  7 lc rgb "black" lw 1 lt 3

set output "StressStrain.eps"

set xlabel "Strain"
set ylabel "Stress [MPa]"
set key top left

plot "avgStress.dat" u 1:($4/1e6) w l ls 2 title "Sigma_{zz}"#, "avgStress.dat" u 1:($2/1e6) w l ls 3 title "Sigma_{xx}", "avgStress.dat" u 1:($3/1e6) w l ls 4 title "Sigma_{yy}"


set output "AvgStrain.eps"
set xlabel "timestep"
set ylabel "Strain"
plot "avgStrain.dat" u 1:4 w l ls 2
