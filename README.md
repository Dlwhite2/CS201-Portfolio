-----------------------------------------------------------------------------------
Personal IMDB Movie Library README
Author: Daniel White
Class: CS201 - Data Structures and Algorithms
Date: 03/31/2019
GitHub: https://github.com/Dlwhite2/CS201-Portfolio.git
Youtube: https://www.youtube.com/watch?v=F0RrsTLF8No&t=9s
-----------------------------------------------------------------------------------



-----------------------------------------------------------------------------------
Summary:
-----------------------------------------------------------------------------------
The purpose of this program is to retrieve the movies from IMDB's movie database
so that a user can add a movie and it's information into a personal library for the
user's own recordkeeping of movies that they own. This program supports creating,
retrieving, updating, and deleting (CRUD)) entries into their personal library. The
program will save personal libraries for each user that signs in at the beginning
of the program so that libraries can be loaded and edited across program runtimes.
-----------------------------------------------------------------------------------



-----------------------------------------------------------------------------------
Installation Instructions:
-----------------------------------------------------------------------------------
To install the Personal IMDB Movie Library, go to the public github repo located
https://github.com/Dlwhite2/CS201-Portfolio.git and download the repo. This repo
contains all of the files needed to run the program. However, installation of this
program may require installation of a some extra command prompt libraries:

   Prerequisites:
     1) make-> Can be installed using the command "sudo apt-get install make"
     2) wget-> Should already be installed on both Ubuntu and Windows (Cygwin)
     3) 7z->   Can be installed using the command "sudo apt-get install p7zip-full"
     4) grep-> Should already be installed on both Ubuntu and Windows (Cygwin)

After ensuring that all of the prerequisites are installed, run the command "make".
Running "make" will download the database from IMDB and extract it. Then, it will
modify the movie database file to retain only the data that will be used by the
program. Lastly, it will compile the program into the executable "movieLibrary.exe"
and then clean up the downloaded/extracted files in the directory.

Once "make" has been successfully run, the Personal IMDB Movie Library has been
installed and can be run using the command, "./movieLibrary.exe".
-----------------------------------------------------------------------------------



-----------------------------------------------------------------------------------
User Instructions:
-----------------------------------------------------------------------------------
To use this program, begin by running the program using the command,
"./movieLibrary.exe". The program begins by loading the IMDB database into the
computer's memory. Once the database has been loaded, the program asks the user to
input a username that will be used for saving the user's library into
[username].txt. From here, the user will see a list of options to choose:

      'c' - This options allows you to search through the IMDB database and select
      	    a movie to CREATE an entry in the personal library. 
	    
      'r' - This option allows you to search through the personal library and select
      	    a movie to RETRIEVE the information about it. This will print out all of
	    the information associated with the movie.

      'u' - This option allows you to search through the personal library and select
      	    a movie whose information you wish to update.

      'd' - This option allows you to search through the personal library and select
      	    a movie you wish to delete from the personal library.

      'p' - This option prints out all of the movies in the personal library.

      'e' - This option saves the user's personal library into [username].txt and
      	    exits the program.

When searching, if you decide you do not want to search, you may enter '!' to
abort the search. If you perform the search, a numbered list (30 max) of matches
(both full and partial) will be displayed. Then you can select a movie from the list
by entering the number that is displayed next to the movie you'd like. This is how
the search works across all of the searching functions. If there are more than 30
search results, you may enter a '0' to quit the command and try to search again.
-----------------------------------------------------------------------------------