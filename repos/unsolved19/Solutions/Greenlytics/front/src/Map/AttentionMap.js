import React, { Component } from "react";
import simpleheat from 'simpleheat';


class AttentionMap extends Component {

  constructor(){
    super();

    this.state = {
      heatMapReady: false,
    }
  }

  componentDidMount() {
    this.setupHeatMap();
    this.setupBounds();
    this.setState({
      heatMapReady: true,
    });
  }

  setupHeatMap = () => {
    this.heatCtx = this.heatCanvas.getContext("2d");

    const grad = { 0.2: "blue", 0.45: "lime", 0.65: "orange", 1.0: "red" };

    const heat = simpleheat(this.heatCanvas);
    heat.radius(this.props.heatMapPointRadius, 10);
    heat.gradient(grad);

    this.heatMap = heat;

  };

  setupBounds = () => {
    this.boundsCtx = this.boundsCanvas.getContext("2d");
  };

  drawAttentionBoundaries = (xMin, xMax, yMin, yMax) => {
    this.boundsCtx.clearRect(
      0,
      0,
      this.boundsCanvas.width,
      this.boundsCanvas.height
    );
    this.boundsCtx.fillStyle = "red";
    this.boundsCtx.strokeStyle = "red";
    this.boundsCtx.lineWidth = 2;
    this.boundsCtx.setLineDash([5]);
    this.boundsCtx.beginPath();

    this.boundsCtx.moveTo(xMin, yMin); // upper line
    this.boundsCtx.lineTo(xMax, yMin);

    this.boundsCtx.moveTo(xMin, yMin); // left line
    this.boundsCtx.lineTo(xMin, yMax);

    this.boundsCtx.moveTo(xMax, yMin); // right line
    this.boundsCtx.lineTo(xMax, yMax);

    this.boundsCtx.moveTo(xMin, yMax); // bottom line
    this.boundsCtx.lineTo(xMax, yMax);

    this.boundsCtx.fill();
    this.boundsCtx.stroke();
  };

  updateCanvas = () => {
    this.heatMap.resize();
    this.heatMap.radius(this.props.heatMapPointRadius, this.props.heatMapBlurRadius);
  };

  shouldComponentUpdate = (nextProps, nextState) => {
    if (nextProps.heatMapPointRadius !== this.props.heatMapPointRadius
      || nextProps.heatMapBlurRadius !== this.props.heatMapBlurRadius
    ){
      this.heatMap.radius(nextProps.heatMapPointRadius, nextProps.heatMapBlurRadius);
    }
    return true;
  }

  componentDidUpdate = () => {
    if (this.state.heatMapReady && this.props.boundaries){
      const { xMin, xMax, yMin, yMax } = this.props.boundaries;

      this.drawAttentionBoundaries(
        xMin * this.props.width,
        xMax * this.props.width,
        yMin * this.props.height,
        yMax * this.props.height
      );
    }
  }

  render() {
    if (
      this.state.heatMapReady &&
      this.props.data &&
      this.props.data.length > 0
    ) {


      // data only contains x and y position scalars that need to be multiplied by actual width and height in pixels
      this.heatMap.data(
        this.props.data.map(array => [
          array[0] * this.props.width,
          array[1] * this.props.height,
          array[2]
        ])
      );

      this.heatMap.draw();


    }

    return (
      <div style={{ opacity: this.props.opacity, zIndex: 3 }}>
        <canvas
          ref={(c) => this.boundsCanvas = c}
          height={this.props.height}
          width={this.props.width}
          style={{
            opacity: 0.7,
            position: "absolute",
            top: 0,
            left: 0,
            zIndex: 3
          }}
        />

        <canvas
          ref={(c) => this.heatCanvas = c}
          height={this.props.height}
          width={this.props.width}
          style={{
            opacity: 0.7,
            position: "absolute",
            top: 0,
            left: 0,
            zIndex: 3
          }}
        />
      </div>
    );
  }
}

AttentionMap.defaultProps = {
  heatMapPointRadius: 10,
  heatMapBlurRadius: 10,
  opacity: 1,
};

export default AttentionMap;
