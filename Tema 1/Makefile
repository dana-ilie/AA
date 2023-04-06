CC=gcc
CFLAGS=-std=c99 -Wall -Wextra

.PHONY: clean

build:testTreap.o testHashtable.o
	

testTreap.o: testTreap.c
	$(CC) testTreap.c -o testTreap $(CFLAGS)

testHashtable.o: testHashtable.c
	$(CC) testHashtable.c -o testHashtable $(CFLAGS)

run-best:
	./testTreap < ./test.in > ./test.out

run-p1:
	./testTreap < ./test.in > ./test.out

run-p2:
	./testHashtable < ./test.in > ./test.out

generate-p1:
	./testTreap < ./in/test1.in > ./out/p1/test1.out
	./testTreap < ./in/test2.in > ./out/p1/test2.out
	./testTreap < ./in/test3.in > ./out/p1/test3.out
	./testTreap < ./in/test4.in > ./out/p1/test4.out
	./testTreap < ./in/test5.in > ./out/p1/test5.out
	./testTreap < ./in/test6.in > ./out/p1/test6.out
	./testTreap < ./in/test7.in > ./out/p1/test7.out
	./testTreap < ./in/test8.in > ./out/p1/test8.out
	./testTreap < ./in/test9.in > ./out/p1/test9.out
	./testTreap < ./in/test10.in > ./out/p1/test10.out
	./testTreap < ./in/test11.in > ./out/p1/test11.out
	./testTreap < ./in/test12.in > ./out/p1/test12.out
	./testTreap < ./in/test13.in > ./out/p1/test13.out
	./testTreap < ./in/test14.in > ./out/p1/test14.out
	./testTreap < ./in/test15.in > ./out/p1/test15.out
	./testTreap < ./in/test16.in > ./out/p1/test16.out
	./testTreap < ./in/test17.in > ./out/p1/test17.out
	./testTreap < ./in/test18.in > ./out/p1/test18.out
	./testTreap < ./in/test19.in > ./out/p1/test19.out
	./testTreap < ./in/test20.in > ./out/p1/test20.out


generate-p2:
	./testHashtable < ./in/test1.in > ./out/p2/test1.out
	./testHashtable < ./in/test2.in > ./out/p2/test2.out
	./testHashtable < ./in/test3.in > ./out/p2/test3.out
	./testHashtable < ./in/test4.in > ./out/p2/test4.out
	./testHashtable < ./in/test5.in > ./out/p2/test5.out
	./testHashtable < ./in/test6.in > ./out/p2/test6.out
	./testHashtable < ./in/test7.in > ./out/p2/test7.out
	./testHashtable < ./in/test8.in > ./out/p2/test8.out
	./testHashtable < ./in/test9.in > ./out/p2/test9.out
	./testHashtable < ./in/test10.in > ./out/p2/test10.out
	./testHashtable < ./in/test11.in > ./out/p2/test11.out
	./testHashtable < ./in/test12.in > ./out/p2/test12.out
	./testHashtable < ./in/test13.in > ./out/p2/test13.out
	./testHashtable < ./in/test14.in > ./out/p2/test14.out
	./testHashtable < ./in/test15.in > ./out/p2/test15.out
	./testHashtable < ./in/test16.in > ./out/p2/test16.out
	./testHashtable < ./in/test17.in > ./out/p2/test17.out
	./testHashtable < ./in/test18.in > ./out/p2/test18.out
	./testHashtable < ./in/test19.in > ./out/p2/test19.out
	./testHashtable < ./in/test20.in > ./out/p2/test20.out

clean:
	rm -rf *.o