./build.sh
if [ ! -f "main_afl" ]
then
	afl-clang++ main_ds_harness.cpp -o main_afl -Isrc/include ./bin/item.o ./bin/list.o ./bin/widget.o ./bin/property.o -ldeepstate -fprofile-arcs -ftest-coverage --coverage
fi

if [ ! -f "mutant_afl" ]
then
	afl-clang++ mutant_ds_harness.cpp -o mutant_afl -Isrc/include ./bin/item.o ./bin/list.o ./bin/widget.o ./bin/property.o -ldeepstate -fprofile-arcs -ftest-coverage --coverage
fi

deepstate-afl ./main_afl -o fuzz_afl --fuzzer_out --timeout 120
#deepstate-afl ./mutant_afl -o mutant_fuzz_afl --fuzzer_out --timeout 12
