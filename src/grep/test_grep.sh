
COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
echo "" > log.txt
echo "wait for testing to be done"

for var in -i -v -c -l -n
do
    for TEST_FILE in 1.txt 2.txt bents.txt test.txt
    do
        for PATTERN in biba boba a EMPEROR -
        do
            TEST1="$var $PATTERN ./test-files/$TEST_FILE"
            ./s21_grep $TEST1 > s21_grep.txt
            grep $TEST1 > grep.txt
            DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
            if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
                then
                    (( COUNTER_SUCCESS++ ))
                else
                    echo "$TEST1" >> log.txt
                    echo "$DIFF_RES" >> log.txt
                    (( COUNTER_FAIL++ ))
            fi
            rm s21_grep.txt grep.txt
        done
    done
done


for TEST_FILE2 in 1.txt 2.txt bents.txt test.txt
do
    for TEST_FILE3 in test.txt bents.txt 2.txt 1.txt
    do
        TEST2="-e biba -e boba -e EMPEROR -e -s ./test-files/$TEST_FILE2 ./test-files/$TEST_FILE3"
        ./s21_grep $TEST2 > s21_grep.txt
        grep $TEST2 > grep.txt
        DIFF_RES1="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES1" == "Files s21_grep.txt and grep.txt are identical" ]
            then
                (( COUNTER_SUCCESS++ ))
            else
                echo "$TEST2" >> log.txt
                echo "$DIFF_RES1" >> log.txt
                (( COUNTER_FAIL++ ))
        fi
        rm s21_grep.txt grep.txt
    done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
if [ "$COUNTER_FAIL" == 0 ]
    then
        rm log.txt
fi