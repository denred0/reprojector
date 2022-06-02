# set base image (host OS)
FROM ubuntu:20.04

# avoiding question about timezone
ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# eigen and opencv
RUN apt-get update 
RUN apt-get install -y build-essential libopencv-dev libeigen3-dev cmake \
        && rm -rf /var/lib/apt/lists/*

# build workdir
WORKDIR /app

# copy data
COPY data ./data
COPY src ./src

CMD [ "bin/bash/"]
