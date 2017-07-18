#FINAL TP - MAKEFILE
#This makefile was made in order to simplify the compilation of the snake.
#(Check if there is an update directly from the object files).
#The project itself is divided in two diferent versions, the pc and the rpi one.
#To compile we need to access to the terminal first and execute the following commands
#
#if the pc version is wanted execute:
#make snake_version_pc 
#then execute
#./snake
#
#if the rpi version is wanted execute:
#make snake_version_rpi
#then execute
#./snake_rpi_exec
#
#if there is a need to remove all the object files execute:
#make clean
#note: the important object files are stored in a separated directory

snake_version_pc: main.o
	gcc main.o snake_graphic_base.o snake_logic.o snake_pc.o ui.o utils.o sound.o -o snake `pkg-config --libs allegro-5.0` `pkg-config --libs allegro_font-5.0` `pkg-config --libs allegro_image-5.0` `pkg-config --libs allegro_primitives-5.0` `pkg-config --libs allegro_ttf-5.0` `pkg-config --libs allegro_audio-5.0` `pkg-config --libs allegro_acodec-5.0`


main.o: main.c snake_logic.o snake_pc.o snake_graphic_base.o sound.o config.h
	gcc -c main.c

snake_graphic_base.o: snake_graphic_base.c snake_graphic_base.h  ui.o config.h
	gcc -c snake_graphic_base.c

sound.o: sound.c sound.h
	gcc -c sound.c

snake_pc.o: snake_pc.c snake_pc.h snake_graphic_base.o utils.o config.h
	gcc -c snake_pc.c


ui.o:	ui.c ui.h utils.o config.h
	gcc -c ui.c


snake_version_rpi: main_rpi.o 
	gcc main_rpi.o rpi_hard.o snake_rpi.o snake_logic.o rpi_lib/joydrv.o rpi_lib/termlib.o rpi_lib/disdrv.o -o snake_rpi_exec

main_rpi.o: main.c rpi_hard.o snake_rpi.o snake_logic.o
	gcc -c main_rpi.c

rpi_hard.o: rpi_hard.c rpi_hard.h snake_logic.o
	gcc -c rpi_hard.c

snake_rpi.o: snake_rpi.c snake_rpi.h rpi_hard.o
	gcc -c snake_rpi.c

snake_logic.o: snake_logic.c snake_logic.h utils.o config.h
	gcc -c snake_logic.c
utils.o: utils.c utils.h
	gcc -c utils.c
	
clean:
	rm *.o


