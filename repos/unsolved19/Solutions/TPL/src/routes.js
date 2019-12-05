import React from "react";

import { BrowserRouter, Route, Switch } from "react-router-dom";

import Start from "./pages/start/index";
import Plan from "./pages/plan/index";

export default () => (
  <div>
    <BrowserRouter>
      <Switch>
        <Route path="/" exact component={Start} />
        <Route path="/plan" exact component={Plan} />
      </Switch>
    </BrowserRouter>
  </div>
);
