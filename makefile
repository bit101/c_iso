# set the sketch file you want to render here.
SKETCH_C := demo/sketch.c

# don't change any of this unless you know what you are doing.
CC := gcc
CFLAGS := `pkg-config --cflags gtk+-3.0`
CLIBS := `pkg-config --libs gtk+-3.0`
SKETCH_O := build/sketh.o
ISO_H := iso.h
ISO_C := iso.c
ISO_A := build/iso.a
MAIN_C := demo/main.c

# to squelch any internal command line output, set BL_QUIET=1
# any print calls in your sketch will continue to work.
default: main
	@BL_QUIET=0 BL_SAVE_FRAMES=0 bash -c "./main"

main: $(MAIN_C) $(SKETCH_O) $(ISO_A)
	@$(CC) $(WARN) $(CFLAGS) -Iinclude $(MAIN_C) $(SKETCH_O) $(ISO_A) libs/bitlib.a -o main -lm $(CLIBS)

$(SKETCH_O): $(SKETCH_C)
	@mkdir -p build
	@$(CC) $(WARN) $(CFLAGS) -I./ -Iinclude -c $(SKETCH_C) -o $(SKETCH_O) -lm $(CLIBS)

$(ISO_A): $(ISO_C)
	@mkdir -p build
	@$(CC) $(WARN) $(CFLAGS) -Iinclude -c $(ISO_C) -o $(ISO_A) -lm $(CLIBS)

dist: $(ISO_A)
	@echo assembling dist package...
	@mkdir -p dist
	@cp $(ISO_A) dist
	@cp $(ISO_H) dist


clean:
	@rm -f main
	@rm -f out.gif
	@rm -f out.mp4
	@rm -f out.png
	@rm -rf bitlib_c_frames
	@rm -f $(SKETCH_O)
	@rm -rf dist
	@rm -rf build
