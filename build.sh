reset

#!/bin/bash
installNecessaryPackages() {
    #Install any missing dependencies, such as xorg or libx11-dev
    packages=("gcc", "g++", "libx11-dev", "xorg",)
    packages_str=""
    for package in "${packages[@]}"
    do
        package=${package::-1}
        dpkg --status $package &> /dev/null
        if [ ! $? -eq 0 ]
        then
            package+=' '
            packages_str+=$package
        fi
    done
    
    #Install any packages not installed
    if [ "$packages_str" != "" ]
    then
        echo "Installing missing dependencies $packages_str"
        sudo apt-get install $packages_str -y
    fi
}

#Make the first argument all lowercase
platform="${1,,}"
#Show the help menu if needed
if [ "$platform" == "--help" ]
then
    echo "build.sh usage: ./build.sh [PLATFORM] or ./build.sh [PLATFORM] [CONFIGURATION PATH]"
    echo "Supported Platforms:"
    echo "  Windows"
    echo "  Linux"
    echo "  All (Windows and Linux)"
elif [ "$platform" == "" ]
then
    echo "Incorrect usage. Correct usage:"
    ./build.sh --help
else
    #Attempt to compile for the given platform
    echo "Attempting to compile for $1..."
    if [ "$platform" == "windows" ]
    then
        #Try to compile onegui for Windows, either x86 or x64 depending on present libraries
        cmd_64=`command -v "x86_64-w64-mingw32-gcc"`
        cmd_i686=`command -v "i686-w64-mingw32-gcc"`
        if [ "$cmd_64" != "" ]
        then
            gpp="x86_64-w64-mingw32-gcc"
        elif [ "$cmd_i686" != "" ]
        then
            gpp="i686-w64-mingw32-gcc"
        fi
        if [ "$gpp" != "" ]
        then
            mkdir -p "bin/windows"
#            cp onegui_config.json bin/windows/onegui_config.json
            $gpp src/main.c -o bin/windows/onegui.exe -Isrc/include -g -static-libstdc++ -static 
            echo "Done."
        else
            echo "You must have MinGW installed to compile for Windows"
        fi
    elif [ "$platform" == "linux" ]
    then
	    #Install required packages
        installNecessaryPackages
        #Build onegui for Linux, targetting Ubuntu or any debian linux-based OS
        mkdir -p "bin/linux"
        gcc src/main.c -Isrc/include -o bin/linux/onegui.o  -g -lX11
 #       cp onegui_config.json bin/linux/onegui_config.json
        bin/linux/onegui.o "$2"
        echo "Done"
    elif [ "$platform" == "all" ]
    then
        ./build.sh windows
        ./build.sh linux
    else
        echo "${platform} is not a supported platform."
    fi
fi
