/*
 main线程读argv[1]路径下对应的文件，如果有一个目录文件就创建一个线程，此线程统计目录下多少个文件，最终main线程能够得到argv[1]文件的总个数
 例如:
 	./a.out /etc

 */
