# protobufExample
this is a try for google tool protobuf，I search the document online，and I have find some problem

my test enviroment: Linux tony-Lenovo-N480 3.19.0-78-generic #86~14.04.1-Ubuntu SMP Tue Dec 6 17:58:35 UTC 2016 x86_64 x86_64 x86_64 GNU/Linux
step1: download the protobuf 
`wget https://github.com/google/protobuf/releases/download/v3.2.0/protobuf-cpp-3.2.0.tar.gz`
step2: compile protobuf
`tar -zxvf protobuf-cpp-3.2.0.tar.gz`
`cd protobuf-cpp`
`./configure`
`make`
`make check`
`make install`
`protoc --version` to test if protoc install sucessfully

but I met a error: error while loading shared libraries.......

cause: protobuf default install path is `/usr/local/lib` but this path is not in environment path LD_LIBRARY_PATH
solution: 
`sudo touch /etc/ld.so.conf.d/libprotobuf.conf`
`echo "/usr/local/lib" > /etc/ld.so.conf.d/libprotobuf.conf` if you type this command you also can miss the command above.
`sudo ldconfig` to update
`protoc --version`

we just create a file.proto then use command to compile it to create addressbook.pb.h and addressbook.pb.cc

