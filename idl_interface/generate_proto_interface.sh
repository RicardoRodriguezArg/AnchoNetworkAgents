echo "Generating python interface"
protoc -I=./ --python_out=./ ./message_interface_idl.proto
echo "Generating C++ interface"
protoc -I=./ --cpp_out=./ ./message_interface_idl.proto
echo "Updating/copying new interface to proper folder"
cp *.py ../interface
cp *.cc ../interface
cp *.h ../interface
echo "Cleaning generated file"
rm -f *.py
rm -f *.cc
rm -f *.h
