#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include<time.h>

//Macro for using switch case with strings
#ifndef SWITCH_CASE_INIT
    #define SWITCH_CASE_INIT
	    #define SWITCH(X)	for (char* __switch_p__ = X, __switch_next__=1 ; __switch_p__ ; __switch_p__=0, __switch_next__=1) { {
        #define CASE(X)			} if (!__switch_next__ || !(__switch_next__ = strcmp(__switch_p__, X))) {
	    #define DEFAULT		  	} {
	    #define END			}}
    #endif

int offset(int c,char** arg,int n)
{
	int val;
	if(c>n)
	{
		if(strcmp(arg[n],"0")==0)
			return 0;
		else
		{
			val=strtol(arg[n],NULL,10);
		}
		if (val==0)
		{
			printf("Incorrect offset\n");
			exit(-1);
		}
		else
			return val;
	}
	else
	{
		printf("Insufficient arguments\n");
		exit(-1);
	}
}
int whence(int c,char** arg,int n)
{
	int val;
	if(c>n)
	{
		switch(arg[n][0])
		{
			case 's':
			{
				return SEEK_SET;
				break;
			}
			case 'e':
			{
				return SEEK_END;
			}
		}
	}
	else
	{
		printf("Insufficient arguments\n");
		exit(-1);
	}
}
int bytes(int c,char** arg,int n)
{
	int val;
	if(c>n)
	{
		if(strcmp(arg[n],"0")==0)
			return 0;
		else
			val=strtol(arg[n],NULL,10);
		if (val==0)
		{
			printf("Incorrect bytes\n");
			exit(-1);
		}
		else
			return val;
	}
	else
	{
		printf("Insufficient arguments\n");
		exit(-1);
	}
}

