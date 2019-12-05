import React, { Component } from 'react'

const MARKER_SIZE = 40

const styles = {
  marker: {
    position: 'absolute',
    width: MARKER_SIZE,
    height: MARKER_SIZE,
    left: -MARKER_SIZE / 2,
    top: -MARKER_SIZE / 2,
    border: '5px solid #000000',
    borderRadius: MARKER_SIZE,
    backgroundColor: '#ffffff',
    textAlign: 'center',
    color: '#890f3a',
    fontSize: 35,
    padding: 4,
    cursor: 'pointer',
  },
  hover: {
    border: '5px solid #890f3a',
    color: '#000000',
  },
}

class MapMarker extends Component {
  render() {
    const { $hover } = this.props
    return (
      <div style={{ ...styles.marker, ...($hover ? styles.hover : {}) }}></div>
    )
  }
}

export default MapMarker
