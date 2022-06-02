# set base image (host OS)
FROM ubuntu:20.04

# avoiding question about timezone
ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# eigen and opencv
RUN apt update 
RUN apt install -y build-essential libopencv-dev libeigen3-dev

# cmake
RUN apt-get install -y cmake

# build workdir
WORKDIR /app

# copy data
COPY data ./data
COPY src ./src

CMD [ "bin/bash/"]