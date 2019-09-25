package main

import (
	"log"
	"os"

	"github.com/northvolt/norrskenunsolved19/api/neo4j"
	csvmap "github.com/recursionpharma/go-csv-map"
)

func ImportEdges(nj neo4j.Neo4j) error {
	f, err := os.Open("../data/transactions.csv")
	if err != nil {
		return err
	}
	defer f.Close()

	reader := csvmap.NewReader(f)
	reader.Columns, err = reader.ReadHeader()
	if err != nil {
		return err
	}
	records, err := reader.ReadAll()
	if err != nil {
		return err
	}
	for _, rrs := range records {
		rs := map[string]interface{}{}
		for k, v := range rrs {
			rs[k] = v
		}
		if err := nj.CreateEdge(rs); err != nil {
			log.Print(err)
		}
	}
	return nil
}

func ImportNodes(nj neo4j.Neo4j) error {
	f, err := os.Open("../data/nodes.csv")
	if err != nil {
		return err
	}
	defer f.Close()

	reader := csvmap.NewReader(f)
	reader.Columns, err = reader.ReadHeader()
	if err != nil {
		return err
	}
	records, err := reader.ReadAll()
	if err != nil {
		return err
	}
	for _, rrs := range records {
		rs := map[string]interface{}{}
		for k, v := range rrs {
			rs[k] = v
		}
		if err := nj.CreateNode(rs); err != nil {
			log.Print(err)
		}
	}
	return nil
}
