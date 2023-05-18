all:
	$(MAKE) -C build all

clean:
	$(MAKE) -C build clean

flash: build/main.bin
	st-flash write build/main.bin 0x8000000
