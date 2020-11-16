
LDFLAGS+=-ldynamiclist -L/home/emb1013/code20201013/emb20201013/ds/llist

lstack:main.o lstack.o
	gcc -o $@ $^ $(LDFLAGS)
hanoi:hanoi.c lstack.o
	gcc -o $@ $^ $(LDFLAGS)

clean:
	rm *.o lstack

