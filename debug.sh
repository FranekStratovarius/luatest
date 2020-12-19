g++ -Wall -Wextra ./src/*.cpp -I ./include/ -o main -llua -O0 -g
cgdb ./main
