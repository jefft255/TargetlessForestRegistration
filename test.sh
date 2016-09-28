# Ce script essai d'aligner 4 scans de Jean-Francois Cote ensemble.
# Les resultats sont enregistre dans le dossier du format "mois-jour-annee-heure"
# Eventuellement on va utiliser ce script pour d'autre scan et faire un test plus
# massif.
#
# Cree le 9 septembre 2016 par Jean-Francois Tremblay.


NOW=$(date +"%m-%d-%Y-%T")
DIR="test_results/$NOW"
mkdir $DIR

echo Debut du test d\'alignement des scans de JFC avec la librairie TargetlessRegistration
# TEST REGULIER COMPLET
# On aligne seulement dans une direction, par exemple si on teste 1-5 -> 1-4, on ne teste pas 1-4 -> 1-5.
# l'algorithme est "commutatif", c-a-d marche aussi bien quand on inverse la source et le target.

./TLR 'stem_maps/stemMap1-2inversed.txt' 'stem_maps/stemMap1-1.txt' 0.02 0.35 0.15 > "$DIR/result1-2to1-1.txt"
./TLR 'stem_maps/stemMap1-3inversed.txt' 'stem_maps/stemMap1-1.txt' 0.02 0.35 0.15 > "$DIR/result1-3to1-1.txt"
./TLR 'stem_maps/stemMap1-3inversed.txt' 'stem_maps/stemMap1-2inversed.txt' 0.02 0.35 0.15 > "$DIR/result1-3to1-2.txt"
./TLR 'stem_maps/stemMap1-4inversed.txt' 'stem_maps/stemMap1-1.txt' 0.02 0.35 0.15 > "$DIR/result1-4to1-1.txt"
./TLR 'stem_maps/stemMap1-4inversed.txt' 'stem_maps/stemMap1-2inversed.txt' 0.02 0.35 0.15 > "$DIR/result1-4to1-2.txt"
./TLR 'stem_maps/stemMap1-4inversed.txt' 'stem_maps/stemMap1-3inversed.txt' 0.02 0.35 0.15 > "$DIR/result1-4to1-3.txt"
./TLR 'stem_maps/stemMap1-5inversed.txt' 'stem_maps/stemMap1-1.txt' 0.02 0.35 0.15 > "$DIR/result1-5to1-1.txt"
./TLR 'stem_maps/stemMap1-5inversed.txt' 'stem_maps/stemMap1-2inversed.txt' 0.02 0.35 0.15 > "$DIR/result1-5to1-2.txt"
./TLR 'stem_maps/stemMap1-5inversed.txt' 'stem_maps/stemMap1-3inversed.txt' 0.02 0.35 0.15 > "$DIR/result1-5to1-3.txt"
./TLR 'stem_maps/stemMap1-5inversed.txt' 'stem_maps/stemMap1-4inversed.txt' 0.02 0.35 0.15 > "$DIR/result1-5to1-4.txt"

echo FIN
