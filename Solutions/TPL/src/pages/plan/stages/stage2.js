import React from "react";
import { Button } from "antd";
import styled from "styled-components";

import SelectList from "../../../components/selectList";
import _ from "lodash";

import RecipeCard from "../../../components/RecipeCard";

const CenteredText = styled.div`
  text-align: center;
`;

const ButtonContainer = styled.div`
  display: flex;
  justify-content: center;
  align-items: center;
  margin: 2rem auto;
`;

const SelectContainer = styled.div`
  margin: 2rem auto;
`;

const HeaderContainer = styled.div`
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
`;

class Stage2 extends React.Component {
  state = {
    selectedItems: []
  };

  selectItem(item) {
    if (this.state.selectedItems.indexOf(item) === -1) {
      this.setState({
        selectedItems: [...this.state.selectedItems, item]
      });
    } else {
      this.setState({
        selectedItems: _.pull(this.state.selectedItems, item)
      });
    }
  }

  render() {
    const { onSubmit, chosenRecipe } = this.props;
    const { selectedItems } = this.state;

    return (
      <div>
        <HeaderContainer>
          <h2>You've selected</h2>
          <RecipeCard recipe={chosenRecipe} />
        </HeaderContainer>
        <SelectContainer>
          <CenteredText>What do you have already?</CenteredText>
          <SelectList
            items={chosenRecipe.ingredients}
            selectedItems={selectedItems}
            onSelect={this.selectItem.bind(this)}
          />
          <ButtonContainer>
            <Button onClick={() => onSubmit(selectedItems)} block>
              Continue
            </Button>
          </ButtonContainer>
        </SelectContainer>
      </div>
    );
  }
}

export default Stage2;
