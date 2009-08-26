#!/usr/bin/env python
# -*- coding: utf-8 -*-

from subprocess import *

def markdown(inp):
	sp = Popen(['markdown'], stdout=PIPE, stdin=PIPE)
	sp.stdin.write(inp)
	output = sp.communicate()[0]
	sp.wait()
	return output

def main(argv):
	print markdown(open(argv[1], 'rb').read())
	return 0

if __name__=='__main__':
	import sys
	sys.exit(main(sys.argv))
