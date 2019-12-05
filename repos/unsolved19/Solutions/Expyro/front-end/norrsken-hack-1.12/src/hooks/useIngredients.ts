import { useContext } from 'react';
import { DataContext } from '../context/DataContext';

export function useIngredients() {
  const { ingredients } = useContext(DataContext);
  return {
    ingredients
  };
}
