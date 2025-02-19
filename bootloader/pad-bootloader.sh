BL_FILE="bootloader.bin"
BL_TARGET_SIZE=$((32 * 1024))


# Get Bootloader file size
BL_FILE_SIZE=$(stat -c %s $BL_FILE)

# Calculate padding
PADDING_SIZE=$(expr $BL_TARGET_SIZE - $BL_FILE_SIZE)

# Create a stream of zeros with `PADDING_SIZE`and transform it into 0xff then
# Append it into the bootloader file
dd if=/dev/zero count=$PADDING_SIZE bs=1 | tr "\000" "\377" >> $BL_FILE
