import React, {Component} from 'react';
import Plot from 'react-plotly.js';



// This is a custom discrete color scale
// used by the contour map and color bar
const colorScale = [
    [0, 'rgb(11,90,169)'], [1/6, 'rgb(11,90,169)'],
    [1/6, 'rgb(105,175,245)'],[2/6, 'rgb(105,175,245)'],
    [2/6, 'rgb(173,222,255)'],[3/6, 'rgb(173,222,255)'],
    [3/6, 'rgb(250,177,177)'],[4/6, 'rgb(250,177,177)'],
    [4/6, 'rgb(243,81,81)'], [5/6, 'rgb(243,81,81)'],
    [5/6, 'rgb(241,33,33)'], [1, 'rgb(241,33,33)'],
];

const colorScaleGray = [
    [0, 'rgb(230,238,255)'], [1/6, 'rgb(230,238,255)'],
    [1/6, 'rgb(204,220,220)'],[2/6, 'rgb(204,220,220)'],
    [2/6, 'rgb(153,165,170)'],[3/6, 'rgb(153,165,170)'],
    [3/6, 'rgb(102,115,120)'],[4/6, 'rgb(102,115,120)'],
    [4/6, 'rgb(51,65,70)'], [5/6, 'rgb(51,65,70)'],
    [5/6, 'rgb(0,15,30)'], [1, 'rgb(0,15,30)'],
];


class ContourMap extends Component {
  render() {
    const filterNumber = this.props.filterNumber;
    let cScale = colorScale;

    if (this.props.colorScalePreset){
      if (this.props.colorScalePreset === 'gray'){
        cScale = colorScaleGray;
      }
    }
    else if (this.props.colorScale){
      cScale = this.props.colorScale;
    }

    return (
      <div
        style={{
          position: "absolute",
          display: "block",
          marginLeft: 0,
          top: 0,
          left: 0,
          zIndex: 1,
          opacity: 0.5,
          background: "transparent",
          borderRadius: 15
        }}
      >
        <Plot
          ref={el => (this.plotRef = el)}
          data={[
            {
              z: this.props.data, // matrix (M x N)
              x: this.props.xCoords, // vector (N)
              y: this.props.yCoords, // vector (M)
              type: "contour",
              line: {
                smoothing: this.props.smoothing ? this.props.smoothing : 1.0
              },
              autocontour: false,
              contours: {
                showlines: false,
                start: 450,
                end: this.props.maxMagnitude,
                size: 5
              },
              showscale: false,
              colorscale: cScale
            }
          ]}
          layout={{
            height: this.props.height,
            width: this.props.width,
            borderradius: 15,
            paper_bgcolor: "#ffffff", // makes plot transparent
            plot_bgcolor: "#ffffff",

            margin: {
              l: 0,
              r: 0,
              t: 0,
              b: 0,
              pad: 0
            }
          }}
          config={{
            displayModeBar: false
          }}
        />
      </div>
    );
  }
}

export default ContourMap;
