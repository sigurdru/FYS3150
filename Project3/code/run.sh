calc_and_plot ()
{
    input_fname=$1
    dt=$2
    N=$3
    solver_method=$4
    beta=$5
    projection=$6
    output_fname="${input_fname}-${solver_method}-${dt}-${N}-${beta}"
    ./main.exe $input_fname $dt $N $solver_method $beta
    if [ $? -ne 0 ]; then
        exit 1
    fi
    python3 plot.py $output_fname $projection
    if [ $? -ne 0 ]; then
        exit 1
    fi
}

produce_circ_orbit ()
{
    echo Circular orbit
    declare -a methods dts
    methods=(
        "euler"
        "verlet"
    )
    dts=(
        "2"
        "3"
        "4"
        "5"
    )
    for method in ${methods[@]}; do
        echo "    Method: $method"
        printf "        dt:"
        for dt in ${dts[@]};do
            printf " $dt"
            N=$(($dt + 2 ))
            output_fname="earth_sun_circ-${method}-${dt}-${N}-2"
            output_fname="../output/reports/${output_fname}.txt"
            calc_and_plot earth_sun_circ $dt $N $method 2 > $output_fname &
        done
        echo
    done
    wait
}

produce_beta ()
{
    echo Testing betas
    declare -a fnames betas
    fnames=(
        "earth_sun_circ"
        "earth_sun_ellip"
    )
    betas=(
        "2"
        "2.25"
        "2.5"
        "2.75"
        "3"
    )
    dt="3"
    N=$(($dt + 2))
    method="verlet"
    for fname in ${fnames[@]}; do
        echo "    File: $fname"
        printf "        beta:"
        for beta in ${betas[@]}; do
            printf " $beta"
            output_fname="${fname}-${method}-${dt}-${N}-${beta}"
            output_fname="../output/reports/${output_fname}.txt"
            calc_and_plot $fname $dt $N $method $beta > $output_fname &
        done
        echo
    done
    wait
}

produce_esc_vel ()
{
    echo Escape velocity
    path="../output/reports"
    output_fname="earth_sun_escape-escape-4-6-2"
    output_fname="${path}/${output_fname}.txt"
    ./main.exe earth_sun_escape 4 6 escape 2 > $output_fname
    cat $output_fname | tail -n 2
}

produce_three_body ()
{
    echo Three-body simulation
    declare -a fnames dts
    fnames=(
        "three_body"
        "three_body10"
        "three_body1000"
    )
    dts=(
        "3"
        "4"
        "5"
    )
    beta="2"
    solver_method="verlet"
    for fname in ${fnames[@]}; do
        echo "    File: $fname"
        printf "        dt:"
        for dt in ${dts[@]}; do
            printf " $dt"
            N=$(($dt + 1 ))
            output_fname="${fname}-${solver_method}-${dt}-${N}-${beta}"
            output_fname="../output/reports/${output_fname}.txt"
            calc_and_plot $fname $dt $N $solver_method $beta > $output_fname &
        done
        echo
    done
    wait
}

produce_mercury ()
{
    echo Mercury
    path="../output/reports"
    output_fname="mercury_relativistic-mercury-6-8-2"
    output_fname="${path}/${output_fname}.txt"
    calc_and_plot mercury_relativistic 6 8 mercury 2 > $output_fname
}

produce_solar_system()
{
    echo Solar system
    path="../output/reports"
    output_fname="all-verlet-5-8-2"
    output_fname="${path}/${output_fname}.txt"
    calc_and_plot all 5 8 verlet 2 > $output_fname
}

produce_all_results ()
{
    produce_circ_orbit
    produce_beta
    produce_three_body
    produce_solar_system &
    produce_mercury &
    produce_esc_vel &
    wait
}

HELPFUL_MSG="Option must be \"all\", \"circ\", \"beta\", \"escape_vel\", \"three_body\", \"mercury\" or \"solar_system\""

if [ "$#" -eq "1" ]; then
    option=$1
    case "$option" in 
        "all")
        produce_all_results; ;;
        "circ")
        produce_circ_orbit; ;;
        "beta")
        produce_beta; ;;
        "escape_vel")
        produce_esc_vel; ;;
        "three_body")
        produce_three_body; ;;
        "mercury")
        produce_mercury; ;;
        "solar_system")
        produce_solar_system; ;;
        *)
        echo ${HELPFUL_MSG}; exit 1 ;;
    esac
elif [ "$#" -lt "5" ]; then
    echo Specify an option to produce several results at once:
    echo $HELPFUL_MSG
    echo example: bash run.sh all
    echo
    echo Or run directly with parameters:
    echo "   - input file (\"all\", \"earth_sun_circ\" etc.)"
    echo "   - dt (\"2\", \"3\", \"4\", ...)"
    echo "   - number of time steps (\"2\", \"3\", \"4\", ...)"
    echo "   - solver method (\"euler\", \"verlet\" or \"mercury\")"
    echo "   - distance dependence parameter beta (\"2\" for normal inverse square gravity)"
    echo "   - optional, projection for plots (\"2D\" or \"3D\")"
    exit 1
else
    calc_and_plot $@
fi
