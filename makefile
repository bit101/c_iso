# set the sketch file you want to render here.
SKETCH_C := sketch.c

# don't change any of this unless you know what you are doing.
CC := gcc
CFLAGS := `pkg-config --cflags gtk+-3.0`
CLIBS := `pkg-config --libs gtk+-3.0`
SKETCH_O := $(SKETCH_C:.c=.o)

# to squelch any internal command line output, set BL_QUIET=1
# any print calls in your sketch will continue to work.
default: main
	@BL_QUIET=0 BL_SAVE_FRAMES=0 bash -c "./main"

main: main.c $(SKETCH_O) iso.o
	@$(CC) $(WARN) $(CFLAGS) -Iinclude main.c $(SKETCH_O) iso.o libs/bitlib.a -o main -lm $(CLIBS)

$(SKETCH_O): $(SKETCH_C)
	@$(CC) $(WARN) $(CFLAGS) -Iinclude -c $(SKETCH_C) -lm $(CLIBS)

iso.o: iso.c
	@$(CC) $(WARN) $(CFLAGS) -Iinclude -c iso.c -lm $(CLIBS)

clean:
	@rm -f main
	@rm -f out.gif
	@rm -f out.mp4
	@rm -f out.png
	@rm -rf bitlib_c_frames
