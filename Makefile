########################################################
#  _ _ _ _ _ _ _
# |  - - - -    |
# | |      / /| |    Zack Traczyk (zbuck)
# | |   / /   | |
# | |/ / _ _ _| |    http://zacktraczyk.com
# |  _ _   _ _  |    https://github.com/xxzbuckxx
# | |_ _| |_ _| |
# |_ _ _ _ _ _ _|
#
#  make                     makes Arithmetic
#  make build               makes Arithmetic
#  make clean               removes all binaries
#
########################################################

all : build

convertLinks : convertLinks.cpp
	g++ -o convertLinks convertLinks.cpp

build: convertLinks
	./build.sh

clean :
	rm -r src imagenames.txt filenames.txt convertLinks

