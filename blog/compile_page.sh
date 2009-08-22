#!/bin/bash

cat \
	<(sed "s/%TITLE%/$(head -1 "$1")/" head.html.template) \
	<(markdown "$1") \
	tail.html.template \
	> "$2"
