#!/bin/bash

USER_NAME=$(whoami)
HOME_DIR=$(eval echo ~$USER_NAME)

ORIGINAL_FILE="/tmp/original_file.txt"
COPIED_FILE="$HOME_DIR/copied_file.txt"

echo "=== Step 1: Create file as normal user ==="
echo "Hello from normal user" > "$ORIGINAL_FILE"
ls -l "$ORIGINAL_FILE"

echo
echo "=== Step 2: Copy file as root ==="

# Копіюємо файл як root (потрібен sudo)
sudo cp "$ORIGINAL_FILE" "$COPIED_FILE"

echo "File copied to $COPIED_FILE"
ls -l "$COPIED_FILE"

echo
echo "=== Step 3: Try to modify file as normal user ==="

echo "Trying to append text..." >> "$COPIED_FILE" 2> /tmp/error.log

if [ $? -ne 0 ]; then
    echo "Modification failed:"
    cat /tmp/error.log
else
    echo "Modification succeeded"
fi

echo
echo "=== Step 4: Try to delete file as normal user ==="

rm "$COPIED_FILE" 2> /tmp/error_rm.log

if [ $? -ne 0 ]; then
    echo " Deletion failed:"
    cat /tmp/error_rm.log
else
    echo "Deletion succeeded"
fi
