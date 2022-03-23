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
# Bash Script to convert Obsidian Wiki into static site
# 
########################################################

SOURCE="$HOME/Library/Mobile Documents/iCloud~md~obsidian/Documents/Main"

# Make build folder if it doesn't exist
[ ! -d "build" ] && mkdir build
[ ! -d "src" ] && mkdir src

# Copy all Makrdown files to build
find "$SOURCE" -type f -name "*.md" > filenames.txt
find "$SOURCE" -type f -name "*.png" > imagenames.txt
find "$SOURCE" -type f -name "*.jpg" >> imagenames.txt
find "$SOURCE" -type f -name "*.gif" >> imagenames.txt

cat imagenames.txt | while read -r LINE
do
	FILE=${LINE##*/}
	HYPHENFILE=$(echo $FILE | tr " " "-")
	cp "$LINE" "build/$HYPHENFILE"
done

cat filenames.txt | while read -r LINE
do
	FILE=${LINE##*/}
	NAME=${FILE%.*}
	HYPHENNAME=$(echo $NAME | tr " " "-")
	./convertLinks "$LINE" "src/$HYPHENNAME.md"
	pandoc -s -f commonmark -t html -o "build/$HYPHENNAME.html" "src/$HYPHENNAME.md" --quiet
done

