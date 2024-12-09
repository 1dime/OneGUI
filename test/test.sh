#The mutants directory
directory="./mutants"
num_fail=0
num_success=0
num_files=0
mkdir -p errors

analyze_mutants test.cpp "make clean; make;" --mutantDir mutants --compileCommand "-Iinclude -o ../bin/item.o ../bin/list.o ../bin/property.o ../bin/widget.o"
#Go through all files
for file in "$directory"/*; do
    echo "Compiling $file..."
    g++ $file -Iinclude -o ../bin/item.o ../bin/list.o ../bin/property.o ../bin/widget.o -g 2> errors/error_$num_files.log
    if [ $? -eq 0 ]
    then
        ((num_success++))
        echo "Success."
    else
        ((num_fail++))
        echo "Failed to compile. Check log at error.log"
    fi

    ((num_files++))
done

echo "Number of files: $(($num_success + $num_fail))"
echo "Number failed: $num_fail"
echo "Number succeeded: $num_success"