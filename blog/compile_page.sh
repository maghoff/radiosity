#!/bin/bash

cat \
	<(sed "s/%TITLE%/$(head -1 "$1")/" head.html.template) \
	<(markdown <(cat "$1" autolinks.md links.md)) \
	tail.html.template \
	> "$2"
