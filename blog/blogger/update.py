#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os, re, publish, prepare, util, itertools

root = u'..'


def generate_automatic_links(feed):
	i = 1
	links = ''
	for entry in reversed(feed.entry):
		links += "[%02i]: %s\n" % (i, entry.GetAlternateLink().href)
		i += 1
	return links

def get_blogger_feed(info):
	return info.blogger_service.GetFeed('/feeds/' + info.blog_id + '/posts/default')

def get_disk_feed():
	r = re.compile('^\d\d-\d\d\d\d-\d\d-\d\d-.*.md$')
	l = [x for x in os.listdir(root) if r.match(x)]
	l.sort()

	return l

def update(dry_run):
	if dry_run:
		print "This is a dry run. Nothing will be sent to blogger.com"
		print "Use command line argument --write to disable dry run"
	else:
		print "This is not a dry run. Updates will happen"

	info = util.Info()

	bloggerfeed = get_blogger_feed(info)

	autolinks = generate_automatic_links(bloggerfeed)

	diskfeed = get_disk_feed()

	unending_bloggerfeed = itertools.chain(reversed(bloggerfeed.entry), itertools.repeat(None))
	for d, b in itertools.izip(diskfeed, unending_bloggerfeed):
		name = os.path.join(root, d)
		title, doc = prepare.prepare(name, autolinks)
		if b:
			print "Considering", d
			should_update = False
			if title != b.title.text:
				print "\tUpdating title '%s' != '%s'" % (title, b.title.text)
				should_update = True
			if doc != b.content.text:
				print "\tUpdating content"
				should_update = True
			if should_update and not dry_run:
				publish.update(info, b, title, doc)
		else:
			print "Adding", d
			if not dry_run:
				publish.add(info, title, doc)


def main(argv):
	dry_run = (argv[1:].count('--write') == 0)
	update(dry_run)

if __name__=='__main__':
	import sys
	sys.exit(main(sys.argv))
