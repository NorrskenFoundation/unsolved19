import React from 'react';
import Plot from 'react-plotly.js';

class StyledPlot extends React.Component {


  constructData = (data) => {
    return data.map(d => {
      return (
        {
          x: d.x,
          y: d.y,
          type: 'scatter',
          mode: 'lines+points',
          marker: {color: d.color},
        }
      )
    })
  }


  render(){
    return (
      <div style={{height: '100%', width: '100%', ...this.props.style}}>
        <Plot
          data={this.constructData(this.props.data)}
          layout={ {width: '100%', height: '100%', title: this.props.title} }
          config={{
            displayModeBar: false,
            staticPlot: this.props.staticPlot,
            responsive: true,
          }}
        />
      </div>
    )
  }

}

export default StyledPlot;
