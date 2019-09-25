package main

import (
	"log"

	"github.com/northvolt/norrskenunsolved19/api/neo4j"
)

func main() {

	nj := neo4j.Neo4j{
		Username: "neo4j",
		Password: "password",
	}
	_, err := nj.NewSession()
	if err != nil {
		log.Fatal(err)
	}
	defer nj.Close()

	if err := ImportNodes(nj); err != nil {
		log.Fatal(err)
	}

	log.Print("import edges")
	if err := ImportEdges(nj); err != nil {
		log.Fatal(err)
	}

}
