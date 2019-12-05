class Recipe < ApplicationRecord
  has_many :recipe_items
  has_many :foods, through: :recipe_items
end
