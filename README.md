# Jgraph

This program allows you to list names of professional golf players and look a their statistics combined.
To run, simply type 'make' and it should compile 5 different lists.
Each one has a different number of players along with an ordered or unordered list of names.
This program allows you to list the players names in whatever order you would like as long as they follow these 
rules:

1. create a .txt file with the following..
2. list players under a "SG: Off-The-Tee" title
3. after that list the players under "SG: Approach-The-Green" title
4. same with "SG: Around-The-Green"
5. Finally "SG: Putting"

If you would like to make your own run 
./main filename.txt
then 
./jj -P filename.jgr | ps2pdf - | convert -density 300 - -quality 100 filename.jpg

