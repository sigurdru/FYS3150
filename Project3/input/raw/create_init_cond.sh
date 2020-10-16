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
num_bodies=${#bodies[@]}
echo $num_bodies > $outfname
# echo planet, date, x, y, z, vx, vy, vz >> $outfname

for body in ${bodies[@]}; do
    fname="${body}.csv"
    line=`cat $fname | head -n 23 | tail -n 1 | cut -d"," -f2-`
    # line1=`echo $line | cut -d" " -f2`
    line2=`echo $line | cut -d" " -f4-`
    # echo ${body}, ${line1}, ${line2} #>> $outfname

    mass=`cat masses_in_kg.txt | grep $body | cut -d" " -f2`

    echo $mass ${line2} >> $outfname
done
