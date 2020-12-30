#!/bin/bash

file_ext="Po"
EXCLUDE_LIST=""


for entry in *.$file_ext
do
  rm $entry
  echo "" > $entry

done
