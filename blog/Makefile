TARGETS = \
	01-2009-08-22-Welcome.html \
	02-2009-08-22-GL_PROJECTION-abuse.html \
	03-2009-08-22-So-your-source-code-is-open-to-the-world.html \
	04-2009-09-06-Results.html \
	05-2009-09-07-Technical-details.html \
	06-2009-09-30-Pretty-results.html \

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

remake: clean all

FORCE:

autolinks.md: FORCE
	./make_autolinks.py

%.html: %.md head.html.template tail.html.template compile_page.sh links.md autolinks.md
	./compile_page.sh "$<" "$@"
