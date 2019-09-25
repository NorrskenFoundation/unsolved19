export const getSelectedTime = state => state.weather.selectedTime.toISOString()

export const getWeatherDataForSelectedTime = state =>
  state.weather.data[getSelectedTime(state)] || []

export const getTriggers = state => state.weather.triggers

export const getActions = state => state.weather.actions
