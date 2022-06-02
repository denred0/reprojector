# Репроектор

docker pull ubuntu:20.04
docker build -t projector .
docker run --name projector_container -it --entrypoint bash projector
cd src/
mkdir build
cd build
cmake ..
make
./projector ../../data/1.jpg 10 10 -1 -1 0 5 5 -1 -1 0.1

CTRL+D

docker export projector_container > projector_container.tar
mkdir projector_container && tar -xf projector_container.tar -C projector_container
cd projector_container/app/data/
ls 
