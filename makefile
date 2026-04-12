.PHONY: all clean-all zip clean

SUBDIRS = list stack queue heap graph dag spanningtree

all:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

clean-all:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	$(MAKE) clean

zip:
	zip -r algo_avancee.zip . -x \
		"*.o" "*.svg" "a.out" \
		"dag/testtopo" "graph/testgraph" "heap/testHeap" "list/testList" "queue/testqueue" "spanningtree/testprim" "stack/teststack" \
		"algo_avancee.zip" \
		".git/*" ".gitignore"

clean:
	rm -f algo_avancee.zip