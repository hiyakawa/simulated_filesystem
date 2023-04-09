# Simulated Filesystem

write a few “commands” or programs that use the interface provided by the file system to create, remove, read, and write files.

able to interact with the filesystem by running these commands through a command_ prompt.

create an abstract base class that declares the interface shared by all file types and then implement this interface to create a class representing a text file.

implement a second concrete file type, an image file. create an abstract base class declaring the interface of a filesystem and implement this interface in a class representing a simple filesystem implementation.

create a new family of classes responsible for creating new files based on the file’s extension (“.txt” for example). implement the abstract factory pattern to accomplish this while allowing your code to be easily extended to support new file types in the future.

use the visitor pattern to display the contents of files in unique ways. The “visitors” can be used to display different information about files or the files contents in different formats. A new “visitor” can be implemented for each new format a file should be displayed in.

use the proxy pattern to add functionality for password protected files.

implement the command_ pattern to create a command_ prompt that listens for user input and executes a “command_” based on the command_ issued by the user. implement the “touch” command_, which creates a new file and adds it to the file system.

implement several more “commands” using a couple of different design patterns. able to interact with the filesystem implementation by interactively executing commands to do things like create files and password protected files, write to files, read from files, copy files, delete files, etc.