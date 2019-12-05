import React, { Component } from "react";

class VectorCanvas extends Component {
  constructor() {
    super();

    this.state = {
      canvasReady: false
    };
  }

  componentDidMount = () => {
    this.setupCanvas();
  };

  // Get canvas element and do some basic configurations
  setupCanvas = () => {
    this.canvasContext = this.canvas.getContext("2d");
    this.canvasContext.fillStyle = "#ffffff";
    this.canvasContext.strokeStyle = "#808080";
    this.canvasContext.lineWidth = 1.5 * this.props.resMultiplier;
    this.setState({ canvasReady: true });
  };

  // Credit: https://stackoverflow.com/a/26080467
  drawArrow = (ctx, fromx, fromy, tox, toy, headlen) => {
    var angle = Math.atan2(toy - fromy, tox - fromx);

    //starting path of the arrow from the start square to the end square and drawing the stroke

    ctx.moveTo(fromx, fromy);
    ctx.lineTo(tox, toy);

    //starting a new path from the head of the arrow to one of the sides of the point
    ctx.moveTo(tox, toy);
    ctx.lineTo(
      tox - headlen * Math.cos(angle - Math.PI / 7),
      toy - headlen * Math.sin(angle - Math.PI / 7)
    );

    //path from the side point of the arrow, to the other side point
    ctx.lineTo(
      tox - headlen * Math.cos(angle + Math.PI / 7),
      toy - headlen * Math.sin(angle + Math.PI / 7)
    );

    //path from the side point back to the tip of the arrow, and then again to the opposite side point
    ctx.lineTo(tox, toy);
    ctx.lineTo(
      tox - headlen * Math.cos(angle - Math.PI / 7),
      toy - headlen * Math.sin(angle - Math.PI / 7)
    );
  };

  canvasDrawVectors = (data) => {
    //variables to be used when creating the arrow
    const headlen = 3 * this.resMultiplier;
    const lineLength = 10;

    this.canvasContext.clearRect(0, 0, this.canvas.width, this.canvas.height);
    this.canvasContext.beginPath();

    data
      .filter((item, idx) => idx % this.props.filterNumber === 0)
      .forEach(row => {
        row
          .filter((item, idx) => idx % this.props.filterNumber === 0)
          .forEach(el => {
            // el[0] = xStart, el[1] = yStart, el[2] = u-direction, el[3] = v-direction
            const xStart = el[0] * this.props.width * this.resMultiplier;
            const yStart = el[1] * this.props.height * this.resMultiplier;
            const u = el[2] * this.props.width * this.resMultiplier;
            const v = el[3] * this.props.height * this.resMultiplier;
            this.drawArrow(
              this.canvasContext,
              xStart,
              yStart,
              xStart + lineLength * u,
              yStart + lineLength * v,
              headlen
            );
          });
      });

    this.canvasContext.stroke();
    this.canvasContext.fill();
  };


  componentDidUpdate = (prevProps, prevState) => {
    if (prevProps.height !== this.props.height || prevProps.width !== this.props.width){
      this.updateCanvas();
    }
  }

  updateCanvas = () => {
    if (this.state.canvasReady) {
      this.canvasDrawVectors(this.props.data);
    }
  };

  render() {
  /*  if (this.props.shouldCanvasResize) {
      this.updateCanvas();
    }*/

    // multiplies the resolution of the canvas
    this.resMultiplier = this.props.resMultiplier
      ? this.props.resMultiplier
      : 1;
    if (
      this.props.data !== undefined &&
      this.props.data.length > 0 &&
      this.state.canvasReady
    ) {
      this.canvasDrawVectors(this.props.data);
    }
    return (
      <div
        className={this.props.className}
        style={{ zIndex: 2, display: "block", marginLeft: 0 }}
      >
        <canvas
          ref={(canvas) => this.canvas = canvas}
          style={{
            opacity: this.props.opacity,
            position: "absolute",
            top: 0,
            left: 0,
            backgroundColor: "transparent",
            height: this.props.height,
            width: this.props.width
          }}
          height={this.resMultiplier * this.props.height}
          width={this.resMultiplier * this.props.width}
        />
      </div>
    );
  }
}

export default VectorCanvas;
