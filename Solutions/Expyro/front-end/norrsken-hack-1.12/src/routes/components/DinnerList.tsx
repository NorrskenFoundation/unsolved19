import React, { useState } from "react";
import { Dinner } from "../../utils";
import DinnerItem from "./DinnerItem";
import RecipeDialog from "./RecipeDialog";

type Props = {
  dinners: Dinner[];
};

const dinnerListStyle = {
  padding: 0,
  width: "500px"
};

const Wrap = {
  padding: "20px"
};

const DinnerList = ({ dinners }: Props) => {
  const [dinner, setDinner] = useState<Dinner | undefined>(undefined);
  const [dialogIsOpen, setDialogIsOpen] = useState(false);

  const showRecipe = (dinner: Dinner) => {
    setDinner(dinner);
    setDialogIsOpen(true);
  };

  if (dinners.length < 1) {
    return <h3>No dinners found :(</h3>;
  }

  return (
    <div style={Wrap}>
      <h2>Recommended Recipes</h2>
      <ul style={dinnerListStyle}>
        {dinners.map(d => (
          <DinnerItem name={d.name} key={d.id} onClick={() => showRecipe(d)} />
        ))}
      </ul>
      <RecipeDialog
        isOpen={dialogIsOpen}
        hideDialog={() => setDialogIsOpen(false)}
        dinner={dinner}
      />
    </div>
  );
};

export default DinnerList;
