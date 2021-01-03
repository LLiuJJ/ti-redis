#### A Persistent Redis Store base on tikv

#### PreRequireds

1.pingcap grpc kvproto @ 0e3ce33

2.googletest @ 389cb68

3.libfiu @ 20ea5e8

#### Build

git clone --recursive https://gitee.com/LLiuJJ/ti-redis.git

mugit select main

mugit pull

cd ci; make build-dev

#### License
