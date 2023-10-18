#!/bin/bash

obj="build/source/triag"

test_files_names=("01.dat" "02.dat" "03.dat" "04.dat" "05.dat" "06.dat" "07.dat" "08.dat" "09.dat" "10.dat" "11.dat" "12.dat" "tst1.dat")
tests_folder="test/tests/"

answer_files_names=("01.ans" "02.ans" "03.ans" "04.ans" "05.ans" "06.ans" "07.ans" "08.ans" "09.ans" "10.ans" "11.ans" "12.ans" "tst1.ans")
answers_folder="test/answers/"
correct_answers_folder="test/correct_answers/"


echo "diffs with expected answers:"
echo
for i in ${!test_files_names[@]}; do
    echo $i
    ${obj} < ${tests_folder}${test_files_names[$i]} > ${answers_folder}${answer_files_names[$i]}
    diff ${correct_answers_folder}${answer_files_names[$i]} ${answers_folder}${answer_files_names[$i]}
done
