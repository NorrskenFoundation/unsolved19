import React from "react";
import ProviderList from "./components/ProviderList";
import { Link } from "react-router-dom";

const Landing = () => {
  return (
    <div>
      <ProviderList />
      <Link to="/dinners">Next Step</Link>
    </div>
  );
};

export default Landing;
