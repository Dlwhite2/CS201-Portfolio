all:	main.c avltree.c crudFunctions.c utilityFunctions.c
	#wget https://datasets.imdbws.com/title.basics.tsv.gz
	#7z x title.basics.tsv.gz
	#grep "movie" data.tsv > original_records.txt
	#cut -s -f1,2,5,7 --complement original_records.txt >movie_records.txt
	gcc -Wall main.c avltree.c crudFunctions.c utilityFunctions.c -o movieLibrary
	#make clean

clean:
	rm title.basics.tsv.gz
	rm data.tsv
	rm original_records.txt
