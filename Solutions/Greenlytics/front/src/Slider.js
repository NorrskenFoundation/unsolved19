import React, {Component} from 'react';
import BaseSlider, {createSliderWithTooltip } from 'rc-slider';
import 'rc-slider/assets/index.css';
//import {formatYearMonthDayHourMin, formatYearMonthDay, diffDays} from '../../Util/Util';

const Slider = createSliderWithTooltip(BaseSlider);

class StyledSlider extends Component {


  constructor(props){
    super(props);

    this.showTooltip = this.showTooltip.bind(this);
    this.onSliderChange = this.onSliderChange.bind(this);

    let nrTicks = 0;

    // if nrTicks is not specified, but a start date and  are
  //  if (props.nrTicks === undefined){
      // calculate the numebr of days between the two range dates
    //  nrTicks = diffDays(this.props.start, this.props.end)-1;
    //}
    // if nrTicks is explicitly specified
  //  else {
      nrTicks = props.nrTicks;
  //  }

    this.state = {nrTicks: nrTicks}

  }


  // This fixes an issue where data is still loading and nrTicks becomes undefined.
  // Here nrTicks is update again when new props arrive
  static getDerivedStateFromProps = (nextProps, prevState) => {
    if (nextProps.nrTicks && nextProps.nrTicks !== prevState.nrTicks){
      return {nrTicks: nextProps.nrTicks};
    }

    return null;
  }


  /*onSliderChange = (value) => {
    console.log("mov");
    console.log(value);
    console.log(this.props.nrTicks);
    this.props.update(value);
  }
  */

  onSliderChange = (val) => {
    if (this.props.disabled){
      if (this.props.onDisabledSliderMovement){
        this.props.onDisabledSliderMovement();
      }
      return;
    }

    let direction = 0;
    if (val < this.props.prevVal){
      direction = -1;
    }
    else {
      direction = 1;
    }

    // If slider moves fast, some ticks might get skipped
    // Calculate absolute value of previous value and current
    const movement = direction*Math.abs(this.props.prevVal-val);
    this.props.update(val, movement);


  }

  // Function used in the Slider property tipFormatter
  showTooltip = () => {
    return this.props.showValue;
    // if value is a date, convert it to string
  //  return formatYearMonthDayHourMin(this.props.showValue);
  }


  render(){
    return(

      <div className='no-select' style={{width: this.props.width, display: 'flex', flexDirection: 'row',
        padding: 10, alignItems: 'center', justifyContent: 'center',
        pointerEvents: 'all',
        opacity: this.props.disabled ? 0.5 : 1.0, ...this.props.style,
      }}>
        <div style={{padding: '2px 5px 2px 5px', display: 'inline-block',
          marginRight: 20, backgroundColor:'#3f3f45',
          borderRadius: 8,
          fontSize: 12,
          color: 'white',
          whiteSpace: 'nowrap',
        }}>
          {this.props.start}
        </div>
        <Slider
          onBeforeChange={this.props.onSlideStart}
          onChange={this.onSliderChange}
          onAfterChange={this.props.onSlideEnd}
          railStyle={{ backgroundColor: '#21c4fb', height: 7 }}
          trackStyle={{backgroundColor: 'transparent'}} // just to prevent color change on the slider bar
          handleStyle={[{
            borderColor: '#21c4fb',
            marginLeft: -12,
            width: 24,
            height: 15,
            borderRadius: 8,

          }]}
          tipFormatter={this.showTooltip}
          tipProps={{prefixCls: 'rc-slider-tooltip'}}
          max={this.props.positiveDirection ? this.state.nrTicks : 0}
          defaultValue={0}
          value={this.props.currentTick}
          min={!this.props.positiveDirection ? -this.state.nrTicks : 0}
          />
          <div style={{padding: '2px 5px 2px 5px', display: 'inline-block',
             marginLeft: 20, backgroundColor:'#3f3f45',
             borderRadius: 8,
             fontSize: 12,
             color: 'white',
             whiteSpace: 'nowrap',
           }}>
            {this.props.end}
          </div>

        </div>

    );
  }






}

export default StyledSlider;
