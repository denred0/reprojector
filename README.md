# Репроектор

В рамках задачи необходимо было написать программу, которая перепроецирует исходное изображение с одной камеры на другую камеры. 

**Параметры камеры:**
<br>_fx_ - фокусное расстояние по оси X
<br>_fy_ - фокусное расстояние по оси Y
<br>_cx_ - оптический центр камеры по оси X
<br>_cy_ - оптический центр камеры по оси Y
<br>_lambda_ - коэффициент радиальной дисторсии

<br>**Описание решения**

<br>docker pull ubuntu:20.04
<br>docker build -t projector .
<br>docker run --name projector_container -it --entrypoint bash projector
<br>cd src/
<br>mkdir build
<br>cd build
<br>cmake ..
<br>make
<br>./projector ../../data/1.jpg 10 10 -1 -1 0 5 5 -1 -1 0.1

<br>CTRL+D

<br>docker export projector_container > projector_container.tar
<br>mkdir projector_container && tar -xf projector_container.tar -C projector_container
<br>cd projector_container/app/data/
<br>ls 
