import React from "react";
import { Link } from "react-router-dom";

const aboutStyle = {
  fontSize: "21px",
  width: "500px"
};

const contentStyle = {
  display: "flex",
  justifyContent: "center",
  alignItems: "center",
  flexDirection: "column" as "column"
};

const LinkStyle = {
  fontSize: "18px",
  textTransform: "uppercase" as "uppercase",
  fontFamily: "Open sans"
};

const LinkStyleSmall = {
  marginTop: "5px",
  fontSize: "12px",
  textTransform: "uppercase" as "uppercase",
  fontFamily: "Open sans"
};

const Enter = () => {
  return (
    <div style={contentStyle}>
      <h1>Expyro</h1>
      <div className="App-logo">🐉</div>
      <p style={aboutStyle}>
        Expyro is a platform that suggest healthy meals based on what’s expiring
        in your fridge.
      </p>
      <Link to="/integrations" style={LinkStyle}>
        Log in
      </Link>
      <Link to="/integrations" style={LinkStyleSmall}>
        Contine without login
      </Link>
    </div>
  );
};

export default Enter;
