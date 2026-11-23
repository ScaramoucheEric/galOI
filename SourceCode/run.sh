cp sample/two/two1.in two.in; cp sample/two/two1.ans two.ans
g++ two.cpp -o two.bin -std=c++14 -Wall -O2; ./two.bin;
diff two.ans two.out