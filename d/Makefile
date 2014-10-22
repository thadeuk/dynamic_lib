progdl: clean
	    g++ -rdynamic progdl.cpp -o progdl -ldl

libd:
	dmd -c dll.d -fPIC
	dmd -oflibdll.so dll.o -defaultlib=libphobos2.so -shared

clean:
		rm -f progdl *.o *.so
