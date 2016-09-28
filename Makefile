imageIndexing: main.o ImageProcessingTools.o
	g++ -g main.o ImageProcessingTools.o -o imageIndexing -ljpeg


main.o: ./src/main.C
	g++ ./src/main.C -c

ImageProcessingTools.o: ./libs/ImageProcessingTools.C
	g++ ./libs/ImageProcessingTools.C -c

clean:
	rm -rf *.o
mrproper: clean
	rm -rf imageIndexing
