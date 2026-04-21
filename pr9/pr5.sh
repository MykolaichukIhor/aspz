#!/bin/bash

USER_NAME=$(whoami)
TMP_FILE="/tmp/test_perm_file.txt"

echo "=== Step 1: Create file as normal user ==="
echo "Initial content" > "$TMP_FILE"
ls -l "$TMP_FILE"

echo
echo "=== Function to test permissions ==="

test_access() {
    echo "---- Testing current permissions ----"
    ls -l "$TMP_FILE"

    # Test read
    if cat "$TMP_FILE" > /dev/null 2>&1; then
        echo "Read: allowed"
    else
        echo "Read: denied"
    fi

    # Test write
    if echo "test" >> "$TMP_FILE" 2>/dev/null; then
        echo "Write: allowed"
    else
        echo "Write: denied"
    fi

    echo
}

echo
echo "=== Step 2: Original permissions ==="
test_access

echo "=== Step 3: Change owner to root (no write for others) ==="
sudo chown root:root "$TMP_FILE"
sudo chmod 644 "$TMP_FILE"
test_access

echo "=== Step 4: Remove write for user completely ==="
sudo chmod 444 "$TMP_FILE"
test_access

echo "=== Step 5: Give write to everyone ==="
sudo chmod 666 "$TMP_FILE"
test_access

echo "=== Step 6: Return ownership to user ==="
sudo chown $USER_NAME:$USER_NAME "$TMP_FILE"
sudo chmod 600 "$TMP_FILE"
test_access

echo "=== Done ==="
