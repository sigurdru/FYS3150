path=../output/time_it
if ! [ -d $path ]; then
    mkdir $path
fi

declare -a algos
algos=(
    "fast"
    "slow"
    "LU"
)
declare -i n
declare -i i
declare -i upper_lim
for algo in ${algos[@]}; do
    echo
    echo $algo
    n=2
    if [ $algo == "fast" ]; then
        upper_lim=6
    elif [ $algo == "slow" ]; then
        upper_lim=6
    elif [ $algo == "LU" ]; then
        n=1
        upper_lim=4
    else
        echo Error in algorithm loop: $algo
        exit 1
    fi
    while [ $n -le $upper_lim ]; do
        i=1
        while [ $i -le 5 ]; do
            ./main.exe $n no_print $algo > ${path}/${algo}_${n}_${i}.txt
            (( i++ ))
        done
        (( n++ ))
    done
done
python3 time_it.py $path 6 5
