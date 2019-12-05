import React, {
  createContext,
  useMemo,
  useState,
  useEffect,
  useCallback
} from 'react';
import { Product } from '../utils';

interface DataContextInterface {
  ingredients: Product[];
  addIngredient: (ingredient: Product) => void;
}

export const DataContext = createContext<DataContextInterface>({
  ingredients: [],
  addIngredient: (ingredient: Product) => {}
});

export const API_URL = 'https://unsolved2019.herokuapp.com';

export const DataContextProvider: React.FC = ({ children }) => {
  const [ingredients, setIngredients] = useState<Product[]>([]);

  useEffect(() => {
    async function fetchIngredients() {
      const response = await fetch(`${API_URL}/products`).then(res =>
        res.json()
      );

      setIngredients(response);
    }
    fetchIngredients();
  }, []);

  const addIngredient = useCallback(
    (ingredient: Product) => {
      setIngredients([...ingredients, ingredient]);
    },
    [ingredients]
  );

  const value = useMemo(
    () => ({
      ingredients,
      addIngredient
    }),
    [ingredients, addIngredient]
  );

  return <DataContext.Provider value={value}>{children}</DataContext.Provider>;
};
