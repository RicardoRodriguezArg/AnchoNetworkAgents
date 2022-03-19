echo "Generating python interface"
protoc -I=./ --python_out=./ ./message_interface_idl.proto
echo "Updating/copying new interface to proper folder"
cp *.py ../interface
echo "Cleaning generated file"
rm -f *.py
