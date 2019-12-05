import React, { useContext, useState } from 'react';
import { Product } from '../../utils';
import DialogTitle from '@material-ui/core/DialogTitle';
import Dialog from '@material-ui/core/Dialog';
import { Button } from '@material-ui/core';
import styled from 'styled-components';
import CameraPng from './Camera.png';
import { DataContext } from '../../context/DataContext';
type Props = {
  isOpen: boolean;
  hideDialog(): void;
};

const contentStyles = {
  display: 'flex',
  alignItems: 'center',
  justifyContent: 'center',
  width: '500px',
  padding: '2rem'
};

const ScanButton = styled.div`
  cursor: pointer;
  padding: 1rem;
  background: #ddd;
  &:hover {
    background: #eee;
  }
  width: 96px;
  height: 96px;

  display: flex;
  align-items: center;
  justify-content: center;
  flex-direction: column;

  font-size: 14px;
`;

const Camera = styled.img`
  height: 48px;
  margin-bottom: 0.5rem;
`;

const Or = styled.div`
  padding: 2rem;
`;

const RecipeDialog = ({ isOpen, hideDialog }: Props) => {
  const { addIngredient } = useContext(DataContext);
  const [name, setName] = useState('');
  const [expiration, setExpiration] = useState('long');
  const ingredient: Product = {
    // @ts-ignore
    expiration: expiration,
    id: '2',
    name: name
  };

  return (
    <Dialog
      onClose={hideDialog}
      aria-labelledby='simple-dialog-title'
      open={isOpen}
    >
      <DialogTitle>Add Ingredients</DialogTitle>
      <div style={contentStyles}>
        <div>
          <ScanButton>
            <Camera src={CameraPng} />
            Scan Receipt
          </ScanButton>
        </div>
        <Or>Or</Or>
        <div>
          <h4>Add Items</h4>
          <div>
            <label>Name</label>
            <input
              onChange={e => setName(e.target.value)}
              value={name}
              type='text'
            />
            <br />
            <label>Expire duration</label>
            <select
              onChange={e => {
                setExpiration(e.target.value);
              }}
            >
              <option value='short'>Short</option>
              <option value='medium'>Medium</option>
              <option value='long'>Long</option>
            </select>
            <button
              onClick={() => {
                addIngredient(ingredient);
                setName('');
              }}
            >
              Add
            </button>
          </div>
        </div>
      </div>
      <Button onClick={hideDialog}>Close</Button>
    </Dialog>
  );
};

export default RecipeDialog;
