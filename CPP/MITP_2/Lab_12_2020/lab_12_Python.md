# Additional exercises for Python labs

## Ex 1. Tic-tac-toe

Write the game code for two players on the 3x3 board:
1. Write a function that displays the board in the form:

-------------
|   |   |   |
-------------
|   |   |   |
-------------
|   |   |   |
-------------

2. Write function, which will get the players' movements and display them on the computer screen.
3. Write a function that will check after each move the result of the match (Player Win / Draw).

-------------
| X | X | X |
-------------
|   | O |   |
-------------
|   |   | O |
-------------    Player X Won!

4. [for volunteers] Implement the game algorithm to play against your computer. 



## Ex 2. Write a program to:
1. read file ex2.csv (from the repository),
1. remove lines from it in which 'val' is an empty string,
1. sort the lines in the file by 'id',
1. fix the 'id' numbering in such a way that there are no duplicates (in the case of finding a duplicate, one should add a number larger than the previous one),
1. convert all uppercase letters to lowercase,
1. delete all words in which the two-letter prefix consists of characters that are side by side on the ASCII board (eg. g-h), display the deleted words and their 'id'.

## Ex 3.  Write a program that will:
1. read the list of files from the 'task1' directory,
2. create new directories and copy files to them whose name begins with the same letter (eg the 'eHszo' file will be copied to the 'E' directory). During the implementation methods like glob.glob (), os.mkdir, os.rename (), shutil.copy will be helpful.
