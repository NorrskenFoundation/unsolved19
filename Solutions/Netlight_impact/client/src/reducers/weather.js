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

const initialState = {
  isLoading: false,
  data: {},
  selectedTime: new Date('2019-09-16T18:00:00+02:00'),
  triggers: [],
  actions: [],
}

const weatherReducer = (state = initialState, { type, payload }) => {
  switch (type) {
    case FETCH_WEATHER_DATA_LOADING:
      return {
        ...state,
        isLoading: true,
      }
    case FETCH_WEATHER_DATA_SUCCESS:
      return {
        ...state,
        data: {
          ...state.data,
          [payload.time]: payload.data.map(point => ({
            lat: point.latitude,
            lng: point.longitude,
            weight: point.intensity,
          })),
        },
        isLoading: false,
      }
    case FETCH_WEATHER_DATA_ERROR: {
      return {
        ...state,
        isLoading: false,
      }
    }
    case FETCH_TRIGGERS_LOADING:
      return {
        ...state,
        isLoading: true,
      }
    case FETCH_TRIGGERS_SUCCESS:
      return {
        ...state,
        triggers: payload,
        isLoading: false,
      }
    case FETCH_TRIGGERS_ERROR: {
      return {
        ...state,
        isLoading: false,
      }
    }
    case FETCH_ACTIONS_LOADING:
      return {
        ...state,
        isLoading: true,
      }
    case FETCH_ACTIONS_SUCCESS:
      return {
        ...state,
        actions: payload,
        isLoading: false,
      }
    case FETCH_ACTIONS_ERROR: {
      return {
        ...state,
        isLoading: false,
      }
    }
    default:
      return state
  }
}

export default weatherReducer
