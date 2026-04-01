.PHONY: zip clean

zip:
	zip -r algo_avancee.zip . -x "*.o" "*.svg" "a.out" "dag/testtopo" "graph/testgraph" "heap/testheap" "list/testList" "queue/testqueue" "spanningtree/testprim" "stack/teststack" ".git/*" ".gitignore"

clean:
	rm -f algo_avancee.zip