#!/bin/bash

for f in *.c-; do
	(./c- -P $f) > $f.me
done
