$MINDIAM = 0.001
$DBH_ERROR_TOL = 0.20
$POSITION_ERROR_TOL = 0.25

$new_dir = Get-Date -format MM-dd-yyyy-HH_mm_ss
$DIR="test_results\$new_dir $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL"
mkdir $DIR

echo "Debut du test dalignement des scans de JFC avec la librairie TargetlessRegistration"
# TEST REGULIER COMPLET
# On aligne seulement dans une direction, par exemple si on teste 1-5 -> 1-4, on ne teste pas 1-4 -> 1-5.
# l'algorithme est "commutatif", c-a-d marche aussi bien quand on inverse la source et le target.

# Savanne
<# & "./TLR.exe" stem_maps\savanne_stemMap25.txt stem_maps\savanne_stemMap24.txt   $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result_savanne25to24.txt"
python python_utils\put_error_reg_report.py answers\savanne_25to24.txt "$DIR\result_savanne25to24.txt"

& "./TLR.exe" stem_maps\savanne_stemMap26.txt stem_maps\savanne_stemMap24.txt   $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result_savanne26to24.txt"
python python_utils\put_error_reg_report.py answers\savanne_26to24.txt "$DIR\result_savanne26to24.txt"

& "./TLR.exe" stem_maps\savanne_stemMap26.txt stem_maps\savanne_stemMap25.txt   $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result_savanne26to25.txt"
python python_utils\put_error_reg_report.py answers\savanne_26to25.txt "$DIR\result_savanne26to25.txt"

& "./TLR.exe" stem_maps\savanne_stemMap27.txt stem_maps\savanne_stemMap24.txt   $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result_savanne27to24.txt"
python python_utils\put_error_reg_report.py answers\savanne_27to24.txt "$DIR\result_savanne27to24.txt"

& "./TLR.exe" stem_maps\savanne_stemMap27.txt stem_maps\savanne_stemMap25.txt   $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result_savanne27to25.txt"
python python_utils\put_error_reg_report.py answers\savanne_27to25.txt "$DIR\result_savanne27to25.txt"

& "./TLR.exe" stem_maps\savanne_stemMap27.txt stem_maps\savanne_stemMap26.txt   $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result_savanne27to26.txt"
python python_utils\put_error_reg_report.py answers\savanne_27to26.txt "$DIR\result_savanne27to26.txt"


# Premiere parcelle valcartier
$MINDIAM = 0.001
$DBH_ERROR_TOL = 0.25
$POSITION_ERROR_TOL = 0.12
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

# Deuxieme parcelle valcartier

& "./TLR.exe" stem_maps\stemMap5-2inversed.txt stem_maps\stemMap5-1.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result5-2to5-1.txt"
python python_utils\put_error_reg_report.py answers\5-2to5-1.txt "$DIR\result5-2to5-1.txt"

& "./TLR.exe" stem_maps\stemMap5-3inversed.txt stem_maps\stemMap5-1.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result5-3to5-1.txt"
python python_utils\put_error_reg_report.py answers\5-3to5-1.txt "$DIR\result5-3to5-1.txt"

& "./TLR.exe" stem_maps\stemMap5-3inversed.txt stem_maps\stemMap5-2inversed.txt $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result5-3to5-2.txt"
python python_utils\put_error_reg_report.py answers\5-3to5-2.txt "$DIR\result5-3to5-2.txt"

& "./TLR.exe" stem_maps\stemMap5-4inversed.txt stem_maps\stemMap5-1.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result5-4to5-1.txt"
python python_utils\put_error_reg_report.py answers\5-4to5-1.txt "$DIR\result5-4to5-1.txt"

& "./TLR.exe" stem_maps\stemMap5-4inversed.txt stem_maps\stemMap5-2inversed.txt $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result5-4to5-2.txt"
python python_utils\put_error_reg_report.py answers\5-4to5-2.txt "$DIR\result5-4to5-2.txt"

& "./TLR.exe" stem_maps\stemMap5-4inversed.txt stem_maps\stemMap5-3inversed.txt $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result5-4to5-3.txt"
python python_utils\put_error_reg_report.py answers\5-4to5-3.txt "$DIR\result5-4to5-3.txt"

