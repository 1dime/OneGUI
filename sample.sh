reset
rm -rf bin
rm -rf **.o **.exe
mkdir -p bin
g++ -c src/list/item.cpp -o bin/item.o -Isrc/include -g
g++ -c src/list/list.cpp -o bin/list.o -Isrc/include -g
g++ -c src/properties/property.cpp -o bin/property.o -Isrc/include -g
g++ -c src/widgets/widget.cpp -o bin/widget.o -Isrc/include -g
g++ src/main.cpp -o main.exe -Isrc/include ./bin/item.o ./bin/list.o ./bin/property.o ./bin/widget.o -g
./main.exe
