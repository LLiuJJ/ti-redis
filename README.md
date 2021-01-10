#### A Persistent Redis Store base on tikv

#### PreRequireds

```
<repository
    path="third_party/googletest"
    url="https://github.com/google/googletest.git"
    branch="master"
    revision="db5f9ec567daff3beba53fd0bcd98e3f3562404c"
    />
<repository
    path="third_party/kvproto"
    url="https://github.com/pingcap/kvproto.git"
    branch="master"
    revision="0e3ce33f29b8be60d24610eb1c4695114de367ca"
    />
<repository
    path="third_party/libfiu"
    url="https://github.com/albertito/libfiu.git"
    branch="master"
    revision="20ea5e85ec63e3dedd6904e103fb2e56b46840cf"
    />
```

#### Build

git clone --recursive https://gitee.com/LLiuJJ/ti-redis.git

sh scripts/pre_download.sh

cd ci; make build-dev

#### GitHub 

https://github.com/LLiuJJ/ti-redis

#### License

MIT
