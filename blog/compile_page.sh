#!/bin/bash

cat \
	<(sed "s/%TITLE%/$(head -1 "$1")/" head.html.template) \
	<(markdown <(cat "$1" links.md)) \
	tail.html.template \
	> "$2"
