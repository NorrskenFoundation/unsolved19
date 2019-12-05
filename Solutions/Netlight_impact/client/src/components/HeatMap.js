import React, { Component } from 'react'
import { connect } from 'react-redux'
import GoogleMap from 'google-map-react'
import { fetchWeatherData, fetchActions } from '../actions/weather'
import MapMarker from './MapMarker'
import {
  getWeatherDataForSelectedTime,
  getSelectedTime,
  getActions,
} from '../reducers/selectors'

class HeatMap extends Component {
  componentDidMount() {
    this.props.fetchWeatherData(this.props.selectedTime)
    this.props.fetchActions(this.props.selectedTime)
  }

  render() {
    const { center, zoom, data, actions } = this.props
    return (
      <div style={{ height: '100vh', width: '100%' }}>
        <GoogleMap
          bootstrapURLKeys={{
            key: process.env.REACT_APP_GOOGLE_MAPS_API_KEY,
          }}
          defaultCenter={center}
          defaultZoom={zoom}
          heatmapLibrary={true}
          heatmap={{ positions: data, options: { radius: 20, opacity: 0.6 } }}
        >
          {actions.map(action => (
            <MapMarker
              lat={action.point.geometry.coordinates[1]}
              lng={action.point.geometry.coordinates[0]}
            />
          ))}
        </GoogleMap>
      </div>
    )
  }
}

HeatMap.defaultProps = {
  center: {
    lat: 59.33258,
    lng: 18.0649,
  },
  zoom: 10,
}

const mapStateToProps = state => ({
  data: getWeatherDataForSelectedTime(state),
  selectedTime: getSelectedTime(state),
  actions: getActions(state),
})

const mapDispatchToProps = dispatch => ({
  fetchWeatherData: time => dispatch(fetchWeatherData(time)),
  fetchActions: time => dispatch(fetchActions(time)),
})

export default connect(
  mapStateToProps,
  mapDispatchToProps
)(HeatMap)
