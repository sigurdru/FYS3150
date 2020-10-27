if [ "$#" -lt "5" ]; then
    echo Please include input file,
    echo dt, number of time steps,
    echo solver method and distance dependence parameter beta
else
    input_fname=$1
    dt=$2
    N=$3
    solver_method=$4
    beta=$5
    output_fname="${input_fname}-${solver_method}-${dt}-${N}-${beta}"
fi

./main.exe $input_fname $dt $N $solver_method $beta
python3 plot.py $output_fname 2D