int main(int argc,char* argv[])
{
	switch (argv[1][0])
	{
		case '-':
			switch (argv[1][1])
			{
				case 'h':
					printf("c create a file\nr read a file\nw write to a file\ni file info\n");
					printf("Add hyphen '-' before args for more details");
					break;
				case 'c':
					printf("<cmode>{cr,cp} <filename> <permission> [overwrite]\nEnter file name/path to create a file\n");
					printf("cr Create regular file\n");
					printf("cp Create pipe\n");
					printf("<filename> Valid file name/path\n");
					printf("[permission] (optional) file access permissions\n");
					printf("[overwrite]{t,true} (optional) Overwrite existing file \n");
					printf("To Create a file\n", );

					break;
				case 'r':
					printf("<rmode>{r,ro,rn,rw,ron,row,rown} <filename> [...]\n");
					printf("r: ...\n");
					printf("ro:... <offset>\n");
					printf("rw:... <whence>\n");
					printf("rn:... <bytes>\n");
					printf("row:... <offset> <whence>\n");
					printf("ron:... <offset> <bytes>\n");
					printf("rown:... <offset> <whence> <bytes>\n");
					printf("<filename> Valid file name/path\n");
					printf("<offset>{int} Offset by which the cursor is placed\n");
					printf("<whence>{s,e} Location to seek from\n");
					printf("<bytes>{int} bytes to read\n");
					printf("To read from a file/pipe")
				break;
				case 'w':
					printf("<wmode>{w,wo,ww,wow} <filename> [...]\n");
					printf("w: ...\n");
					printf("wo: ... <offset>\n");
					printf("ww: ... <whence>\n");
					printf("wow: ... <offset> <whence>\n");
					printf("<filename> Valid file name/path\n");
					printf("<offset>{int} Offset by which the cursor is placed\n");
					printf("<whence>{s,e} Location to seek from\n");
					printf("To write data into a file/pipe\n")
					break;
				case 'i':
					printf("i <filename>\n");
					printf("<filename> Valid file name/path\n");
					printf("To get file details\n");

				default:
				printf("Invalid argument");
			}
			break;
		case 'c':
			{
				if (argc<3)
				{
					printf("Insufficient arguments\n");
					break;
				}
				int permission=0666;
				if (argc>3)
				{
					permission=strtol(argv[3],NULL,8);
					if (permission==0)
					{
						printf("Insufficient permission\n");
						break;
					}
				}
				int overwrite=0;
				if (argc==5 && (strcmp(argv[4],"t") || strcmp(argv[4],"true")))
							overwrite=1;
						if (overwrite==1)
							if(unlink(argv[2]) == -1)
								if(errno!=ENOENT)
								{
									printf("Unable to overwrite\n");
									perror("abc");
									break;
								}
				switch (argv[1][1])
				{
					case 'r':
					{
						struct stat buf;
						int file=stat(argv[2],&buf);
						//printf("\x1B[A\b");
						if(file<0)
						{
							file=creat(argv[2],permission);
							if (file<=0)
								printf("Cannot create new file\n");
							else
							{
								printf("File created successfully\n");
								close(file);
							}
						}
						else
							printf("File already exists\n");
						break;
						}
					case 'p':
					{
						int status= mknod(argv[2], S_IFIFO | permission, 0);
						
						if (status==-1)
							printf("Cannot create pipe\n");
						else
							printf("Pipe created successfully\n");
						break;
					}
				}
				break;
			}
		case 'r':
		{	

			int _offset=0;
			int _whence=SEEK_SET;
			int _bytes=-1;

			SWITCH (argv[1])
				CASE ("r")
					break;
				CASE ("row")
					_offset=offset(argc,argv,3);
					_whence=whence(argc,argv,4);
					break;
				CASE ("ro")
					_offset=offset(argc,argv,3);
					break;
				CASE ("rw")
					_whence=whence(argc,argv,3);
					break;
				CASE ("rn")
					_bytes=bytes(argc,argv,3);
					break;
				CASE ("ron")
					_offset=offset(argc,argv,3);
					_bytes=bytes(argc,argv,4);
					break;
				CASE ("rown")
					_offset=offset(argc,argv,3);
					_whence=whence(argc,argv,4);
					_bytes=bytes(argc,argv,5);
					break;
				DEFAULT

					printf("Invalid argument\n");
			END

			int file=open(argv[2],O_RDONLY);
			if (file==-1)
			{
				printf("Cannot read file\n");
				break;
			}
			if (_whence != SEEK_SET || _offset != 0)
			{
				int new_offset = lseek(file, _offset, _whence);
		        if(new_offset == -1)
		            printf("Seek failed\n");
		    }
	        char* data;
	        ssize_t nbytes_read;
	        if(_bytes != -1)
	        {
		        data=malloc(_bytes);
		        nbytes_read = read(file, data, _bytes);
		        if(nbytes_read == 0)
		        {
		            printf("Reached EOF\n");
		        }
		        else if(nbytes_read == -1)
		        {
		            printf("Failed read\n");
		        }
		        else
		        {
		        	printf("%s",data);
		        	exit(100);
		        }
				break;
			}
			else
			{
				char buffer[1024];
		        while((nbytes_read =read(file, buffer, sizeof(buffer))) )
		        {
		            if(nbytes_read == -1)
		            {
		                printf("Cannot read contents of the file");
		            }
		            else if (nbytes_read<sizeof(buffer))
		            {
		            	buffer[nbytes_read]='\0';
		            }
		            printf("%s",buffer);
		        }
		        close(file);
		        break;
		    }
	        case 'w':
	        {
		        int _offset=0;
				int _whence=SEEK_SET;

				SWITCH (argv[1])
					CASE("w")
						break;
					CASE ("ww")
						_whence=whence(argc,argv,3);
						break;
					CASE ("wo")
						_offset=offset(argc,argv,3);
						break;
					CASE ("wow")
						_offset=offset(argc,argv,3);
						_whence=whence(argc,argv,4);
						break;
					DEFAULT
						printf("Invalid argument\n");
				END

				int file=open(argv[2],O_WRONLY);
				if (file==-1)
				{
					printf("Cannot write into file\n");
					break;
				}
				if (_whence != SEEK_SET || _offset != 0)
			    {
			        int new_offset = lseek(file, _offset, _whence);
			        if(new_offset ==-1)
			        {
			            perror("Error caught");
			            exit(-1);
			        }
			    }
				char buffer[1024];
				int stdin=0;
		        while((nbytes_read =read(stdin, buffer, sizeof(buffer))) )
		        {
		            if(nbytes_read == -1)
		            {
		                printf("Cannot write from console");
		            }
		            else if (nbytes_read<sizeof(buffer))
		            {
		            	buffer[nbytes_read]='\0';
		            }
				    int nbytes_written = write(file,buffer,nbytes_read);
				    if(nbytes_written == -1)
			    	printf("Failed write\n");
			    }
			    close(file);
			    break;
			}
			case 'i':
			{
				struct stat sb;
				int status = lstat(argv[2],&sb);
				if (status==0)
				{
					printf("File type:                ");

				   switch (sb.st_mode & S_IFMT) {
				    case S_IFBLK:  printf("block device\n");            break;
				    case S_IFCHR:  printf("character device\n");        break;
				    case S_IFDIR:  printf("directory\n");               break;
				    case S_IFIFO:  printf("FIFO/pipe\n");               break;
				    case S_IFLNK:  printf("symlink\n");                 break;
				    case S_IFREG:  printf("regular file\n");            break;
				    case S_IFSOCK: printf("socket\n");                  break;
				    default:       printf("unknown?\n");                break;
				    }

				   printf("I-node number:            %ld\n", (long) sb.st_ino);

				   printf("Mode:                     %lo (octal)\n",
				            (unsigned long) sb.st_mode);

				   printf("Link count:               %ld\n", (long) sb.st_nlink);
				    printf("Ownership:                UID=%ld   GID=%ld\n",
				            (long) sb.st_uid, (long) sb.st_gid);

				   printf("Preferred I/O block size: %ld bytes\n",
				            (long) sb.st_blksize);
				    printf("File size:                %lld bytes\n",
				            (long long) sb.st_size);
				    printf("Blocks allocated:         %lld\n",
				            (long long) sb.st_blocks);

				   printf("Last status change:       %s", ctime(&sb.st_ctime));
				    printf("Last file access:         %s", ctime(&sb.st_atime));
				    printf("Last file modification:   %s", ctime(&sb.st_mtime));

				   exit(EXIT_SUCCESS);
				}
				else
				{
					printf("File does not exist\n");
				}		
			}
		}
	}
}