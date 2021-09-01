# File-Sorter-Terminal-Tool
File sorter management tool. https://github.com/rounnus/File-Sorter-Core
# Download & Build
First download the program from github and go to the File-Sorter-Core folder.
```
% git clone https://github.com/rounnus/File-Sorter-Terminal-Tool
% cd File-Sorter-Terminal-Tool/
```
After installation the program must be built. In order to build the program, the following instructions must be followed.<br>
```
% mkdir build
% cd build/
% cmake ../
% make
% sudo make install
```
After this the program will be installed and ready to run.<br>

# Commands

Command |  Description
---------|--------------
`sorter --help` | Displays all available commands. 
`sorter --set-check-interval [value]`  | Changes the value of the check interval field to the value `[value]`. 
`sorter --set-parse-interval [value]`  | Changes the value of the parse interval field to the value `[value]`.
`sorter --set-default-dir-path [path]` | Changes the default location to `[path]`.
`sorter --set-debug-log [value]` | Changes the logs status based on the value `[value]`. It can get the values `1` `(debug mode)` and `0` `(normal mode)`.
`sorter --add-check [path]` | Adds `[path]` to the list of locations that the program looks at.
`sorter --add-target [ext] [path]` | Adds to the list the information that the program must send the file with extension `[ext]` to the location `[path]` if such a file is found. 
`sorter --remove-check [row number]` | Deletes the item in the line `[row_number]`, the line number appears with the command `--list-checks` or `--list-targets`. 
`sorter --list-checks` | Displays all locations that the program looks at.
`sorter --list-targets` | Displays all the elements that describe what the program does for a file. 
`sorter --list-options` | Displays the program options.

For more information on what each of the fields is, please read the core readme below: 
https://github.com/rounnus/File-Sorter-Core
