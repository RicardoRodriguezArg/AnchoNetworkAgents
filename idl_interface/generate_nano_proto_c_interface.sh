echo "Generating C-Nano interface"
mkdir ./temp
echo "Uncompressing third-party Nano Lib"
unzip -d ./temp ../ext_libs/nano_pb/nanopb.zip
echo "Generating C headers and source files"
python3 ./temp/nanopb/generator/nanopb_generator.py message_interface_idl.proto

#TODO: need to install lib in system, but this is a workaround
sed -i 's+#include <pb.h>+#include "pb.h"+g' message_interface_idl.pb.h
mv message_interface_idl.pb.h message_interface_idl.pb.nano.h
mv message_interface_idl.pb.c message_interface_idl.pb.nano.c
sed -i 's+#include "message_interface_idl.pb.h"+#include "message_interface_idl.pb.nano.h"+g' message_interface_idl.pb.nano.c


echo "Copying headers and source files to target directory"
cp -v *.h ../interface/
cp -v *.c ../interface/
echo "Cleaning generated file"
rm -f *.h
rm -f *.c

echo "Updating nano lib source and headers files"
cp ./temp/nanopb/pb.h ../interface/
cp ./temp/nanopb/pb_common.h ../interface/
cp ./temp/nanopb/pb_common.c ../interface/
cp ./temp/nanopb/pb_decode.h ../interface/
cp ./temp/nanopb/pb_decode.c ../interface/
cp ./temp/nanopb/pb_encode.h ../interface/
cp ./temp/nanopb/pb_encode.c ../interface/

rm -rf ./temp
