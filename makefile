CMakeReplace = \n)\n\nadd_subdirectory(tests)
CMakeAddText=\n        Day${d}/Day${d}.h\n        Day${d}/Part1.cpp        Day${d}/Part2.cpp        Day${d}/Part3.cpp\n)\n\nadd_subdirectory(tests)

create:
	mkdir -p Day${d}

	cp "./Templates/DayX.h" "./Day${d}/Day${d}.h"
	cp "./Templates/PartY.cpp" "./Day${d}/Part1.cpp"
	cp "./Templates/PartY.cpp" "./Day${d}/Part2.cpp"
	cp "./Templates/PartY.cpp" "./Day${d}/Part3.cpp"

	sed -i "s/X/${d}/g" ./Day${d}/Day${d}.h
	sed -i "s/X/${d}/g" ./Day${d}/Part1.cpp
	sed -i "s/Y/1/g" ./Day${d}/Part1.cpp
	sed -i "s/X/${d}/g" ./Day${d}/Part2.cpp
	sed -i "s/Y/2/g" ./Day${d}/Part2.cpp
	sed -i "s/X/${d}/g" ./Day${d}/Part3.cpp
	sed -i "s/Y/3/g" ./Day${d}/Part3.cpp

	sed -i --debug "s:${CMakeReplace}:${CMakeAddText}:g" ./CMakeLists.txt