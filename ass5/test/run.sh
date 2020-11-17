#!/bin/bash

for f in *.c-; do
	(../c- $f) > $f.out
done
