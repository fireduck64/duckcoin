#!/bin/sh

i=0
while [ $i -lt 1000 ]
do
  s=$i
  if [ $i -lt 10 ]
  then
    s="0$s"
  fi
  if [ $i -lt 100 ]
  then
    s="0$s"
  fi
  echo $s
  ../src/duckcoind getnewaddress >> address-list.txt
  i=$(($i+1))
done
