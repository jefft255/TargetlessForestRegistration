$MINDIAM = 0.001
$DBH_ERROR_TOL = 0.25
$POSITION_ERROR_TOL = 0.10
$new_dir = Get-Date -format MM-dd-yyyy-HH_mm_ss
$DIR="test_results\$new_dir $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL"
mkdir $DIR

echo "Debut du test dalignement des scans de JFC avec la librairie TargetlessRegistration"
# TEST REGULIER COMPLET
# On aligne seulement dans une direction, par exemple si on teste 1-5 -> 1-4, on ne teste pas 1-4 -> 1-5.
# l'algorithme est "commutatif", c-a-d marche aussi bien quand on inverse la source et le target.

& "./TLR.exe" stem_maps\stemMap1-2inversed.txt stem_maps\stemMap1-1.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result1-2to1-1.txt"
python python_utils\put_error_reg_report.py answers\1-2to1-1.txt "$DIR\result1-2to1-1.txt"

& "./TLR.exe" stem_maps\stemMap1-3inversed.txt stem_maps\stemMap1-1.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result1-3to1-1.txt"
python python_utils\put_error_reg_report.py answers\1-3to1-1.txt "$DIR\result1-3to1-1.txt"

& "./TLR.exe" stem_maps\stemMap1-3inversed.txt stem_maps\stemMap1-2inversed.txt $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result1-3to1-2.txt"
python python_utils\put_error_reg_report.py answers\1-3to1-2.txt "$DIR\result1-3to1-2.txt"

& "./TLR.exe" stem_maps\stemMap1-4inversed.txt stem_maps\stemMap1-1.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result1-4to1-1.txt"
python python_utils\put_error_reg_report.py answers\1-4to1-1.txt "$DIR\result1-4to1-1.txt"

& "./TLR.exe" stem_maps\stemMap1-4inversed.txt stem_maps\stemMap1-2inversed.txt $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result1-4to1-2.txt"
python python_utils\put_error_reg_report.py answers\1-4to1-2.txt "$DIR\result1-4to1-2.txt"

& "./TLR.exe" stem_maps\stemMap1-4inversed.txt stem_maps\stemMap1-3inversed.txt $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result1-4to1-3.txt"
python python_utils\put_error_reg_report.py answers\1-4to1-3.txt "$DIR\result1-4to1-3.txt"

& "./TLR.exe" stem_maps\stemMap1-5inversed.txt stem_maps\stemMap1-1.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result1-5to1-1.txt"
python python_utils\put_error_reg_report.py answers\1-5to1-1.txt "$DIR\result1-5to1-1.txt"

& "./TLR.exe" stem_maps\stemMap1-5inversed.txt stem_maps\stemMap1-2inversed.txt $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result1-5to1-2.txt"
python python_utils\put_error_reg_report.py answers\1-5to1-2.txt "$DIR\result1-5to1-2.txt"

& "./TLR.exe" stem_maps\stemMap1-5inversed.txt stem_maps\stemMap1-3inversed.txt $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result1-5to1-3.txt"
python python_utils\put_error_reg_report.py answers\1-5to1-3.txt "$DIR\result1-5to1-3.txt"

& "./TLR.exe" stem_maps\stemMap1-5inversed.txt stem_maps\stemMap1-4inversed.txt $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result1-5to1-4.txt"
python python_utils\put_error_reg_report.py answers\1-5to1-4.txt "$DIR\result1-5to1-4.txt"

echo FIN