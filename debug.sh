g++ -Wall -Wextra -O0 *.cpp -I . -o main -llua -L../lua -g
cgdb ./main
