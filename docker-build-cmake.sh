#! /bin/bash

DOCKER_IMAGE="openmp-workshop"

docker images | grep $DOCKER_IMAGE > /dev/null
if [ $? -ne 0 ] ; then
    echo "Missing docker image: $DOCKER_IMAGE. \n Building docker image...\n"
    sh docker/create-docker.sh
fi

docker run --rm -v `pwd`:/home/user $DOCKER_IMAGE bash -c "./build-cmake.sh"
