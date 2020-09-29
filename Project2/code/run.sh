execute () {
    if [ "${3}" == "0" ]; then
        endl=""
    else
        endl=", omega_r = ${3}"
    fi
    echo Computing $2 with n = ${1}${endl}
    ./main.exe $1 $2 $3
    if [ $? -ne 0 ]; then
        exit 1
    fi
    echo "    Plotting"
    python3 plot.py $2 $1 $3
    if [ $? -ne 0 ]; then
        exit 1
    fi
}

declare -a algos
declare -a omega_rs
declare -a ns
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
                    execute $n $algo $omega_r
                done
                echo "    Plotting for all omega"
                python3 plot.py $algo $n 0 
                if [ $? -ne 0 ]; then
                    exit 1
                fi
            else
                execute $n $algo 0
            fi
        done
    done
else
    if [ "$2" == "QM2" ]; then
        execute $1 $2 $3
    else
        execute $1 $2 0
    fi
fi
