declare -a bodies
bodies=(
    "sun"
    "mercury"
    "venus"
    "earth"
    "mars"
    "jupiter"
    "saturn"
    "uranus"
    "neptune"
    "pluto"
)

outfname="../planets_IC.csv"
echo planet, date, x, y, z, vx, vy, vz > $outfname

for body in ${bodies[@]}; do
    fname="${body}.csv"
    line=`cat $fname | head -n 23 | tail -n 1 | cut -d"," -f2-`
    line=`echo $line | cut -d" " -f2-2,4-`
    echo ${body}, ${line} >> $outfname
done
