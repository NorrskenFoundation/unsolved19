import React from 'react';
import { Dinner } from '../../utils';
import DialogTitle from '@material-ui/core/DialogTitle';
import Dialog from '@material-ui/core/Dialog';
import { Button } from '@material-ui/core';

type Props = {
  isOpen: boolean;
  hideDialog(): void;
  dinner?: Dinner;
};

const ingredientStyle = {
  marginBottom: '10px',
  display: 'flex',
  alignItems: 'center',
  justifyContent: 'center',
  listStyleType: 'none',
  fontSize: '13px'
};

const listStyles = {
  marginTop: '5px',
  padding: 0
};

const stepsStyle = {
  marginTop: '5px',
  padding: '20px'
};

const printStyle = {
  display: 'flex',
  alignItems: 'center',
  justifyContent: 'center',
  color: 'black',
  width: '150px',
  marginBottom: '20px'
};

const contentStyles = {
  display: 'flex',
  alignItems: 'center',
  justifyContent: 'center',
  width: '500px',
  flexDirection: 'column' as 'column'
};

const RecipeDialog = ({ isOpen, hideDialog, dinner }: Props) => {
  if (!dinner) {
    return null;
  }

  return (
    <Dialog
      onClose={hideDialog}
      aria-labelledby='simple-dialog-title'
      open={isOpen}
    >
      <div style={contentStyles}>
        <DialogTitle id='simple-dialog-title'>{dinner.name}</DialogTitle>
        <b>Ingredients</b>
        <ul style={listStyles}>
          {dinner.foods.map(i => (
            <li key={i.id} style={ingredientStyle}>
              {i.name}
            </li>
          ))}
        </ul>
        {dinner.description && (
          <div style={stepsStyle}>
            <b>Instructions</b>
            <p>{dinner.description}</p>
          </div>
        )}
        <a href='#print' style={printStyle}>
          ️ 🖨️ Print recipe
        </a>
        <a href='#print' style={printStyle}>
          Mark as cooked
        </a>
      </div>
      <Button onClick={hideDialog}>Close</Button>
    </Dialog>
  );
};

export default RecipeDialog;