& "./TLR.exe" stem_maps\stemMap5-5inversed.txt stem_maps\stemMap5-1.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result5-5to5-1.txt"
python python_utils\put_error_reg_report.py answers\5-5to5-1.txt "$DIR\result5-5to5-1.txt"

& "./TLR.exe" stem_maps\stemMap5-5inversed.txt stem_maps\stemMap5-2inversed.txt $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result5-5to5-2.txt"
python python_utils\put_error_reg_report.py answers\5-5to5-2.txt "$DIR\result5-5to5-2.txt"

& "./TLR.exe" stem_maps\stemMap5-5inversed.txt stem_maps\stemMap5-3inversed.txt $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result5-5to5-3.txt"
python python_utils\put_error_reg_report.py answers\5-5to5-3.txt "$DIR\result5-5to5-3.txt"

& "./TLR.exe" stem_maps\stemMap5-5inversed.txt stem_maps\stemMap5-4inversed.txt $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\result5-5to5-4.txt"
python python_utils\put_error_reg_report.py answers\5-5to5-4.txt "$DIR\result5-5to5-4.txt" #>

# Sequoias
& "./TLR.exe" stem_maps\sequoia2.txt stem_maps\sequoia1.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia2toSequoia1.txt"
python python_utils\put_error_reg_report.py answers\sequoia2to1.txt "$DIR\resultSequoia2toSequoia1.txt"
& "./TLR.exe" stem_maps\sequoia3.txt stem_maps\sequoia1.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia3toSequoia1.txt"
python python_utils\put_error_reg_report.py answers\sequoia3to1.txt "$DIR\resultSequoia3toSequoia1.txt"
& "./TLR.exe" stem_maps\sequoia3.txt stem_maps\sequoia2.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia3toSequoia2.txt"
python python_utils\put_error_reg_report.py answers\sequoia3to2.txt "$DIR\resultSequoia3toSequoia2.txt"
& "./TLR.exe" stem_maps\sequoia4.txt stem_maps\sequoia1.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia4toSequoia1.txt"
python python_utils\put_error_reg_report.py answers\sequoia4to1.txt "$DIR\resultSequoia4toSequoia1.txt"
& "./TLR.exe" stem_maps\sequoia4.txt stem_maps\sequoia2.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia4toSequoia2.txt"
python python_utils\put_error_reg_report.py answers\sequoia4to2.txt "$DIR\resultSequoia4toSequoia2.txt"
& "./TLR.exe" stem_maps\sequoia4.txt stem_maps\sequoia3.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia4toSequoia3.txt"
python python_utils\put_error_reg_report.py answers\sequoia4to3.txt "$DIR\resultSequoia4toSequoia3.txt"
& "./TLR.exe" stem_maps\sequoia5.txt stem_maps\sequoia1.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia5toSequoia1.txt"
python python_utils\put_error_reg_report.py answers\sequoia5to1.txt "$DIR\resultSequoia5toSequoia1.txt"
& "./TLR.exe" stem_maps\sequoia5.txt stem_maps\sequoia2.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia5toSequoia2.txt"
python python_utils\put_error_reg_report.py answers\sequoia5to2.txt "$DIR\resultSequoia5toSequoia2.txt"
& "./TLR.exe" stem_maps\sequoia5.txt stem_maps\sequoia3.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia5toSequoia3.txt"
python python_utils\put_error_reg_report.py answers\sequoia5to3.txt "$DIR\resultSequoia5toSequoia3.txt"
& "./TLR.exe" stem_maps\sequoia5.txt stem_maps\sequoia4.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia5toSequoia4.txt"
python python_utils\put_error_reg_report.py answers\sequoia5to4.txt "$DIR\resultSequoia5toSequoia4.txt"
& "./TLR.exe" stem_maps\sequoia6.txt stem_maps\sequoia1.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia6toSequoia1.txt"
python python_utils\put_error_reg_report.py answers\sequoia6to1.txt "$DIR\resultSequoia6toSequoia1.txt"
& "./TLR.exe" stem_maps\sequoia6.txt stem_maps\sequoia2.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia6toSequoia2.txt"
python python_utils\put_error_reg_report.py answers\sequoia6to2.txt "$DIR\resultSequoia6toSequoia2.txt"
& "./TLR.exe" stem_maps\sequoia6.txt stem_maps\sequoia3.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia6toSequoia3.txt"
python python_utils\put_error_reg_report.py answers\sequoia6to3.txt "$DIR\resultSequoia6toSequoia3.txt"
& "./TLR.exe" stem_maps\sequoia6.txt stem_maps\sequoia4.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia6toSequoia4.txt"
python python_utils\put_error_reg_report.py answers\sequoia6to4.txt "$DIR\resultSequoia6toSequoia4.txt"
& "./TLR.exe" stem_maps\sequoia6.txt stem_maps\sequoia5.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia6toSequoia5.txt"
python python_utils\put_error_reg_report.py answers\sequoia6to5.txt "$DIR\resultSequoia6toSequoia5.txt"
& "./TLR.exe" stem_maps\sequoia7.txt stem_maps\sequoia1.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia7toSequoia1.txt"
python python_utils\put_error_reg_report.py answers\sequoia7to1.txt "$DIR\resultSequoia7toSequoia1.txt"
& "./TLR.exe" stem_maps\sequoia7.txt stem_maps\sequoia2.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia7toSequoia2.txt"
python python_utils\put_error_reg_report.py answers\sequoia7to2.txt "$DIR\resultSequoia7toSequoia2.txt"
& "./TLR.exe" stem_maps\sequoia7.txt stem_maps\sequoia3.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia7toSequoia3.txt"
python python_utils\put_error_reg_report.py answers\sequoia7to3.txt "$DIR\resultSequoia7toSequoia3.txt"
& "./TLR.exe" stem_maps\sequoia7.txt stem_maps\sequoia4.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia7toSequoia4.txt"
python python_utils\put_error_reg_report.py answers\sequoia7to4.txt "$DIR\resultSequoia7toSequoia4.txt"
& "./TLR.exe" stem_maps\sequoia7.txt stem_maps\sequoia5.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia7toSequoia5.txt"
python python_utils\put_error_reg_report.py answers\sequoia7to5.txt "$DIR\resultSequoia7toSequoia5.txt"
& "./TLR.exe" stem_maps\sequoia7.txt stem_maps\sequoia6.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia7toSequoia6.txt"
python python_utils\put_error_reg_report.py answers\sequoia7to6.txt "$DIR\resultSequoia7toSequoia6.txt"
& "./TLR.exe" stem_maps\sequoia8.txt stem_maps\sequoia1.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia8toSequoia1.txt"
python python_utils\put_error_reg_report.py answers\sequoia8to1.txt "$DIR\resultSequoia8toSequoia1.txt"
& "./TLR.exe" stem_maps\sequoia8.txt stem_maps\sequoia2.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia8toSequoia2.txt"
python python_utils\put_error_reg_report.py answers\sequoia8to2.txt "$DIR\resultSequoia8toSequoia2.txt"
& "./TLR.exe" stem_maps\sequoia8.txt stem_maps\sequoia3.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia8toSequoia3.txt"
python python_utils\put_error_reg_report.py answers\sequoia8to3.txt "$DIR\resultSequoia8toSequoia3.txt"
& "./TLR.exe" stem_maps\sequoia8.txt stem_maps\sequoia4.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia8toSequoia4.txt"
python python_utils\put_error_reg_report.py answers\sequoia8to4.txt "$DIR\resultSequoia8toSequoia4.txt"
& "./TLR.exe" stem_maps\sequoia8.txt stem_maps\sequoia5.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia8toSequoia5.txt"
python python_utils\put_error_reg_report.py answers\sequoia8to5.txt "$DIR\resultSequoia8toSequoia5.txt"
& "./TLR.exe" stem_maps\sequoia8.txt stem_maps\sequoia6.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia8toSequoia6.txt"
python python_utils\put_error_reg_report.py answers\sequoia8to6.txt "$DIR\resultSequoia8toSequoia6.txt"
& "./TLR.exe" stem_maps\sequoia8.txt stem_maps\sequoia7.txt         $MINDIAM $DBH_ERROR_TOL $POSITION_ERROR_TOL > "$DIR\resultSequoia8toSequoia7.txt"
python python_utils\put_error_reg_report.py answers\sequoia8to7.txt "$DIR\resultSequoia8toSequoia7.txt"
echo FIN
