class ProductsController < ApplicationController
  def index
    render json: PurchaseRepresenter.for_collection.new(get_purchases).to_json
  end

  private

  def get_purchases
    PurchaseFetcher.call(current_user)
  end
end
