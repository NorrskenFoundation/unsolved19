import { createStore, applyMiddleware } from 'redux'
import thunk from 'redux-thunk'
import { composeWithDevTools } from 'redux-devtools-extension'
import rootReducer from '../reducers'

const configureStore = initialState =>
  createStore(
    rootReducer,
    initialState,
    composeWithDevTools(applyMiddleware(thunk))
  )

export default configureStore
