
L="2"
T_start="1"
dT="0"
N_T="0"
N_carl="100000"
random_init="true"
spin_plot="true"

if [ $random_init == "true" ]; then
    config="random"
else
    config="up"
fi

fname="${L}_${config}_ExpVals.csv"

./main.exe $L $T_start $dT $N_T $N_carl $random_init $spin_plot
python3 plot.py $fname $L plot_comparison
