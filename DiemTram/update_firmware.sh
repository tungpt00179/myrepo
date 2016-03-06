#!/bin/bash
if [ "$#" -ne 3 ] ; then
  echo "Usage: $0 URL Checksum ReplacePath" >&2
  exit 1
fi

cd /tmp

/usr/local/bin/wget -c -t 0 --timeout=30 --waitretry=30 "$1" >> a.log

checksum=($(shasum $(basename "$1")))

if [ "$2" = "$checksum" ]
then
  echo $(date)" Checksum correct." >> a.log
  sudo chown --reference=$3 $(basename "$1")
  sudo chmod --reference=$3 $(basename "$1")
  mv $(basename "$1") $3
  echo $(date) $(dirname "$3")/update.txt >> a.log
  rm -f $(dirname "$3")/update.txt
else
  echo $(date)" Checksum false." >> a.log
fi
