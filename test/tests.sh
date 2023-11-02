#!/bin/bash

obj="build/src/triag"

test_files_names=(  "01.dat" "02.dat" "03.dat" "04.dat" "05.dat" "06.dat" "07.dat" "08.dat" "11v.dat" "13.dat" "14.dat" "16.dat" "17.dat" "18.dat" "19.dat" "20.dat" "20v.dat" "09.dat" "10.dat" "11.dat" "15.dat" "12.dat" "tst1.dat")
tests_folder="test/tests/"

answer_files_names=("01.ans" "02.ans" "03.ans" "04.ans" "05.ans" "06.ans" "07.ans" "08.ans" "11v.ans" "13.ans" "14.ans" "16.ans" "17.ans" "18.ans" "19.ans" "20.ans" "20v.ans" "09.ans" "10.ans" "11.ans" "15.ans" "12.ans" "tst1.ans")
answers_folder="test/answers/"
correct_answers_folder="test/correct_answers/"


echo "diffs with expected answers:" 
echo
for i in ${!test_files_names[@]}; do
    #echo $i
    time ${obj} < ${tests_folder}${test_files_names[$i]} > ${answers_folder}${answer_files_names[$i]}
    diff ${correct_answers_folder}${answer_files_names[$i]} ${answers_folder}${answer_files_names[$i]}
done
