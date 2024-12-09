
#Compile all files
./build.sh

#Mutate the code
if [ ! -d "mutants" ]
then
	mkdir -p mutants
	mutate src/main.cpp --mutantDir mutants --cmd "afl-g++ src/main.cpp -o main_afl -ldeepstate -Isrc/include ./bin/list.o ./bin/widget.o ./bin/property.o"
fi

#Check if we should re-mutate
if [ "$1" == "--remutate " ]
then
	mutate src/main.cpp --mutantDir mutants --cmd "afl-g++ src/main.cpp -o main_afl -ldeepstate -Isrc/include ./bin/list.o ./bin/widget.o ./bin/property.o"
fi

#Analyze all mutants
analyze_mutants src/main.cpp "afl-g++ src/main.cpp -o main_afl -ldeepstate -Isrc/include ./bin/list.o ./bin/widget.o ./bin/property.o" --mutantDir mutants --timeout 120 --verbose
cp killed.txt oldkilled.txt
cp notkilled.txt oldnotkilled.txt

#Now analyze the files that havent been killed
analyze_mutants src/main.cpp "afl-g++ src/main.cpp -o main_afl -ldeepstate -Isrc/include ./bin/list.o ./bin/widget.o ./bin/property.o" --mutantDir mutants --timeout 120 --verbose --fromFile notkilled.txt
