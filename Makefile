# Definições do Compilador para Xbox 360
CC      = xenon-gcc
CXX     = xenon-g++
LD      = xenon-ld
OBJCOPY = xenon-objcopy

# Flags recomendadas para a arquitetura Xenon do Xbox 360
CFLAGS  = -m32 -fno-pic -mpowerpc64 -mcpu=cell
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
