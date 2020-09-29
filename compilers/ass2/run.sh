#!/bin/bash

for f in test/*.c-; do
	(./c- -p $f) > $f.out
done
