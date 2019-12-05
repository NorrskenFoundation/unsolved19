import { useCallback, useState } from 'react';
import { API_URL } from '../context/DataContext';
import { Dinner } from '../utils';

function useSuggestions() {
  const [loading, setLoading] = useState(false);
  const [suggestions, setSuggestions] = useState<Dinner[]>([]);

  const getSuggestions = useCallback(() => {
    async function getSuggestionsFromApi() {
      setLoading(true);
      try {
        const response = await fetch(`${API_URL}/recipes`).then(res =>
          res.json()
        );
        setSuggestions(response);
      } catch (e) {
        console.error(e);
      } finally {
        setLoading(false);
      }
    }
    return getSuggestionsFromApi();
  }, []);

  return { suggestions, getSuggestions, loading };
}
export default useSuggestions;
