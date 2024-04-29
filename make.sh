#!/bin/sh
# axllr8tr's scalable build system 1.0
ROOT_DIR=.
OUT_DIR=$ROOT_DIR/out
TMP_DIR=$ROOT_DIR/tmp
TMP_SUFFIX=obj
OUT_FILE=$OUT_DIR/out.bin
ASM_FORMATS="*.S"
NASM_FORMATS="*.asm"
GCC_FORMATS="*.c"
GPP_FORMATS="*.cpp"
LD_SCRIPT=$ROOT_DIR/linker.ld
PREFIX=i686-elf
ASM_EXEC=$PREFIX-gcc
NASM_EXEC="nasm"
GCC_EXEC=$PREFIX-gcc
GPP_EXEC=$PREFIX-g++
LD_EXEC=$GCC_EXEC
QEMU_EXEC="qemu-system-i386"
COMMON_ARGS="-lgcc"
ASM_ARGS=""
GCC_ARGS="-ffreestanding -O0 -Wall -Wextra -fno-exceptions -I $ROOT_DIR/include -I $ROOT_DIR -std=gnu11 -nostdlib -mgeneral-regs-only" # bad
GPP_ARGS="-ffreestanding -O0 -Wall -Wextra -fno-exceptions -fno-rtti -I $ROOT_DIR/include -I $ROOT_DIR -std=gnu++11 -nostdlib"
LD_ARGS="-T $LD_SCRIPT -o $OUT_FILE -ffreestanding -O0 -nostdlib -fno-use-linker-plugin -fpermissive"
QEMU_ARGS="-kernel $OUT_FILE"

echo "Cleaning up..."
rm -rfv $TMP_DIR/* 2>/dev/null

echo "Assembling $ASM_FORMATS..."
for i in $(find -name "$ASM_FORMATS" 2>/dev/null)
do
  echo $i -\> $TMP_DIR/$(echo $i.$TMP_SUFFIX | sed 's/\.//' | sed 's/\//_/g')
  $ASM_EXEC -c $i -o $TMP_DIR/$(echo $i.$TMP_SUFFIX | sed 's/\.//' | sed 's/\//_/g') $ASM_ARGS
done

echo "Assembling $NASM_FORMATS..."
for i in $(find -name "$NASM_FORMATS" 2>/dev/null)
do
  echo $i -\> $TMP_DIR/$(echo $i.$TMP_SUFFIX | sed 's/\.//' | sed 's/\//_/g')
  $NASM_EXEC -f elf32 $i -o $TMP_DIR/$(echo $i.$TMP_SUFFIX | sed 's/\.//' | sed 's/\//_/g')
done

echo "Compiling $GCC_FORMATS..."
for i in $(find -name "$GCC_FORMATS" 2>/dev/null)
do
  echo $i -\> $TMP_DIR/$(echo $i.$TMP_SUFFIX | sed 's/\.//' | sed 's/\//_/g')
  $GCC_EXEC -DTHOS_BUILDDATE="\"$(date +%c)\"" -c $i -o $TMP_DIR/$(echo $i.$TMP_SUFFIX | sed 's/\.//' | sed 's/\//_/g') $GCC_ARGS $COMMON_ARGS
done

echo "Compiling $GPP_FORMATS..."
for i in $(find -name "$GPP_FORMATS" 2>/dev/null)
do
  $GPP_EXEC $GPP_PREARGS -c $i -o $TMP_DIR/$(echo $i.$TMP_SUFFIX | sed 's/\.//' | sed 's/\//_/g') $GPP_ARGS $COMMON_ARGS
done

echo "Linking..."
$LD_EXEC $LD_ARGS $(find $TMP_DIR/*.obj) $COMMON_ARGS

echo "Done!"
$QEMU_EXEC $QEMU_ARGS & disown
