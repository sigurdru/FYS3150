if [ $# -gt 0 ]; then
    n=$1
else
    echo Please provide number of steps as argument, ex.:
    echo bash $0 1001
    exit 1
fi
fname="../output/output_${n}.txt"
./lineq.exe $n > $fname && \
python3 plot.py $n $fname
