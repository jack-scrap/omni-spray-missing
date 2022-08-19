#!/bin/bash

for c in {a..z}
do
	./a.out "$c"
done

for c in {0..9}
do
	./a.out "$c"
done
