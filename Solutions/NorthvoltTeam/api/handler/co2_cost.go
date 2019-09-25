package handler

import (
	"bytes"
	"encoding/json"
	"io/ioutil"
	"log"
	"net/http"

	"github.com/gorilla/mux"
)

func (h *Handler) Co2Cost(w http.ResponseWriter, r *http.Request) {
	id := mux.Vars(r)["shipmentID"]

	c, err := h.Nj.ExecEdgeQuery(id)
	if err != nil {
		log.Print(err)
		return
	}

	dd, err := h.Nj.ExecEdgeTime(id)
	if err != nil {
		log.Print(err)
		return
	}

	trans := []float64{}
	for _, d := range dd {
		v := struct {
			From string  `json:"from"`
			To   string  `json:"to"`
			Time float64 `json:"time"`
		}{
			d.From,
			d.To,
			d.Time,
		}
		b, err := json.Marshal(v)
		if err != nil {
			log.Print(err)
			return
		}
		resp, err := http.Post("http://localhost:5000/api", "application/json", bytes.NewBuffer(b))
		if err != nil {
			log.Printf("error post %s", err)
			return
		}
		t, err := ioutil.ReadAll(resp.Body)
		if err != nil {
			log.Print(err)
			return
		}

		var risk float64
		if err := json.Unmarshal(t, &risk); err != nil {
			log.Print(err)
			return
		}
		trans = append(trans, risk)

	}

	//log.Print(c)

	t := struct {
		Co2             float64
		TransactionRisk []float64
	}{
		Co2:             c,
		TransactionRisk: trans,
	}
	WriteJSON(w, r, t)

	// get all the data from node4JS

	// calculate the cost

	// send the

}

func WriteJSON(w http.ResponseWriter, r *http.Request, v interface{}) {
	w.Header().Set("content-type", "application/json;charset=utf-8")
	e := json.NewEncoder(w)
	if has(r, "pretty") {
		e.SetIndent("", "    ")
	}
	if err := e.Encode(v); err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
}

// has returns true if the query has a parameter with the given name.
func has(r *http.Request, name string) bool {
	_, ok := r.URL.Query()[name]
	return ok
}
