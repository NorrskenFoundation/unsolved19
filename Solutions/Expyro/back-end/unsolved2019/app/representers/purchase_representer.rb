require 'roar/json'

class PurchaseRepresenter < Roar::Decorator
  include Roar::JSON

  property :food_id
  property :name
  property :expiration
  property :created_at
end
