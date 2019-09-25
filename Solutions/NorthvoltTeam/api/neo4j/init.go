package neo4j

import (
	"fmt"
	"log"
	"strconv"
	"time"

	"github.com/pkg/errors"

	"github.com/neo4j/neo4j-go-driver/neo4j"
)

type Neo4j struct {
	Username string
	Password string

	query   string
	driver  neo4j.Driver
	session neo4j.Session
}

type Edge struct {
	Arrival   string
	Carrier   int
	Co2       float32
	Departure time.Time
	Distance  float32
	Dwell     time.Time
	FromLat   float32
	FromLon   float32
	FromName  string
	Mode      string
	Shipment  string
	Step      int
	Time      float32
	ToLat     float32
	ToLon     float32
	ToName    string
}

//const Neo4jURI = "bolt://0.tcp.ngrok.io:10246"

const Neo4jURI = "bolt://0.0.0.0:7687"

const MatchQuery = `MATCH (n)
RETURN n;`

func (n *Neo4j) NewSession() (neo4j.Session, error) {
	var err error
	n.driver, err = neo4j.NewDriver(Neo4jURI, neo4j.BasicAuth(n.Username, n.Password, ""))
	if err != nil {
		return nil, err
	}

	n.session, err = n.driver.Session(neo4j.AccessModeRead)
	if err != nil {
		return nil, err
	}
	return n.session, nil
}

func (n *Neo4j) Close() {
	n.driver.Close()
	n.session.Close()
}

func (n *Neo4j) CreateNode(obj map[string]interface{}) error {
	result, err := n.session.Run("CREATE (n:Site { name: $name, lat: $lat, lon: $lon, type: $type}) RETURN n.name", obj)
	if err != nil {
		return err // handle error
	}

	for result.Next() {
		fmt.Printf("Created Item %s\n", result.Record().GetByIndex(0).(string))
	}
	if err = result.Err(); err != nil {
		return err // handle error
	}
	return nil
}

func (n *Neo4j) CreateEdge(edge map[string]interface{}) error {

	q := `MATCH (a:Site),(b:Site)
	WHERE a.name = $from_name AND b.name = $to_name
	CREATE (a)-[r:TRANSACTION { arrival: $arrival, carrier: $carrier, co2: $co2, departure: $departure, distance: $distance, dwell: $dwell, from_lat: $from_lat, from_name: $from_name, mode: $mode, shipment: $shipment, step: $step, time: $time, to_lat: $to_lat, to_lon: $to_lon, to_name: $to_name }]->(b)
	RETURN r.shipment`
	log.Println(q)
	result, err := n.session.Run(q, edge)
	if err != nil {
		log.Print(err)
		return err // handle error
	}

	for result.Next() {
		fmt.Printf("Created Item for shipment %s\n", result.Record().GetByIndex(0).(string))
	}
	if err = result.Err(); err != nil {
		return err // handle error
	}
	return nil
}

func (n *Neo4j) ExecEdgeQuery(shipment string) (float64, error) {
	// Execute the transaction function
	n.query = fmt.Sprintf(`MATCH ()-[r:TRANSACTION]->() WHERE r.shipment = '%s' RETURN r.co2`, shipment)
	p, err := n.session.ReadTransaction(n.executeQuery)
	if err != nil {
		return 0, err
	}

	//fmt.Printf("\n%d records processed\n", p)
	return p.(float64), nil
}

func (n *Neo4j) executeQuery(tx neo4j.Transaction) (interface{}, error) {
	var (
		counter int
		result  neo4j.Result
		err     error
		co2     float64
	)

	log.Print(n.query)
	if result, err = tx.Run(n.query, nil); err != nil {
		return nil, errors.Wrapf(err, "failed to run query")
	}

	for result.Next() {
		a, _ := result.Record().Values()[0].(string)
		aa, _ := strconv.ParseFloat(a, 32)

		//a := result.Record().GetByIndex(0).([]map[string]interface{})
		log.Printf("%#v", aa)

		//processRecord(result.Record())
		co2 = co2 + aa
		counter++
	}
	if err = result.Err(); err != nil {
		return nil, err
	}

	return co2, nil
}

// Simple record values printing logic, open to improvements
func processRecord(record neo4j.Record) {
	for index, value := range record.Values() {
		if index > 0 {
			fmt.Print("\t")
		}
		fmt.Printf("%#v", value)

	}
	fmt.Print("\n")
}

func (n *Neo4j) ExecEdgeTime(shipment string) ([]timeTransac, error) {
	// Execute the transaction function
	n.query = fmt.Sprintf(`MATCH ()-[r:TRANSACTION]->() WHERE r.shipment = '%s' RETURN r.to_name, r.from_name, r.time`, shipment)
	p, err := n.session.ReadTransaction(n.executeQueryTime)
	if err != nil {
		return nil, err
	}

	fmt.Printf("%#v\n", p)
	return p.([]timeTransac), nil
}

type timeTransac struct {
	To   string
	From string
	Time float64
}

func (n *Neo4j) executeQueryTime(tx neo4j.Transaction) (interface{}, error) {
	var (
		counter int
		result  neo4j.Result
		err     error
	)

	log.Print(n.query)
	if result, err = tx.Run(n.query, nil); err != nil {
		return nil, errors.Wrapf(err, "failed to run query")
	}

	res := []timeTransac{}
	for result.Next() {
		to, _ := result.Record().Values()[0].(string)
		from, _ := result.Record().Values()[1].(string)
		t, _ := result.Record().Values()[2].(string)
		tt, _ := strconv.ParseFloat(t, 32)

		//processRecord(result.Record())
		res = append(res, timeTransac{
			To:   to,
			From: from,
			Time: tt,
		})
		counter++
	}
	if err = result.Err(); err != nil {
		return nil, err
	}

	return res, nil
}
