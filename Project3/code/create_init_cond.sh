### Run from within the code directory

declare -a bodies

### bodies should be a list of the bodies you want to include in the simulation
### comment out the other bodies
bodies=(
    "sun"
    "mercury"
    # "venus"
    # "earth"
    # "mars"
    # "jupiter"
    # "saturn"
    # "uranus"
    # "neptune"
    # "pluto"
    # "europa"
)

### give the IC file an appropriate name
# fname="earth_sun_circ"
fname="mercury_relativistic"
# fname="three_body"
# fname="three_body10"
# fname="three_body1000"
# fname="planets"
# fname="all"


### the rest is handled automatically
num_bodies=${#bodies[@]}
outfname="../input/${fname}.txt"
path="../input/raw"
echo $num_bodies > $outfname

for body in ${bodies[@]}; do
    fname="${path}/${body}.csv"
    line=`cat $fname | head -n 23 | tail -n 1 | cut -d"," -f2-`
    line=`echo $line | cut -d" " -f4- | tr ',' ' '`

    mass=`cat ${path}/masses_in_kg.txt | grep $body | cut -d" " -f2-`

    echo $body $mass $line >> $outfname
done
