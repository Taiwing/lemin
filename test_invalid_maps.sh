path="/Users/trponess/Documents/lemin_c/maps/invalid_maps"
nb_files=`ls $path | wc -l`
echo "LAUNCHING LEMIN PARSER ON" $path
echo "nb of files to check : " $nb_files
i=0
printf "\n\n\n"
for invalid_map in /Users/trponess/Documents/lemin_c/maps/invalid_maps/*;
do
    echo "-------------------------------file" $i")" $invalid_map "-------------------------------"
    echo doing..
    #./lem_in invalid_map
    echo "-------------------------------" DONE "-------------------------------"
    i=$((i+1))
done