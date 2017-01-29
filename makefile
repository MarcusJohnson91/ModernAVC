PACKAGE_NAME        := libAVC
FILE                := $(CURDIR)/libAVC/include/libAVC.h
VERSION             := $(shell cat ${FILE} | grep -e "@version")
CC                  := cc
DESTINATION         := /usr/local/Packages/$(PACKAGE_NAME)
BUILD_DIR           := $(CURDIR)/BUILD
CFLAGS              := -std=c11 -march=native -funroll-loops `pkg-config --libs libBitIO`
LDFLAGS             := -flto=thin
DEB_ERROR_OPTIONS   := -Wno-unused-parameter -Wno-unused-variable -Wno-int-conversion
REL_ERROR_OPTIONS   := -Weverything -Wunreachable-code -Wno-conversion
DEB_FLAGS           := $(CFLAGS) -g -o0 $(DEB_ERROR_OPTIONS) $(LDFLAGS)
REL_FLAGS           := $(CFLAGS) -ofast $(REL_ERROR_OPTIONS) $(LDFLAGS)

.PHONY: all detect_platform Release Debug Install Uninstall Clean distclean

all: release
	$(release)
	$(install)
check: 
	$(test)
distclean: 
	$(clean)

CHECK_VERS:
	$(shell echo ${VERSION})

release:
	mkdir -p   $(BUILD_DIR)
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
	mkdir -p   $(BUILD_DIR)
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
	install -d -m 777 $(DESTINATION)/lib
	install -d -m 777 $(DESTINATION)/include
	install -C -v -m 444 $(BUILD_DIR)/libAVC/libAVC.a $(DESTINATION)/lib/libAVC.a
	install -C -v -m 444 $(CURDIR)/libAVC/include/libAVC.h $(DESTINATION)/include/libAVC.h

uninstall:
	rm -d -i $(DESTINATION)

clean:
	cd $(BUILD_DIR)/libAVC/
	rm -f -v -r libAVC.o
	rm -f -v -r DecodeSEI.o
	rm -f -v -r DecodeAVC.o
	rm -f -v -r DecodeSlice.o
	rm -f -v -r DecodeMacroBlock.o
	rm -f -v -r ParseNAL.o
	rm -f -v -r libAVC.a
	rm -f -v -r .DS_Store
	rm -f -v -r Thumbs.db
	rm -f -v -r desktop.ini
	rmdir $(BUILD_DIR)
