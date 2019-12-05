

# Hackathon for Ericsson Weather Challenge 2.8

- Team name: Always Bring the Weather
- Team members: Johanna Samuelsen, Alexander Gyllensvärd, Andres Mellik, Johnnie Hård, Magnus Westerberg
- Solution: See below and slides
- Presentation slides: [SLIDES](https://github.com/johnniehard/impactweatherhackathon/blob/master/2.8%20-%20Always%20Bring%20the%20Weather.key)
- Services used: Ericsson Weather Data, OSRM, MapBox, ISF, TensorFlow
- Tech stack: Node.js, React

## Available

- Local, 'micro data' for local weather

## Challenge

- Provide municipalities with short term (half an hour) forecasts of local weather

## Values to Deliver
- To improve waterworks and planning
- To automatically turn on and off pumps
- To give give citizens access to the same kind of forecasts for their personal use cases

## Solution
- By combining Ericsson's data with user generated data, parsing it to an open forecasting model and feeding the whole this into TensorFLow, we can bootstrap machine learning and get the local, short term forecasts that will deliver the value.

## Examples of User Data

### Automated
- Geo location
- Device signal profile

### User Genereated
- Pictures of the sky
- Waze-like confirmation of weather conditions (i.e. opt-in notifications ask you to confirm if it's raining or not)

## Open Forecasting Model
- IFS

## Machine Learning Platform
- TensorFlow
