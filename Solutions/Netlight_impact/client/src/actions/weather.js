import {
  FETCH_WEATHER_DATA_LOADING,
  FETCH_WEATHER_DATA_SUCCESS,
  FETCH_WEATHER_DATA_ERROR,
  FETCH_TRIGGERS_LOADING,
  FETCH_TRIGGERS_SUCCESS,
  FETCH_TRIGGERS_ERROR,
  FETCH_ACTIONS_LOADING,
  FETCH_ACTIONS_SUCCESS,
  FETCH_ACTIONS_ERROR,
} from '../actions/types'

export const fetchWeatherDataLoading = () => ({
  type: FETCH_WEATHER_DATA_LOADING,
})

export const fetchWeatherDataSuccess = (time, data) => ({
  type: FETCH_WEATHER_DATA_SUCCESS,
  payload: { time, data },
})

export const fetchWeatherDataError = error => ({
  type: FETCH_WEATHER_DATA_ERROR,
  payload: error,
})

export const fetchWeatherData = time => dispatch => {
  dispatch(fetchWeatherDataLoading())

  fetch(
    `https://afternoon-dawn-61570.herokuapp.com/api/weather?time=${encodeURIComponent(
      time
    )}`
  )
    .then(response => {
      if (!response.ok) {
        throw Error(response.statusText)
      }
      return response
    })
    .then(response => response.json())
    .then(data => dispatch(fetchWeatherDataSuccess(time, data.points)))
    .catch(error => dispatch(fetchWeatherDataError(error)))
}

export const fetchTriggersLoading = () => ({
  type: FETCH_TRIGGERS_LOADING,
})

export const fetchTriggersSuccess = data => ({
  type: FETCH_TRIGGERS_SUCCESS,
  payload: data,
})

export const fetchTriggersError = error => ({
  type: FETCH_TRIGGERS_ERROR,
  payload: error,
})

export const fetchTriggers = () => dispatch => {
  dispatch(fetchTriggersLoading())

  fetch('https://afternoon-dawn-61570.herokuapp.com/alarm/defs')
    .then(response => {
      if (!response.ok) {
        throw Error(response.statusText)
      }
      return response
    })
    .then(response => response.json())
    .then(data => dispatch(fetchTriggersSuccess(data)))
    .catch(error => dispatch(fetchTriggersError(error)))
}

export const fetchActionsLoading = () => ({
  type: FETCH_ACTIONS_LOADING,
})

export const fetchActionsSuccess = data => ({
  type: FETCH_ACTIONS_SUCCESS,
  payload: data,
})

export const fetchActionsError = error => ({
  type: FETCH_ACTIONS_ERROR,
  payload: error,
})

export const fetchActions = time => dispatch => {
  dispatch(fetchActionsLoading())

  fetch(
    `https://afternoon-dawn-61570.herokuapp.com/alarm/active?time=${encodeURIComponent(
      time
    )}`
  )
    .then(response => {
      if (!response.ok) {
        throw Error(response.statusText)
      }
      return response
    })
    .then(response => response.json())
    .then(data => dispatch(fetchActionsSuccess(data)))
    .catch(error => dispatch(fetchActionsError(error)))
}
