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

SOURCE="$HOME/Library/Mobile Documents/iCloud~md~obsidian/Documents/Main"

# Make build folder if it doesn't exist
[ ! -d "build" ] && mkdir build

# Copy all Makrdown files to build
find "$SOURCE" -type f -name "*.md" > filenames.txt
cat filenames.txt | while read -r LINE
do
	FILE=${LINE##*/}
	NAME=${FILE%.*}
	# NOTE: -s is self contained (adds css and boiler plate)
	pandoc -s -f commonmark -t html -o "build/$NAME.html" "$LINE" --metadata title="$NAME"
done
