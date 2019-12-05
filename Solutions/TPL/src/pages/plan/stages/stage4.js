import React from "react";

import RecipeCard from "../../../components/RecipeCard";
import recipes from "../../../data/recipes";
import styled from "styled-components";

const HeaderContainer = styled.div`
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
`;

const Stage4 = ({ ingredients }) => {
  const ingredientsAsTitle = ingredients.map(_ => _.title);
  const recipe = recipes.find(recipe => {
    return recipe.ingredients.reduce((acc, ingredient) => {
      return acc && ingredientsAsTitle.includes(ingredient.title);
    }, true);
  });

  return (
    <div>
      <h1>We suggest you make this meal</h1>
      {recipe ? (
        <HeaderContainer>
          <RecipeCard showIngredients recipe={recipe} />
        </HeaderContainer>
      ) : (
        <h2>"Could not find a meal"</h2>
      )}
    </div>
  );
};

export default Stage4;
