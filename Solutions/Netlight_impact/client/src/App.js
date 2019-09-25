import React from 'react'
import HeatMap from './components/HeatMap'
import TriggerList from './components/TriggerList'
import './App.css'

const App = () => (
  <div className="App">
    <HeatMap
      data={[{ lat: 59.33258, lng: 18.0649 }, { lat: 58.33258, lng: 18.0649 }]}
    />
    <TriggerList />
  </div>
)

export default App
