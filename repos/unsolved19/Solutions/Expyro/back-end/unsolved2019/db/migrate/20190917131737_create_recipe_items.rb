class CreateRecipeItems < ActiveRecord::Migration[6.0]
  def change
    create_table :recipe_items do |t|
      t.belongs_to :recipe
      t.belongs_to :food
      t.timestamps
    end
  end
end
