class RecipeMatcher
  def self.call(foods)
    food_ids = foods.map(&:id)
    Recipe.includes(:recipe_items).where(recipe_items: { food_id: food_ids } )
  end
end
