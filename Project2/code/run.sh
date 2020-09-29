execute () {
    if [ "${4}" == "0" ]; then
        endl=""
    else
        endl=", omega_r = ${4}"
    fi
    echo Computing $2 with n = ${2}${endl}
    ./main.exe $1 $2 $3 $4
    if [ $? -ne 0 ]; then
        exit 1
    fi
    echo "    Plotting"
    python3 plot.py $3 $2 $4
    if [ $? -ne 0 ]; then
        exit 1
    fi
}

declare -a algos
declare -a omega_rs
declare -a ns
declare -i counter
algos=(
    "BB"
    "QM1"
    "QM2"
)
omega_rs=(
    "0.01"
    "0.5"
    "1"
    "5"
)
ns=(
    "10"
    "50"
    "100"
    "200"
)

if [ "$1" == "all" ]; then
    for algo in ${algos[@]}; do
        for n in ${ns[@]}; do
            if [ $algo == "QM2" ]; then
                for omega_r in ${omega_rs[@]}; do
                    execute 1 $n $algo $omega_r
                done
                echo "    Plotting for all omega"
                python3 plot.py $algo $n 0 
                if [ $? -ne 0 ]; then
                    exit 1
                fi
            else
                execute 1 $n $algo 0
            fi
        done
    done
elif [ "$1" == "time" ]; then
    declare -i lim
    for algo in ${algos[@]}; do
        for n in ${ns[@]}; do
            if [ $n -lt 150 ]; then
                lim=5
            else
                lim=3
            fi
            fname="../output/time_${algo}_${n}.txt"
            if [ -f $fname ]; then
                rm $fname
            fi
            counter=1
            printf "Timing ${algo} for n = ${n}:"
            while [ $counter -le $lim ]; do
                printf " ${counter}"
                if [ $algo == "QM2" ]; then
                    out=`./main.exe 0 $n $algo 0.05`
                else
                    out=`./main.exe 0 $n $algo 0`
                fi
                printf "$out" | cut -d":" -f2 | cut -d" " -f2 >> $fname
                (( counter++ ))
            done
            echo
        done
        echo
    done
    python3 time_table.py
else
    if [ "$2" == "QM2" ]; then
        execute 1 $1 $2 $3
    else
        execute 1 $1 $2 0
    fi
fi
