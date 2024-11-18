CMakeAddText=        Day${d}/Day${d}.h\n        Day${d}/Part1.cpp\n        Day${d}/Part2.cpp\n        Day${d}/Part3.cpp\n\#\#\#\#
MainCppCase=        case ${d}\:\n            std\:\:cout << "Day ${d} - Part 1\: " << Day${d}\:\:Part1() << std\:\:endl;\n            std\:\:cout << "Day ${d} - Part 2\: " << Day${d}\:\:Part2() << std\:\:endl;\n            std\:\:cout << "Day ${d} - Part 3\: " << Day${d}\:\:Part3() << std\:\:endl;\n            break;\n        //\#\#\#\#case
create:
	mkdir -p Day${d}

	cp "./Templates/DayX.h" "./Day${d}/Day${d}.h"
	cp "./Templates/PartY.cpp" "./Day${d}/Part1.cpp"
	touch "./Day${d}/Part1.txt"
	cp "./Templates/PartY.cpp" "./Day${d}/Part2.cpp"
	touch "./Day${d}/Part2.txt"
	cp "./Templates/PartY.cpp" "./Day${d}/Part3.cpp"
	touch "./Day${d}/Part3.txt"


	sed -i "s/X/${d}/g" ./Day${d}/Day${d}.h
	sed -i "s/X/${d}/g" ./Day${d}/Part1.cpp
	sed -i "s/Y/1/g" ./Day${d}/Part1.cpp
	sed -i "s/X/${d}/g" ./Day${d}/Part2.cpp
	sed -i "s/Y/2/g" ./Day${d}/Part2.cpp
	sed -i "s/X/${d}/g" ./Day${d}/Part3.cpp
	sed -i "s/Y/3/g" ./Day${d}/Part3.cpp

	sed -i 's:####:${CMakeAddText}:g' ./CMakeLists.txt
	sed -i 's://\#\#\#\#include:#include "Day${d}/Day${d}.h"\n//\#\#\#\#include:g' ./main.cpp
	sed -i 's://\#\#\#\#case:${MainCppCase}:g' ./main.cpp
	sed -i -r 's:switch \([0-9]+\):switch (${d}):g' ./main.cpp

	git add .
	git commit -m "Day${d} init"
