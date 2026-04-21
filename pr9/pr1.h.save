#!/bin/bash

current_user=$(whoami)
MIN_UID=1000
found=0

while IFS=: read -r username x uid gid comment home shell
do
    if [ "$uid" -ge "$MIN_UID" ] && [ "$username" != "$current_user" ]; then
        echo "Знайдено іншого звичайного користувача: $username (UID=$uid)"
        found=1
    fi
done < <(getent passwd)

if [ "$found" -eq 0 ]; then
    echo "Інших звичайних користувачів не знайдено."
fi
