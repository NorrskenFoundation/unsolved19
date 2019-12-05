import React from 'react';
import './App.css';
import styled from 'styled-components';
import ApiConfig from './ApiConfig';
import Plot from './Plot';
import MeteoMap from './Map/MeteoMap';
import BasemapImage from './Assets/Norrsken-hack-stockholm.png';
import Slider from './Slider';
import ColorBar from './ColorBar';
import moment from 'moment';


const colorScale = [
    [0, 'rgb(255,255,255)'], [1/6, 'rgb(255,255,255)'],
    [1/6, 'rgb(105,175,245)'],[2/6, 'rgb(105,175,245)'],
    [2/6, 'rgb(173,222,255)'],[3/6, 'rgb(173,222,255)'],
    [3/6, 'rgb(250,177,177)'],[4/6, 'rgb(250,177,177)'],
    [4/6, 'rgb(243,81,81)'], [5/6, 'rgb(243,81,81)'],
    [5/6, 'rgb(241,33,33)'], [1, 'rgb(241,33,33)'],
];


const Container = styled.div`
  display: flex;
  justify-content: flex-start;
  align-items: center;
  flex-direction: column;
  width: 100%;
  height: 100vh;
  background-color: #f2f6f9e9;
`;

const CardContainer = styled.div`
  display: flex;
  justify-content: center;
  align-items: center;
  flex-direction: row;
  width: 95%;
  height: 100vh;
  margin-left: 32px;
  margin-right: 32px;
`;

const NavBar = styled.div`
  background-color: white;
  height: 80px;
  width: 100%;
  display: flex;
  flex-direction: row;
  justify-content: flex-start;
  box-shadow: 0px 1px 4px 1px #3f3f4522;
  margin-bottom: 4px;
`


const Card = styled.div`
  background-color: white;
  box-shadow: 0px 1px 4px 1px #3f3f4522;
  border-radius: 10px;
  padding: 16px;

`;


const Overlay = styled.div`
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: transparent;
  z-index: 10;
`

const Point = styled.div`
  position: absolute;
  bottom: 51%;
  right: 48%;
  background-color: purple;
  height: 20px;
  width: 20px;
  border-radius: 20px;
  z-index: 20;
`


class App extends React.Component {


  state = {
    grid: [[1]],
    date: new Date('2019-09-09 03:00'),
    value: 0,
    prevVal: 0,
    smhiData: {x: [], y: [], color: '#21c4fb'}
  }


  dateToStringNice = (date) => {
    const dateStr = moment(date).format('YYYY-MM-DD HH:mm');
    return dateStr;
  }

  dateToString = (date) => {
    const dateStr = moment(date).format('YYYYMMDDHHmm');
    return dateStr;
  }

  changeMinute = (value, change) => {
    let addVal = -1;
    if (value >= this.state.prevVal){
      addVal = 1;
    }

    const tempDate = new Date(this.state.date.getTime());
    tempDate.setMinutes(tempDate.getMinutes()+addVal);
    this.setState({
      date: tempDate,
      value: value,
      prevVal: this.state.value,
    })
    this.fetchData(tempDate);
  }


  fetchData = async (date) => {
    const response = await fetch(ApiConfig.localApi+'?timestamp='+this.dateToString(date));
    const data = await response.json();

    this.setState({
      grid: data.grids[0],
    })
  }


  fetchSmhi = async () => {
    const response = await fetch('http://localhost:5000/api/get_smhi');
    const data = await response.json();
    this.setState({
      smhiData: {
        x: data['timestamps'],
        y: data['values'],
        color: '#21c4fb'
      }
    })

  }

  componentDidMount =  () => {
    this.fetchData(this.state.date);
    this.fetchSmhi();

  }

  render(){


    const maxValue = 700;


    return (
      <Container>
        <NavBar>
          <img src={require('./Assets/watermind.png')} style={{height: 80, marginLeft: 32}}/>
        </NavBar>
        <CardContainer>
          <Card style={{flex: 1}}>
            <div style={{marginBottom: 16, fontWeight: 'bold', color: '#404e48'}}>
              Precipitation per minute
            </div>
            <div style={{position: 'relative', width: '100%', height: '100%'}}>
              <MeteoMap
                mapImage={BasemapImage}
                height={450}
                contourData={this.state.grid}
                onMapRendered={() => {}}
                maxMagnitude={maxValue}
                contourSmoothing={0}
                isDataAvailable={true}
                colorScale={colorScale}
              />
              <Overlay>
                <Point/>
              </Overlay>
            </div>
            <ColorBar style={{margin: 5}} title='mm/min' height={40}
              width={500}
              colorScale={colorScale}
              maxValue={maxValue/1020*30/60} opacity={0.5}/>
          </Card>
          <Card style={{marginLeft: 32, flex: 1}}>
            <div style={{marginLeft: 16, marginBottom: 16}}>
              {this.dateToStringNice(this.state.date)}
            </div>
            <Slider
              currentTick={this.state.value}
              start={0}
              nrTicks={60}
              end={59}
              showValue={this.dateToStringNice(this.state.date)}
              prevVal={this.state.prevVal}
              update={(value, change) => this.changeMinute(value, change)}
            />
            <Plot
              data={[
                this.state.smhiData
              ]}
            />
          </Card>
        </CardContainer>
      </Container>
    );
  }

}

export default App;
