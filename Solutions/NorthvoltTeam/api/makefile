.PHONY: build neo4j init all

all: build
	$(MAKE) neo4j &  $(MAKE) tf & $(MAKE) init & $(MAKE) run

build:
	go build -mod=vendor -o ./build/import ./import/...
	go build -mod=vendor -o ./build/api ./main.go

neo4j:
	docker run \
    --publish=7474:7474 --publish=7687:7687 \
    --env NEO4J_AUTH=none \
    neo4j:3.5

tf:
	python3 ../server.py

init:
	./build/import

run:
	./build/api
