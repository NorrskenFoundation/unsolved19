package main

import (
	"log"
	"net/http"

	"github.com/gorilla/mux"

	"github.com/northvolt/norrskenunsolved19/api/handler"
	"github.com/northvolt/norrskenunsolved19/api/neo4j"
)

const addr = "localhost:8080"

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

	// if err := Import(nj); err != nil {
	// 	log.Fatal(err)
	// }

	// return

	// if err := nj.Create(); err != nil {
	// 	log.Fatal(err)
	// }

	// c, err := nj.ExecEdgeQuery("ship00006")
	// if err != nil {
	// 	log.Fatal(err)
	// }
	// log.Print(c)
	// return

	h := handler.Handler{
		Nj: nj,
	}

	r := mux.NewRouter()
	r.Path("/info/{shipmentID}").
		Methods("GET").
		HandlerFunc(h.Co2Cost)

	r.HandleFunc("/ping", handler.OK)

	go http.ListenAndServe(addr, r)
	for {
	}

	// if err := nj.Exec(MatchQuery); err != nil {
	// 	log.Fatalf("failed to exec: %s", err)
	// }

}
