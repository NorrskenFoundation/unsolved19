import express from 'express'
import path from 'path'
import bodyParser from 'body-parser'
import compression from 'compression'
import fetch from 'node-fetch'

import auth, { requireAuth, checkAuth } from './api/auth'

const app = express()
app.use(compression())
app.use(bodyParser.json())

app.use(express.static(path.join(__dirname, 'build')))

app.use(checkAuth)
app.use('/auth', auth)

app.get('/precipdata/:date', async (req, res) => {
    try {

        const { date } = req.params

        console.log('date:', date)

        const response = await fetch(`https://demo-apim.westeurope.cloudapp.azure.com/api_secure/PrecipitationAPI/3.0.0/weather/precipitation/at/${date}?location=stockholm`, {
            headers: {
                Authorization: `Bearer ${process.env.ERICSSON_AUTH}`
            }
        })
        const json = await response.json()

        const featurecollection = {
            "type": "FeatureCollection",
            "features": json.points
        }
        console.log(featurecollection)
        console.log('sending data')
        res.json(featurecollection)
    } catch (e) {
        console.error(e)
    }
})
app.get('/map/:from/:to', async (req, res) => {
    const {from, to} = req.params;
    const response = await fetch(`https://skolor-api.geoinfobyran.se/v1/osrm/route?start=${from}&end=${to}`);
    const json = await response.json();
    console.log(json);
    res.json(json);
})

app.get('*', (req, res) => {
    res.sendFile(path.join(__dirname, 'build', 'index.html'))
})

app.listen(process.env.PORT || 5000)