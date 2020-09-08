execute () {
    algo=$1
    n=$2
    path="../output"
    fname="${path}/${algo}_${n}"
    echo Computing for n = $n
    ./main.exe $n $fname $algo && \
    # valgrind --leak-check=yes ./main.exe $n $fname $algo > $fname && \
    echo Plotting  for n = $n && \
    python3 plot.py $n $fname
}

if [ "$1" == "all" ]; then
    declare -a algos
    algos=(
        "fast"
        "slow"
    )
    for algo in ${algos[@]}; do
        echo
        echo $algo
        declare -i i=2
        while [ $i -le 6 ]; do
            echo
            execute $algo $i
            (( i++ ))
        done
        python3 table_of_errors.py $algo
    done
    algo="LU"   # We want to run this algo only up to n=4
    echo
    echo $algo
    declare -i i=2
    while [ $i -le 4 ]; do
        echo
        execute $algo $i
        (( i++ ))
    done
    python3 table_of_errors.py $algo

elif [ $# -eq 2 ]; then
    execute $1 $2
else
    echo Please provide the arguments described in README.md
    exit 1
fi
