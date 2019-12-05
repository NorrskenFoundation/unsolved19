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
      <h1>We suggest you to make this meal</h1>
      {recipe ? (
        <HeaderContainer>
          <RecipeCard showIngredients recipe={recipe} />
        </HeaderContainer>
      ) : (
          <div>Sorry, could not find any recipes for the ingredients you have.</div>
      )}
    </div>
  );
};

export default Stage4;
