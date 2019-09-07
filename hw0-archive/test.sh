#Compile the code
# if the file densemult exits then remove it
if [ -f denseadd ]; then
    rm denseadd
fi
g++ -std=c++11 *.cpp -o denseadd
# if the file densemult does not exit then exit the test
if [ ! -f denseadd ]; then
    echo -e "\033[1;91mCompile FAILED.\033[0m"
    exit
fi
# clean
rm *.out *.stderr *.stdcout
# For test case 1
# input 1.txt and output 1.out
./denseadd "A=test0A1.txt;B=test0A2.txt;C=test0A3.txt" 1>1.stdcout 2>1.stderr
# compare 1.out with 1.ans, output the difference to 1.diff
diff -iEBwu ans0A.txt test0A3.txt > 1.diff
# if diff returns nothing, it means you pass the test case (Your ourput file 1.out is correct)
if [ $? -ne 0 ]; then
    # display "test case 1 FAILED" to the screen. The word "FAILED" is highlighted in Red color
    echo -e "Test case 1    \033[1;91mFAILED.\033[0m"
else
    # display "test case 1 PASSED" to the screen. The word "PASSED" is highlighted in Green color
    echo -e "Test case 1    \033[1;92mPASSED.\033[0m"
    # remove the file 1.diff
    rm -f 1.diff
fi
# For test case 2
./denseadd "A=test0B1.txt;B=test0B2.txt;C=test0B3.txt" 1>2.stdcout 2>2.stderr
diff -iEBwu ans0B.txt test0B3.txt > 2.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 2    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 2    \033[1;92mPASSED.\033[0m"
    rm -f 2.diff
fi
# For test case 3
./denseadd "A=test0C1.txt;B=test0C2.txt;C=test0C3.txt" 1>3.stdcout 2>3.stderr
diff -iEBwu ans0C.txt test0C3.txt > 3.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 3    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 3    \033[1;92mPASSED.\033[0m"
    rm -f 3.diff
fi

