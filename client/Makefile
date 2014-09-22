client: ../lib/csapp.c ../lib/csapp.h client.c find_worker.h find_worker.c upload_file.h upload_file.c
	gcc client.c ../lib/csapp.c ../lib/csapp.h find_worker.h find_worker.c upload_file.h upload_file.c -o client -lpthread
clean:
	-rm -rf *.o client
