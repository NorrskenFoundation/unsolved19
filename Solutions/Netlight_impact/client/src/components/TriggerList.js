import React, { Component } from 'react'
import { connect } from 'react-redux'
import { getTriggers } from '../reducers/selectors'
import { fetchTriggers } from '../actions/weather'
import './TriggerList.css'

class TriggerList extends Component {
  componentDidMount() {
    this.props.fetchTriggers()
  }

  render() {
    const { triggers } = this.props
    return (
      <div className="trigger-list">
        <h1>Triggers</h1>
        {triggers &&
          triggers.map(triggerData => (
            <div className="trigger">
              <p>Trigger type: {triggerData.trigger.type}</p>
              <p>Threshold: {triggerData.trigger.threshold}</p>
              <p>Callback URL: {triggerData.callbackUrl}</p>
            </div>
          ))}
      </div>
    )
  }
}

const mapStateToProps = state => ({
  triggers: getTriggers(state),
})

const mapDispatchToProps = dispatch => ({
  fetchTriggers: () => dispatch(fetchTriggers()),
})

export default connect(
  mapStateToProps,
  mapDispatchToProps
)(TriggerList)
