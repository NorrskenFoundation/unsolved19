import React, { Component } from "react";
import ContourMap from "./ContourMap";
import VectorCanvas from "./VectorCanvas";
import AttentionMap from "./AttentionMap";


let mapOverlay = {
  borderRadius: 15,
  boxShadow:' 0 0 0 8px white',
};


let mapOverlayDark = {
  boxShadow: '0 0 0 8px #3f3f45',
  filter: 'brightness(1.25) saturate(1)',
  borderRadius: 15,
};

const noSelect = {
  userDrag: 'none',
  WebkitUserDrag: 'none',
  userSelect: 'none',
  MozUserSelect: 'none',
  WebkitUserSelect: 'none',
  msUserSelect: 'none',
  khtmlUserSelect: 'none',
  OUserSelect: 'none',
};

class MeteoMap extends Component {
  constructor(props) {
    super(props);

    this.state = {
      ratio: 1,
      height: props.height,
      width: props.width,
      mapRendered: false
    };
  }

  onImageLoaded = ({ target: image }, height) => {
    const ratio = image.naturalWidth / image.naturalHeight;

    this.setState({
      ratio: ratio,
      height: height,
      width: height * ratio,
      mapRendered: true
    });

    // callback for parent to know if basemap has been rendered
    if (this.props.onMapRendered) {
      this.props.onMapRendered({ target: image }, height);
    }
  };


  // this is to allow map to respond to dimensions changes
  static getDerivedStateFromProps = (nextProps, state) => {
    if (nextProps.height){
      return {height: nextProps.height, width: nextProps.height*state.ratio};
    }

    return null;
  }

  render() {
    if (this.props.style && this.props.style.backgroundColor){
      mapOverlay.boxShadow = `0 0 0 8px ${this.props.style.backgroundColor}`;
      mapOverlayDark.boxShadow = `0 0 0 8px ${this.props.style.backgroundColor}`;
    }

    return (
      <div
        style={{
          ...noSelect,
          position: "relative",
          height: this.state.height,
          width: this.state.width,
          background: "transparent",
          pointerEvents: "all",
          ...this.props.style
        }}
      >
        <img
          className={this.props.imageClassName}
          src={this.props.mapImage}
          onContextMenu={e => { // prevents right click menu
            e.preventDefault();
            return false;
          }}
          onLoad={event => this.onImageLoaded(event, this.state.height)}
          draggable={false}
          style={{
            ...noSelect,
            display: "block",
            position: "absolute",
            top: 0,
            left: 0,
            marginLeft: 0,
            width: this.state.width,
            height: this.state.height,
            opacity: this.props.isDataAvailable ? 1 : 0,
            zIndex: 0,
          }}
        />
        {this.props.isDataAvailable && (
          <div>
            <ContourMap
              height={this.state.height}
              width={this.state.width}
              data={this.props.contourData}
              maxMagnitude={this.props.maxMagnitude}
              smoothing={this.props.contourSmoothing}
              colorScale={this.props.colorScale}
              colorScalePreset={this.props.colorScalePreset}
            />

            {this.props.showVectors &&
            <VectorCanvas
              height={this.state.height}
              width={this.state.width}
              data={this.props.vectorData}
              opacity={this.props.vectorsToggled ? 1.0 : 0}
              filterNumber={2}
              resMultiplier={2} // multiplies canvas resolution
              shouldCanvasResize={this.props.shouldCanvasResize}
              setCanvasResized={this.props.setCanvasResized}
              boundaries={{
                // vectors will not be drawn outside of this boundary
                xMin: 0,
                xMax: this.state.width,
                yMin: 0,
                yMax: this.state.height
              }}
            />
            }
            {this.props.showHeatMap &&
              <AttentionMap
                height={this.state.height}
                width={this.state.width}
                data={this.props.heatMapData}
                heatMapPointRadius={this.props.heatMapPointRadius}
                heatMapBlurRadius={this.props.heatMapBlurRadius}
                boundaries={this.props.heatMapBoundaries}
                opacity={1}
              />

            }
            <div
              style={{
                ...(this.props.darkTheme ? mapOverlayDark : mapOverlay),
                zIndex: 10,
                position: "absolute",
                top: 0,
                l: 0,
                right: 0,
                bottom: 0,
                height: "100%",
                width: "100%",
                backgroundColor: "transparent"
              }}
            />
            <div
              style={{
                zIndex: 100,
                position: "absolute",
                top: 0,
                l: 0,
                right: 0,
                bottom: 0,
                height: "100%",
                width: "100%",
                backgroundColor: "transparent"
              }}
            />
          </div>
        )}
      </div>
    );
  }
}

export default MeteoMap;
