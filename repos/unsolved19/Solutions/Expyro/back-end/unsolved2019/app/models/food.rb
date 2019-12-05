class Food < ApplicationRecord
  enum expiration: { short: 1, medium: 2, long: 3 }

  has_many :purchases

  def self.random(n = 3)
    order('RANDOM()').limit(n)
  end
end
