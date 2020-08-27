if [ $# -eq 2 ]; then
    algo=$1
    n=$2
else
    echo Please provide the arguments described in README, f.ex.:
    echo bash $0 1001 slow
    exit 1
fi
fname="../output/output_${n}.txt"
echo Computing
./main.exe $n $fname $algo > $fname && \
echo Plotting
python3 plot.py $n $fname
