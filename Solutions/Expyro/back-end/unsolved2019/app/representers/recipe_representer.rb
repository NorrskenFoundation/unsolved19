require 'roar/json'

class RecipeRepresenter < Roar::Decorator
  include Roar::JSON

  property :id
  property :name
  property :description

  collection :foods, class: Food do
    property :id, as: :food_id
    property :name
    property :expiration
  end
end
