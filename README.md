# File-Monitoring-System

The File-Montoring-System scans a user-inputted root directory at a set time interval.  The program logs create, modify, and delete events that occur within the directory.  When an event occurs, the program will execute commands on the file if the file matches a specified pattern.  The commands and patterns come from a user-written rules file.  Each line of the rules file contains an event type (create, modify, delete), a pattern to match (ex. \*.jpg), and a command to execute.  This rules file is read in and parsed by the program.
