#!/bin/bash

USER_NAME=$(whoami)

echo "=============================="
echo "1. HOME DIRECTORY ($HOME)"
echo "=============================="

ls -l "$HOME"

echo
echo "Testing access in HOME..."

TEST_FILE="$HOME/test_access_file.txt"


echo "test" > "$TEST_FILE" 2>/dev/null && echo "✔ Write in HOME: allowed" || echo "✘ Write in HOME: denied"


cat "$TEST_FILE" >/dev/null 2>&1 && echo "✔ Read in HOME: allowed" || echo "✘ Read in HOME: denied"


chmod +x "$TEST_FILE" 2>/dev/null
"$TEST_FILE" >/dev/null 2>&1 && echo "✔ Execute in HOME: allowed" || echo "✘ Execute in HOME: denied"

echo
echo "=============================="
echo "2. /usr/bin"
echo "=============================="

ls -l /usr/bin | head -n 10

echo
echo "Testing restricted access in /usr/bin..."

BIN_FILE="/usr/bin/ls"


cat "$BIN_FILE" >/dev/null 2>&1 && echo "✔ Read /usr/bin file: allowed" || echo "✘ Read /usr/bin file: denied"


echo "hack" >> "$BIN_FILE" 2>/dev/null && echo "✔ Write /usr/bin file: allowed (unexpected!)" || echo "✘ Write /usr/bin file: denied"


"$BIN_FILE" /tmp >/dev/null 2>&1 && echo "✔ Execute /usr/bin binary: allowed" || echo "✘ Execute /usr/bin binary: denied"

echo
echo "=============================="
echo "3. /etc"
echo "=============================="

ls -l /etc | head -n 10

echo
echo "Testing restricted access in /etc..."

CONF_FILE="/etc/passwd"


cat "$CONF_FILE" >/dev/null 2>&1 && echo "✔ Read /etc file: allowed" || echo "✘ Read /etc file: denied"


echo "hack" >> "$CONF_FILE" 2>/dev/null && echo "✔ Write /etc file: allowed (unexpected!)" || echo "✘ Write /etc file: denied"


"$CONF_FILE" >/dev/null 2>&1 && echo "✔ Execute /etc file: allowed (unexpected!)" || echo "✘ Execute /etc file: denied"

echo
echo "=============================="
echo "SUMMARY"
echo "=============================="
echo "User: $USER_NAME"
echo "UID: $(id -u)"
echo "Groups: $(id -Gn)"
