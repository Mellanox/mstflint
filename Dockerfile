FROM centos:7.9.2009

# Run update in a seperate layer to minimize RE-build time
RUN yum -y update 

RUN yum -y install \
    glibc \
    make \
    autoconf \
    automake \
    git \
    libtool \
    zlib-devel \
    tar \
    wget \
    openssl-devel \
    gcc \
    gcc-c++

# backwards compatilibity due to inifiniband/libibmad
RUN wget -qO /tmp/rdma-core-44.0.tar.gz https://github.com/linux-rdma/rdma-core/releases/download/v44.0/rdma-core-44.0.tar.gz \
    && cd /tmp \
    && tar xzvf rdma-core-44.0.tar.gz \
    && cp -rf /tmp/rdma-core-44.0/libibmad/ /usr/include/infiniband/

ENTRYPOINT ["/bin/bash"]