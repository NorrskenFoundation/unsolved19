import React, { useState } from 'react';
import { Input, Button, Loader } from 'semantic-ui-react';
import axios from 'axios';
import moment from 'moment'
import haversine from 'haversine';

const TOKEN = process.env.TOKEN;
const MINUTE_DELTA = '15';
const DISTANCE = 10000;

const toDateFormat = dateString => `${dateString.slice(0, 4)}-${dateString.slice(4, 6)}-${dateString.slice(6, 8)}:${dateString.slice(8, 10)}:${dateString.slice(10, 12)}`;

async function queryForWeather(userPosition) {
  const { data: mostRecentData } = await axios({
    method: 'get',
    url: `https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/availability?location=stockholm`,
    headers: { Authorization: TOKEN }
  }).catch(console.error);

  const toAnalysePromises = [];
  const timeToTry = moment(new Date(toDateFormat(mostRecentData.maxTime)));
  
  for (let i = 0; i < 3; i++) {
    toAnalysePromises.push(
      axios({
        method: 'get',
        url: `https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/${timeToTry.format("YYYYMMDDHHmm")}?location=stockholm`,
        headers: { Authorization: TOKEN }
      }).catch(console.error)
    );

    timeToTry.subtract(MINUTE_DELTA, 'minutes');
  }

  const toAnalyse = await Promise.all(toAnalysePromises);

  const averages = toAnalyse.map(({ data }) => {    
    const points = data.points.filter(({ geometry }) => {
      const [longitude, latitude] = geometry.coordinates;
      const distance = haversine(userPosition, { latitude, longitude }, { unit: 'meter' });

      return distance < DISTANCE;
    });

    const avg = points.reduce((reduced, { properties }) =>  reduced + properties.value, 0) / points.length;

    return avg;
  });

  
   return averages[0] + (averages[0] - averages[averages.length - 1]);
}


const renderResult = prediction => {
  let result;
  
  if (prediction <= 0) {
    result = 'Its not going to rain';
  } else if (prediction < 0.5) {
    result = 'There may be a drop or two'
  } else if (prediction < 1) {
    result = 'There will be light rain';
  } else if (prediction < 4) {
    result = 'Bring an umbrella';
  } else {
    result = 'Cars will be floating';
  }

  return (
    <div>
      <h2 style={{ margin: '1em' }}>In 30 minutes ...</h2>
      <p style={{ margin: '1em', fontSize: '3em' }}>{result}</p>
      <h2 style={{ margin: '1em' }}>with 0.5% certainty</h2>
    </div>
  );
};

function App() {
  const [latitude, setLat] = useState('59.3293');
  const [longitude, setLng] = useState('18.0686');
  const [descision, setDescision] = useState(null);
  const [loading, setLoading] = useState(false);

  return (
    <div 
      style={{
        backgroundColor: '#282c34',
        minHeight: '100vh',
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
        justifyContent: 'center',
        fontSize: 'calc(10px + 2vmin)',
        color: 'white',
        textAlign: 'center'
      }}
    >
      {
        loading && <Loader active inline size="massive" />
      }
      { 
        !descision && !loading && (
          <Input
            style={{ margin: '1em' }}
            inverted
            placeholder="Latitude"
            value={latitude}
            onChange={({ target }) => setLat(target.value)}
          />
        )
      }
      { 
        !descision && !loading && (
          <Input
            style={{ margin: '1em' }}
            inverted
            placeholder="Longitude"
            value={longitude}
            onChange={({ target }) => setLng(target.value)}
          />
        )
      }
      {
        !descision && !loading && (
          <Button
            style={{ margin: '1em' }}
            inverted
            disabled={!latitude || !longitude}
            onClick={() => {
              setLoading(true)
              queryForWeather({ latitude, longitude }).then(setDescision).then(() => setLoading(false))
            }}
            content="Get prediction"
          />
        )
      }
      {(descision || descision === 0) && renderResult(descision)}
    </div>
  );
}

export default App;
