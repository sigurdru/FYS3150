declare -a algos
algos=(
    "fast"
    "slow"
)
for algo in ${algos[@]}; do
    echo
    fname="../output/test_result_${algo}"
    ./test_lineq.exe $fname $algo
    python3 test_results_verify.py $fname && \
    echo The $algo algorithm has passed the test
    rm "${fname}_error.txt"
done

