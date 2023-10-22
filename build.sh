#!/bin/bash
#
compile_way="make"
#
while getopts :f: opt
do
    case "$opt" in
        f) echo "The entry of compilation is $OPTARG."
            if [ $OPTARG = "cmake" ]
            then
                compile_way="cmake"
            fi ;;
        *) echo "Unknown option: $opt" ;;
    esac
done
#
if [ $compile_way = "cmake" ]
then
    rm -rf ./build/*
    touch ./build/build.sh
    echo "#!/bin/bash" >> ./build/build.sh

    echo "echo" >> ./build/build.sh
    echo "echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Begin MinGW Makefiles <<<<<<<<<<<<<<<<<<<<<<<<<<<<<'" >> ./build/build.sh
    echo "cmake -G \"MinGW Makefiles\" .." >> ./build/build.sh
    echo "echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>> End MinGW Makefiles <<<<<<<<<<<<<<<<<<<<<<<<<<<<<'" >> ./build/build.sh
    echo "echo" >> ./build/build.sh

    echo "echo" >> ./build/build.sh
    echo "echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Begin cmake .. <<<<<<<<<<<<<<<<<<<<<<<<<<<<<'" >> ./build/build.sh
    echo "cmake .." >> ./build/build.sh
    echo "echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>> End cmake .. <<<<<<<<<<<<<<<<<<<<<<<<<<<<<'" >> ./build/build.sh
    echo "echo" >> ./build/build.sh
else
    rm ./build/build.sh
    touch ./build/build.sh
    echo "#!/bin/bash" >> ./build/build.sh
fi
#
echo "echo" >> ./build/build.sh
echo "echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Begin make <<<<<<<<<<<<<<<<<<<<<<<<<<<<<'" >> ./build/build.sh
echo "make" >> ./build/build.sh
echo "echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>> End make <<<<<<<<<<<<<<<<<<<<<<<<<<<<<'" >> ./build/build.sh
echo "echo" >> ./build/build.sh
#
#echo "echo" >> ./build/build.sh
#echo "echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Begin make test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<'" >> ./build/build.sh
#echo "make test" >> ./build/build.sh
#echo "echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>> End make test <<<<<<<<<<<<<<<<<<<<<<<<<<<<<'" >> ./build/build.sh
#echo "echo" >> ./build/build.sh
#
#echo "echo" >> ./build/build.sh
#echo "echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Begin make install <<<<<<<<<<<<<<<<<<<<<<<<<<<<<'" >> ./build/build.sh
#echo "make install" >> ./build/build.sh
#echo "echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>> End make install <<<<<<<<<<<<<<<<<<<<<<<<<<<<<'" >> ./build/build.sh
#echo "echo" >> ./build/build.sh
#
#echo "echo" >> ./build/build.sh
#echo "echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Begin cpack bin <<<<<<<<<<<<<<<<<<<<<<<<<<<<<'" >> ./build/build.sh
#echo "cpack -C CPackConfig.cmake # 生成二进制安装包" >> ./build/build.sh
#echo "echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>> End cpack bin <<<<<<<<<<<<<<<<<<<<<<<<<<<<<'" >> ./build/build.sh
#echo "echo" >> ./build/build.sh
#
#echo "echo" >> ./build/build.sh
#echo "echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Begin cpack source <<<<<<<<<<<<<<<<<<<<<<<<<<<<<'" >> ./build/build.sh
#echo "cpack -C CPackSourceConfig.cmake # 生成源码安装包" >> ./build/build.sh
#echo "echo '>>>>>>>>>>>>>>>>>>>>>>>>>>>>> End cpack source <<<<<<<<<<<<<<<<<<<<<<<<<<<<<'" >> ./build/build.sh
#echo "echo" >> ./build/build.sh
#
cd build
./build.sh
#
