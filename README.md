# Find-and-Replace-Boyer-Moore-Horspool-in-C
A Program that finds a word inside a passage using Boyer-Moore Horspool algorithm and changes it as requested by the user. User has the option to select Case Sensitivity while for searching the word. It works just as Find and Replace logic of editores.<br/>

The program is consisted of three main features:<br/>
# Reading of the data:
The user has the ability to select the word or phrase that will be searched, the word or phrase that will replace it, the name of the file to read the passage from and the case sensitivity of the search

# Boyer-Moore Horspool Algorithm
The passage is read from the file in memory using an array. All the point that the phrase occurs will be found and replaced with the new phrase. The replacement is performed inplace without using extra array. Finally the new passage is written back to the file.

# Report
After the program performs the replacement a report detailing the number of replacements done and their positions is printed on screen.
![Capture6 (2)](https://user-images.githubusercontent.com/49107892/152588387-fc4c70b8-240d-4495-bf48-bd90edf6e557.PNG)
