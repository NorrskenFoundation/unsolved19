import React, { useState } from "react";
import { Button } from "antd";
import { Link } from "react-router-dom";
import StageWrapper from "../../components/stageWrapper";
import Stage2 from "./stages/stage2";
import Stage3 from "./stages/stage3";
import Stage4 from "./stages/stage4";

const Start = ({}) => {
  const [stages, setActiveStages] = useState([0]);
  const [ingredients, setIngredients] = useState([]);
  const [leftovers, setLeftovers] = useState([]);

  const setActiveStage = stage => {
    setActiveStages([...stages, stage]);
  };

  return (
    <div
      style={{
        maxWidth: "500px",
        background: "white",
        minHeight: "100vh",
        margin: "20px auto",
        padding: "20px",
        borderRadius: "20px"
      }}
    >
      <StageWrapper>
        <h1>What do you want to do?</h1>
        <Button onClick={() => setActiveStage(2)}>I have leftovers</Button>
        <Link to="/plan">
          <Button>I want to plan my meals</Button>
        </Link>
      </StageWrapper>

      {/* Stage 2 - Depending on the previous answer what do you have left over? */}
      {stages.includes(2) && (
        <StageWrapper>
          <Stage2
            previousMeal={0}
            onSubmit={chosenLeftOvers => {
              setLeftovers(chosenLeftOvers);
              setActiveStage(3);
            }}
          />
        </StageWrapper>
      )}

      {/* Stage 3 - Do you also have this ingredient? */}
      {stages.includes(3) && (
        <StageWrapper>
          <Stage3
            leftovers={leftovers}
            onSubmit={choseningredients => {
              setIngredients(choseningredients);
              setActiveStage(4);
            }}
          />
        </StageWrapper>
      )}

      {/* Stage 4 - We suggest you make this meal */}
      {stages.includes(4) && (
        <StageWrapper>
          <Stage4 ingredients={[...ingredients, ...leftovers]} />
        </StageWrapper>
      )}
    </div>
  );
};

export default Start;
