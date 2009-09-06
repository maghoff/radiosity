TARGETS = \
	01-2009-08-22-Welcome.html \
	02-2009-08-22-GL_PROJECTION-abuse.html \
	03-2009-08-22-So-your-source-code-is-open-to-the-world.html \
	04-2009-09-06-Results.html \

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

remake: clean all

%.html: %.md head.html.template tail.html.template compile_page.sh links.md
	./compile_page.sh "$<" "$@"
