# AOS
UNIX OS based Implementations

## fop 
file operations program can execute file operations like

* Create
* Read
* Write 
* Information 

# Usage
fop uses command line arguments to execute system calls to implement file operations

# Execution
* > ./fop cr \<filename\> [permissions] [overwrite]
* > ./fop cp \<filename\> [permissions] [overwrite]
* > ./fop r \<filename\>
* > ./fop ro \<filename\> \<offset\>
* > ./fop rw \<filename\> \<whence\>
* > ./fop row \<filename\> \<offset\> \<whence\>
* > ./fop ron \<filename\> \<offset\> \<bytes\>
* > ./fop rown \<filename\> \<offset\> \<whence\> \<bytes\>
* > ./fop w \<filename\>
* > ./fop wo \<filename\> \<offset\>
* > ./fop ww \<filename\> \<whence\>
* > ./fop wow \<filename\> \<offset\> \<whence\>
* > ./fop i \<filename\>

# System calls
|          Task         |            System Call(s) Used            |
|:---------------------:|:-----------------------------------------:|
| Create New Files      | creat, mknod                              |
| Access Existing Files | open, read, write, lseek, close           |
| Advanced System Calls | pipe, unlink                              |

# Prerequisite
* The GNU Compiler Collection for compilation of \'.c\' file or any equivalent C compiler

# About
Created by Arnav Kumar Jain
Roll No. 57
M.Sc Computer Science
Department of Computer Science, University of Delhi

# Bibliography
* The Design of the UNIX Operating System, Maurice J. Bach
* Linux Manual Pages for System Calls and Functions

# Reference
Github
