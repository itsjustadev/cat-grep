#!/bin/bash

TEST_FILE1="./test-files/test1.txt"
TEST_FILE2="./test-files/test2.txt"
TEST_FILE3="./test-files/weirdo.txt"
TEST_FILE4="./test-files/bytes.txt"
all_num=0
for var1 in -b -e -n -s -t -v
do
    for var2 in -b -e -n -s -t -v
    do
        for var3 in -b -e -n -s -t -v
        do
            TEST1="$var1 $var2 $var3 $TEST_FILE1"
            TEST2="$var1 $var2 $var3 $TEST_FILE2"
            TEST3="$var1 $var2 $var3 $TEST_FILE3"
            TEST4="$var1 $var2 $var3 $TEST_FILE4"
            LOG2="log.txt"
            echo $TEST1
            echo $TEST1
            ./s21_cat $TEST1 > s21_compare.txt
            cat $TEST1 > orig_compare.txt
            diff --suppress-common-lines -y s21_compare.txt orig_compare.txt  
            diff --suppress-common-lines -y s21_compare.txt orig_compare.txt  > $LOG2 
            diff --suppress-common-lines -y s21_compare.txt orig_compare.txt | wc -l | awk '{print "Error Num: "$1}'
            num_of_lines=$(< "$LOG2" wc -l)
            all_num=$((num_of_lines+all_num))
            echo $TEST2
            echo $TEST2
            ./s21_cat $TEST2 > s21_compare.txt
            cat $TEST2 > orig_compare.txt
            diff --suppress-common-lines -y s21_compare.txt orig_compare.txt  
            diff --suppress-common-lines -y s21_compare.txt orig_compare.txt  > $LOG2 
            diff --suppress-common-lines -y s21_compare.txt orig_compare.txt | wc -l | awk '{print "Error Num: "$1}'
            num_of_lines=$(< "$LOG2" wc -l)
            all_num=$((num_of_lines+all_num))
            echo $TEST3
            echo $TEST3
            ./s21_cat $TEST3 > s21_compare.txt
            cat $TEST3 > orig_compare.txt
            diff --suppress-common-lines -y s21_compare.txt orig_compare.txt  
            diff --suppress-common-lines -y s21_compare.txt orig_compare.txt  > $LOG2 
            diff --suppress-common-lines -y s21_compare.txt orig_compare.txt | wc -l | awk '{print "Error Num: "$1}'
            num_of_lines=$(< "$LOG2" wc -l)
            all_num=$((num_of_lines+all_num))
            echo $TEST4
            echo $TEST4
            ./s21_cat $TEST4 > s21_compare.txt
            cat $TEST4 > orig_compare.txt
            diff --suppress-common-lines -y s21_compare.txt orig_compare.txt  
            diff --suppress-common-lines -y s21_compare.txt orig_compare.txt  > $LOG2 
            diff --suppress-common-lines -y s21_compare.txt orig_compare.txt | wc -l | awk '{print "Error Num: "$1}'
            num_of_lines=$(< "$LOG2" wc -l)
            all_num=$((num_of_lines+all_num))
        done
    done
done
echo $all_num
