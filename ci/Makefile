default: image build-test

BUILDER_IMAGE := $(or $(BUILDER_IMAGE),hub.pingcap.net/tikv/client-c)

image:
	docker build -f Dockerfile -t $(BUILDER_IMAGE) .
build-test:
	su -c "setenforce 0";
	docker run --rm -v $(realpath ..):/ti-redis $(BUILDER_IMAGE) /ti-redis/ci/build-test.sh
build-dev:
	docker run --rm -v $(realpath ..):/ti-redis cxspace/ti-redis-dev:v0.0.1 /ti-redis/ci/build-test.sh;
build-run:
	docker run -it -v $(realpath ..):/ti-redis cxspace/ti-redis-dev:v0.0.1 /bin/bash;
