CC                  := cc
CURDIR              := $(shell pwd)
LIB                 := libAVC
PREFIX              ?= /usr/local/Packages/$(LIB)
VERSION              = `grep @version $(CURDIR)/libBitIO/include/BitIO.h | echo | grep -o '[0-9]\.[0-9]\.[0-9]'`
CFLAGS              := -std=c11 -march=native -funroll-loops -ferror-limit=1024 -pedantic
LDFLAGS             := -flto=thin

BUILD_DIR           := $(CURDIR)/BUILD
LIB_DIR             := $(CURDIR)/libAVC/src
LIB_INC             := $(CURDIR)/libAVC/include
BUILD_LIB           := $(BUILD_DIR)/libAVC

DEB_FLAGS           := $(CFLAGS) -g -o0 $(DEB_ERROR_OPTIONS) $(LDFLAGS)
REL_FLAGS           := $(CFLAGS) -ofast $(REL_ERROR_OPTIONS) $(LDFLAGS)

.PHONY: all detect_platform Release Debug Install Uninstall Clean distclean

all:
	$(release)
	$(install)
check: 
	$(test)
distclean: 
	$(clean)

CHECK_VERS:
	$(shell echo ${VERSION})



$(BUILD_LIB)/libAVC.a():

release:
	mkdir -p   $(BUILD_DIR)/libAVC
	$(CC)      $(REL_FLAGS) -c $(CURDIR)/libAVC/src/Decoder/DecodeSEI.c -o $(BUILD_DIR)/libAVC/DecodeSEI.o
	$(CC)      $(REL_FLAGS) -c $(CURDIR)/libAVC/src/Decoder/DecodeSlice.c -o $(BUILD_DIR)/libAVC/DecodeSlice.o
	$(CC)      $(REL_FLAGS) -c $(CURDIR)/libAVC/src/Decoder/DecodeMacroBlock.c -o $(BUILD_DIR)/libAVC/DecodeMacroBlock.o
	$(CC)      $(REL_FLAGS) -c $(CURDIR)/libAVC/src/Decoder/ParseNAL.c -o $(BUILD_DIR)/libAVC/ParseNAL.o
	$(CC)      $(REL_FLAGS) -c $(CURDIR)/libAVC/src/libAVC.c -o $(BUILD_DIR)/libAVC/libAVC.o
	$(CC)      $(REL_FLAGS) -c $(CURDIR)/libAVC/src/Decoder/DecodeAVC.c -o $(BUILD_DIR)/libAVC/DecodeAVC.o
	ar -crsu   $(BUILD_DIR)/libAVC/libAVC.a $(BUILD_DIR)/libAVC/*.o
	ranlib -sf $(BUILD_DIR)/libAVC/libAVC.a

debug:
	mkdir -p   $(BUILD_DIR)/libAVC
	$(CC)      $(DEB_FLAGS) -c $(CURDIR)/libAVC/src/Decoder/DecodeSEI.c -o $(BUILD_DIR)/libAVC/DecodeSEI.o
	$(CC)      $(DEB_FLAGS) -c $(CURDIR)/libAVC/src/Decoder/DecodeSlice.c -o $(BUILD_DIR)/libAVC/DecodeSlice.o
	$(CC)      $(DEB_FLAGS) -c $(CURDIR)/libAVC/src/Decoder/DecodeMacroBlock.c -o $(BUILD_DIR)/libAVC/DecodeMacroBlock.o
	$(CC)      $(DEB_FLAGS) -c $(CURDIR)/libAVC/src/Decoder/ParseNAL.c -o $(BUILD_DIR)/libAVC/ParseNAL.o
	$(CC)      $(DEB_FLAGS) -c $(CURDIR)/libAVC/src/libAVC.c -o $(BUILD_DIR)/libAVC/libAVC.o
	$(CC)      $(DEB_FLAGS) -c $(CURDIR)/libAVC/src/Decoder/DecodeAVC.c -o $(BUILD_DIR)/libAVC/DecodeAVC.o
	ar -crsu   $(BUILD_DIR)/libAVC/libAVC.a $(BUILD_DIR)/libAVC/*.o
	ranlib -sf $(BUILD_DIR)/libAVC/libAVC.a

install:
	install -d -m 777 $(PREFIX)/lib
	install -d -m 777 $(PREFIX)/include
	install -C -v -m 444 $(BUILD_DIR)/libAVC/libAVC.a $(PREFIX)/lib/libAVC.a
	install -C -v -m 444 $(CURDIR)/libAVC/include/libAVC.h $(PREFIX)/include/libAVC.h

uninstall:
	rm -d -i $(PREFIX)

clean:
	cd $(BUILD_DIR)/libAVC/
	rm -f -v -r *.o
	rm -f -v -r libAVC.a
	rm -f -v -r .DS_Store
	rm -f -v -r Thumbs.db
	rm -f -v -r desktop.ini
	rmdir $(BUILD_DIR)
