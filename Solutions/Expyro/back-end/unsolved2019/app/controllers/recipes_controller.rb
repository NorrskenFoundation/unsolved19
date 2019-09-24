class RecipesController < ApplicationController
  def index
    render json: RecipeRepresenter.for_collection.new(get_recipes).to_json
  end

  private

  def get_recipes
    food = current_user.purchases.map(&:food).uniq
    RecipeMatcher.call(food)
  end
end
