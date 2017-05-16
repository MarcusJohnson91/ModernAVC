CC                  := cc
CURDIR              := $(shell pwd)
LIB                 := ModernAVC
PREFIX              ?= /usr/local/Packages/$(LIB)
VERSION              = `grep @version $(CURDIR)/libBitIO/include/BitIO.h | echo | grep -o '[0-9]\.[0-9]\.[0-9]'`
CFLAGS              := -std=c11 -march=native -funroll-loops -ferror-limit=1024 -pedantic
LDFLAGS             := -flto=thin

BUILD_DIR           := $(CURDIR)/BUILD
LIB_DIR             := $(CURDIR)/libModernAVC/src
LIB_INC             := $(CURDIR)/libModernAVC/include
BUILD_LIB           := $(BUILD_DIR)/libModernAVC

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



$(BUILD_LIB)/libModernAVC.a():

release:
	mkdir -p   $(BUILD_DIR)/libModernAVC
	$(CC)      $(REL_FLAGS) -c $(CURDIR)/libModernAVC/src/Decoder/DecodeSEI.c -o $(BUILD_DIR)/libModernAVC/DecodeSEI.o
	$(CC)      $(REL_FLAGS) -c $(CURDIR)/libModernAVC/src/Decoder/DecodeSlice.c -o $(BUILD_DIR)/libModernAVC/DecodeSlice.o
	$(CC)      $(REL_FLAGS) -c $(CURDIR)/libModernAVC/src/Decoder/DecodeMacroBlock.c -o $(BUILD_DIR)/libModernAVC/DecodeMacroBlock.o
	$(CC)      $(REL_FLAGS) -c $(CURDIR)/libModernAVC/src/Decoder/ParseNAL.c -o $(BUILD_DIR)/libModernAVC/ParseNAL.o
	$(CC)      $(REL_FLAGS) -c $(CURDIR)/libModernAVC/src/libModernAVC.c -o $(BUILD_DIR)/libModernAVC/libModernAVC.o
	$(CC)      $(REL_FLAGS) -c $(CURDIR)/libModernAVC/src/Decoder/DecodeAVC.c -o $(BUILD_DIR)/libModernAVC/DecodeAVC.o
	ar -crsu   $(BUILD_DIR)/libModernAVC/libModernAVC.a $(BUILD_DIR)/libModernAVC/*.o
	ranlib -sf $(BUILD_DIR)/libModernAVC/libModernAVC.a

debug:
	mkdir -p   $(BUILD_DIR)/libModernAVC
	$(CC)      $(DEB_FLAGS) -c $(CURDIR)/libModernAVC/src/Decoder/DecodeSEI.c -o $(BUILD_DIR)/libModernAVC/DecodeSEI.o
	$(CC)      $(DEB_FLAGS) -c $(CURDIR)/libModernAVC/src/Decoder/DecodeSlice.c -o $(BUILD_DIR)/libModernAVC/DecodeSlice.o
	$(CC)      $(DEB_FLAGS) -c $(CURDIR)/libModernAVC/src/Decoder/DecodeMacroBlock.c -o $(BUILD_DIR)/libModernAVC/DecodeMacroBlock.o
	$(CC)      $(DEB_FLAGS) -c $(CURDIR)/libModernAVC/src/Decoder/ParseNAL.c -o $(BUILD_DIR)/libModernAVC/ParseNAL.o
	$(CC)      $(DEB_FLAGS) -c $(CURDIR)/libModernAVC/src/libModernAVC.c -o $(BUILD_DIR)/libModernAVC/libModernAVC.o
	$(CC)      $(DEB_FLAGS) -c $(CURDIR)/libModernAVC/src/Decoder/DecodeAVC.c -o $(BUILD_DIR)/libModernAVC/DecodeAVC.o
	ar -crsu   $(BUILD_DIR)/libModernAVC/libModernAVC.a $(BUILD_DIR)/libModernAVC/*.o
	ranlib -sf $(BUILD_DIR)/libModernAVC/libModernAVC.a

install:
	install -d -m 777 $(PREFIX)/lib
	install -d -m 777 $(PREFIX)/include
	install -C -v -m 444 $(BUILD_DIR)/libModernAVC/libModernAVC.a $(PREFIX)/lib/libModernAVC.a
	install -C -v -m 444 $(CURDIR)/libModernAVC/include/libModernAVC.h $(PREFIX)/include/libModernAVC.h

uninstall:
	rm -d -i $(PREFIX)

clean:
	cd $(BUILD_DIR)/libModernAVC/
	rm -f -v -r *.o
	rm -f -v -r libModernAVC.a
	rm -f -v -r .DS_Store
	rm -f -v -r Thumbs.db
	rm -f -v -r desktop.ini
	rmdir $(BUILD_DIR)
