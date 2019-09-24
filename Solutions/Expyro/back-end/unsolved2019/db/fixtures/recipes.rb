Recipe.delete_all
RecipeItem.delete_all

10.times do
  food = Food.order('RANDOM()').load
  recipe = Recipe.create name: Faker::Food.dish, description: Faker::Food.description
  rand(4).times do
    recipe.foods << food.sample
  end
end
