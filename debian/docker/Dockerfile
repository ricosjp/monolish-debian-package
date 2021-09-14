FROM ghcr.io/ricosjp/allgebra/cuda10_1/clang12/oss:21.06.1
LABEL maintainer "Ryo IGARASHI <rigarash@gmail.com>"

COPY . /monolish

RUN sed -i -e 's%http://[^ ]\+%mirror://mirrors.ubuntu.com/mirrors.txt%g' /etc/apt/sources.list
RUN apt-get update && apt-get install -y \
    git-buildpackage \ 
    debhelper \
    patchelf \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

# Build monolish with git-buildpackage
WORKDIR /monolish
RUN git clone -b ubuntu/focal/oss https://github.com/ricosjp/monolish-debian-package.git

# workaround allgebra bug
ENV CC=/usr/local/llvm-12.0.0/bin/clang \
    CXX=/usr/local/llvm-12.0.0/bin/clang++ \
    LIBRARY_PATH=/usr/local/llvm-12.0.0/lib64:/usr/local/cuda-10.1/lib64:/usr/local/cuda-10.1/lib64/stubs

WORKDIR /monolish/monolish-debian-package
RUN gbp buildpackage
