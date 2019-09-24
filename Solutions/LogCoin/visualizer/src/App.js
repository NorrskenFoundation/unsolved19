import React from 'react';
import 'bootstrap';
import { Button, FormControl, InputGroup } from 'react-bootstrap';
import { Route, Link, BrowserRouter, Switch } from 'react-router-dom';
import './App.css';
import { Sankey } from 'react-vis';

class SearchInput extends React.Component {
  constructor(props) {
    super(props);
    this.state = { id: "", currentLink: null }
  }

  handleInputChange(id) {
      this.setState({
        id
      })
  }

  render() {
    return (
      <div className="centered-container">
          <InputGroup className="mb-3">
            <FormControl
              placeholder="Enter consignment ID"
              onChange={event => this.handleInputChange(event.target.value)} 
              type="text"
            />
            <InputGroup.Append>
              <Link className="btn btn-outline-primary" to={`/network-graph/${this.state.id}`}>Search</Link>
            </InputGroup.Append>
          </InputGroup>
      </div>
    );
  }
}

class NetworkGraph extends React.Component {
  constructor(props) {
    super(props)
    this.state = { 
      id: this.props.match.params.id,
      transactions: {
        nodes: [],
        links: []
      }
    }
  }

  componentWillMount() {
    var transactionId = this.state.id

    var transactions = [
      {
        "from": [
          {"account": "Iron Mine A", "amount": 5}, 
          {"account": "Iron Mine B", "amount": 10},
          {"account": "Iron Mine C", "amount": 5},
        ],
        "to": {"account": "Iron Smeltery A", "amount": 20},
      },
      {
        "from": [
          {"account": "Iron Mine A", "amount": 5}, 
        ],
        "to": {"account": "Iron Smeltery B", "amount": 5},
      },
      {
        "from": [
          {"account": "Copper Mine", "amount": 8},
        ],
        to: {"account": "Copper Smeltery", "amount": 8}
      },
      {
        "from": [
          {"account": "Iron Smeltery A", "amount": 10},
          {"account": "Copper Smeltery", "amount": 4}
        ],
        to: {"account": "PCBs 'r' Us", "amount": 3}
      },
      {
        "from": [
          {"account": "Iron Smeltery B", "amount": 5},
        ],
        "to": {"account": "Bolts Inc", "amount": 2},
      },
      {
        "from": [
          {"account": "PCBs 'r' Us", amount: 3},
          {account: "Bolts Inc", amount: 2}
        ],
        to: {account: "Laptops You Thought Would Work, Plc", amount: 1}
      }
    ]

    // TODO Fix API
    /*fetch(`/account/${transactionId}/transaction-tree`)
    .then(response => response.json())
    .then((response) => {*/
      
    // nodes: [{"name": "foo", "name": "bar", "name": "tar"}]
    //                    foo            bar
    // links: [{"source": "0", "target": "1", "value": "1.0"}]
    var result = {
      "nodes": [],
      "links": []
    };
    var fromNames = transactions.map((transaction) => transaction.from.map((from) => from.account)).flat()
    var toNames = transactions.map((transaction) => transaction.to.account)
    var names = new Set()
    fromNames.concat(toNames).forEach((name) => names.add(name))
    result.nodes = Array.from(names).map((name) => ({"name": name}))
    var onlyNames = result.nodes.map((obj) => obj.name)
    var links = []
    transactions.forEach((transaction) => {
      transaction.from.forEach((from) => { 
        links.push({source: onlyNames.indexOf(from.account), target: onlyNames.indexOf(transaction.to.account), value: from.amount})
      }); 
    });
    result.links = links
    this.setState({
      transactions: result
    })
  }

  render() {
    var currentLink = this.state.currentLink
    return (
      <Sankey
          animation
          margin={50}
          nodes={this.state.transactions.nodes}
          links={this.state.transactions.links}
          width={960}
          height={800}
          layout={24}
          nodeWidth={15}
          nodePadding={10}
          style={{
            links: {
              opacity: 0.3
            },
            labels: {
              fontSize: '12px',
            },
          }}
        />
    );
  }
}

function App() {
  return (
    <BrowserRouter>
      <Switch>
        <Route path="/network-graph/:id" component={NetworkGraph}/>
        <Route path="/" component={SearchInput} exactMatch={true}/>
      </Switch>
    </BrowserRouter>
  );
}

export default App;
