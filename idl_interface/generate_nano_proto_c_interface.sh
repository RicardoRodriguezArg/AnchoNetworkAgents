echo "Generating C-Nano interface"
mkdir ./temp
echo "Uncompressing third-party Nano Lib"
unzip -d ./temp ../ext_libs/nano_pb/nanopb.zip
echo "Generating C headers and source files"
python3 ./temp/nanopb/generator/nanopb_generator.py message_interface_idl.proto
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

echo "Cleaning previous installation"
unlink /usr/local/include/pb.h 
unlink /usr/local/include/pb_common.h
unlink /usr/local/include/pb_decode.h
unlink /usr/local/include/pb_encode.h

echo "Creating sym link for system wide compilation"
ln -s ../interface/pb.h        /usr/local/include/pb.h 
ln -s ../interface/pb_common.h /usr/local/include/pb_common.h
ln -s ../interface/pb_decode.h /usr/local/include/pb_decode.h
ln -s ../interface/pb_encode.h /usr/local/include/pb_encode.h

rm -rf ./temp
