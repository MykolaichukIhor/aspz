#!/bin/bash

echo "=== Checking current user ==="
CURRENT_USER=$(whoami)
echo "whoami: $CURRENT_USER"

echo
echo "=== Full identity info (id) ==="
ID_OUTPUT=$(id)
echo "$ID_OUTPUT"

echo
echo "=== Parsed groups ==="


GROUPS=$(id -Gn)

for group in $GROUPS; do
    echo "- $group"
done

echo
echo "=== Additional details ==="
echo "UID: $(id -u)"
echo "GID: $(id -g)"
