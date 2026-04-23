TARGET = hqc-gf-mul

SRC += hqc-gf-mul-firm.c

EXTRAINCDIRS += src

CRYPTO_TARGET = NONE
SS_VER = SS_VER_2_1

include ../simpleserial/Makefile.simpleserial
FIRMWAREPATH = ../.
include $(FIRMWAREPATH)/Makefile.inc

OBJDIR = objdir-$(PLATFORM)
EXTRA_CPP_OBJ = $(OBJDIR)/gf-target.o

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXTRA_CPP_OBJ): gf-target.cpp | $(OBJDIR)
	arm-none-eabi-g++ $(CFLAGS) -O3 $(addprefix -I,$(EXTRAINCDIRS)) \
	-I.././simpleserial/ -I.././hal/ -I.././crypto/ \
	-c $< -o $@

$(TARGET)-$(PLATFORM).elf: $(EXTRA_CPP_OBJ)

OBJ += $(EXTRA_CPP_OBJ)