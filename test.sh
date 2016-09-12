# Ce script essai d'aligner 5 scans de Jean-Francois Cote ensemble.
# Les resultats sont enregistre dans le dossier du format "mois-jour-annee-heure"
# Eventuellement on va utiliser ce script pour d'autre scan et faire un test plus
# massif.
#
# Cree le 9 septembre 2016 par Jean-Francois Tremblay.


NOW=$(date +"%m-%d-%Y-%T")
DIR="test_results/$NOW"
mkdir $DIR

echo Debut du test d\'alignement des scans de JFC avec la librairie TargetlessRegistration
# TEST REGULIER
#./TLR 'stem_maps/stemMap1-2inversed.txt' 'stem_maps/stemMap1-1.txt' 0.02 0.25 0.05 > "$DIR/result1-2to1-1.txt"
#./TLR 'stem_maps/stemMap1-3inversed.txt' 'stem_maps/stemMap1-1.txt' 0.02 0.25 0.05 > "$DIR/result1-3to1-1.txt"
#./TLR 'stem_maps/stemMap1-4inversed.txt' 'stem_maps/stemMap1-1.txt' 0.02 0.25 0.05 > "$DIR/result1-4to1-1.txt"
#./TLR 'stem_maps/stemMap1-5inversed.txt' 'stem_maps/stemMap1-1.txt' 0.02 0.25 0.05 > "$DIR/result1-5to1-1.txt"
# TEST SPECIAL : on aligne 1-5 vers 1-4
./TLR 'stem_maps/stemMap1-5inversed.txt' 'stem_maps/stemMap1-4inversed.txt' 0.07 0.25 0.05 > "$DIR/result1-5to1-4.txt"
echo FIN
