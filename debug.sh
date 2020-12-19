stty sane
g++ -Wall -Wextra -O0 *.cpp -I . -o main -lncurses -llua -L../lua -I../lua -ldl -g 
cgdb ./main
